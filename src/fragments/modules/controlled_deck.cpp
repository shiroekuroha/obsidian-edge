#include <pch.h>

#include "controlled_deck.h"

#include "core/log/log.h"
#include "core/renderer/render_engine.h"
#include "game_master.h"

namespace ObsidianEdge {
ControlledDeck::ControlledDeck(GameMaster *gameMaster) : gameMaster(gameMaster) {}

ControlledDeck::~ControlledDeck() = default;

auto ControlledDeck::duplicate() const -> std::shared_ptr<Entity> {
    OE_ERROR("Do not duplicate this class");
    throw std::runtime_error("Game Master is not a duplicateble class!");
}

void ControlledDeck::onAttach() {}

void ControlledDeck::onDetach() {}

void ControlledDeck::onUpdate(float delta) {}

void ControlledDeck::onEvent(Event &event) {}

OE_SETUP_ENTITY_TYPE_DEF(ControlledDeck, Image)

void ControlledDeck::drawCards(Vector2 showAreaOrigin, float showAreaWidth, DeckDrawMode drawMode) {
    clearChildren();

    static const float maxGap = 20.0f;

    unsigned int N = count();
    float gap = maxGap;

    if (N == 0)
        return;

    if (N > 1) {
        float totalWidth = (float)N * Card::cardSize_x + ((float)N - 1) * maxGap;
        if (totalWidth > showAreaWidth) {
            gap = (showAreaWidth - (float)N * Card::cardSize_x) / ((float)N - 1);
            if (gap < 0)
                gap = 0;
        }
    } else {
        gap = 0;
    }

    float rowWidth = (float)N * Card::cardSize_x + ((float)N - 1) * gap;
    float startX = showAreaOrigin.x + (showAreaWidth - rowWidth) / 2;
    float startY = showAreaOrigin.y;

    switch (drawMode) {
    case DeckDrawMode::ShowAll:
        for (int i = 0; i < count(); i++) {
            float cardPosX = startX + (float)i * (Card::cardSize_x + gap);
            float cardPosY = startY;

            drawCard(getCard(i), Vector2(cardPosX, cardPosY), false);
        }

        break;
    case DeckDrawMode::HideAll:
        for (int i = 0; i < count(); i++) {
            float cardPosX = startX + (float)i * (Card::cardSize_x + gap);
            float cardPosY = startY;

            drawCard(getCard(i), Vector2(cardPosX, cardPosY), true);
        }

        break;
    case DeckDrawMode::ShowFirst:
        drawCard(getCard(0), Vector2(startX, showAreaOrigin.y), false);

        for (int i = 1; i < count(); i++) {
            float cardPosX = startX + (float)i * (Card::cardSize_x + gap);
            float cardPosY = startY;

            drawCard(getCard(i), Vector2(cardPosX, cardPosY), true);
        }

        break;
    }
}

void ControlledDeck::drawCard(const Card &card, Vector2 position, bool hideCard) {
    (*gameMaster)
        .addChild(std::shared_ptr<Entity>(
            // Break
            new Card(card.getCardValue(), Vector3(position.x, position.y, 0.0f), 0.0f, Vector3(1.0f), (hideCard))));
}
} // namespace ObsidianEdge
