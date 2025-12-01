#include <pch.h>

#include "game_master.h"

#include "core/event/event_app.h"
#include "core/event/event_mouse.h"
#include "core/log/log.h"
#include "core/renderer/render_engine.h"

namespace ObsidianEdge {
GameMaster::GameMaster() : houseCards(this), userCards(this) {};

GameMaster::~GameMaster() = default;

auto GameMaster::duplicate() const -> std::shared_ptr<Entity> {
    OE_ERROR("Do not duplicate this class");
    throw std::runtime_error("Game Master is not a duplicateble class!");
}

void GameMaster::onAttach() {
    masterDeck.genDefaultDeck();
    masterDeck.shuffle();

    setupGame();
}

void GameMaster::onDetach() {}

void GameMaster::onUpdate(float delta) {
    if (showEndGameScreen > 0.0f) {
        showEndGameScreen += delta;

        if (showEndGameScreen >= 4.0f) {
            showEndGameScreen = 0.0f;
            clearChildren();

            houseCards.clear();
            userCards.clear();

            setupGame();
        }
    }
}

void GameMaster::onEvent(Event &event) {
    EventDispatcher eventDispatcher(event);

    eventDispatcher.dispatch<WindowResizedEvent>([this](WindowResizedEvent &event) -> bool {
        drawGame();

        return true;
    });

    eventDispatcher.dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent &event) -> bool {
        if (showEndGameScreen != 0)
            return false;

        switch (event.getMouseCode()) {
        case Input::MOUSE_LEFT:
            userHit();
            break;

        case Input::MOUSE_RIGHT:
            userStay();
            break;

        default:
            return false;
            break;
        }

        return false;
    });
}

OE_SETUP_ENTITY_TYPE_DEF(GameMaster, Node)

void GameMaster::setupGame() {
    // House

    addCardToDeckFromMasterDeck(houseCards);
    addCardToDeckFromMasterDeck(houseCards);

    if (getDeckHighestScore(houseCards) == 21) {
        houseWin();
    }

    // User

    addCardToDeckFromMasterDeck(userCards);
    addCardToDeckFromMasterDeck(userCards);

    if (getDeckHighestScore(userCards) == 21) {
        userWin();
    }

    drawGame();
}

void GameMaster::drawGame() {
    clearChildren();

    drawHouseHand();
    drawUserHand();
}

void GameMaster::drawEndGame() {
    clearChildren();
    drawHouseHand(true);
    drawUserHand();

    drawWinScreen();
}

void GameMaster::userHit() {
    addCardToDeckFromMasterDeck(userCards);

    drawGame();

    if (getDeckHighestScore(userCards) == 21) {
        userWin();
    }

    if (getDeckHighestScore(userCards) > 21) {
        houseWin();
    }
}

void GameMaster::userStay() { houseTurn(); }

void GameMaster::houseTurn() {
    while (getDeckHighestScore(houseCards) < getDeckHighestScore(userCards)) {
        addCardToDeckFromMasterDeck(houseCards);
    }

    drawGame();

    if (getDeckHighestScore(houseCards) <= 21) {
        houseWin();
    } else {
        userWin();
    }
}

void GameMaster::houseWin() {
    houseWinCount += 1;
    playerWinLast = false;
    showEndGameScreen = 0.01f;

    drawEndGame();
}

void GameMaster::userWin() {
    userWinCount += 1;
    playerWinLast = true;
    showEndGameScreen = 0.01f;

    drawEndGame();
}

auto GameMaster::getDeckHighestScore(Deck &deck) const -> unsigned int {
    unsigned int totalScore = 0;
    unsigned int aceCount = 0;

    for (unsigned int i = 0; i < deck.count(); i++) {
        if (deck.getCard(i).getCardValue() % s_cardRankLimit == 0) {
            aceCount++;
        } else {
            if (deck.getCard(i).getCardValue() % s_cardRankLimit < 10) {
                totalScore += deck.getCard(i).getCardValue() % s_cardRankLimit + 1;
            } else {
                totalScore += 10;
            }
        }
    }

    while (aceCount) {
        if (totalScore + 11 > 21)
            return totalScore + 1 * aceCount;

        totalScore += 11;
        aceCount--;
    }

    return totalScore;
}

void GameMaster::addCardToDeckFromMasterDeck(Deck &deck) {
    if (masterDeck.isEmpty()) {
        masterDeck.genDefaultDeck();
        masterDeck.shuffle();
    }

    deck.pushCard(masterDeck.getNext());
    masterDeck.popCard();
}

void GameMaster::drawHouseHand(bool reveal) {
    static const float drawAreaWidth = 800;
    Vector2 drawOrigin = Vector2((getRenderEngine().getViewportSize().x - drawAreaWidth) / 2,
                                 (getRenderEngine().getViewportSize().y - Card::cardSize_y));

    houseCards.drawCards(drawOrigin, drawAreaWidth, reveal ? DeckDrawMode::ShowAll : DeckDrawMode::ShowFirst);
}

void GameMaster::drawUserHand() {
    static const float drawAreaWidth = 800;
    Vector2 drawOrigin = Vector2((getRenderEngine().getViewportSize().x - drawAreaWidth) / 2, (0));

    userCards.drawCards(drawOrigin, drawAreaWidth, DeckDrawMode::ShowAll);
}

void GameMaster::drawWinScreen() {
    static const float sX = 400.0f;
    static const float sY = 400.0f;

    static const float oX = (getRenderEngine().getViewportSize().x - sX) / 2;
    static const float oY = (getRenderEngine().getViewportSize().y - sY) / 2;

    addChild(std::shared_ptr<Entity>(new Image(Vector3(oX, oY, 0.0f), 0.0f, Vector3(1.0f), Vector2(sX, sY), Vector4(1.0f),
                                               Texture(playerWinLast ? "textures/user_win.png" : "textures/user_lost.png"))));
}
} // namespace ObsidianEdge
