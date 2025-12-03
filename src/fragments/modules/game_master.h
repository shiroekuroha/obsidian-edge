#pragma once

#include "controlled_deck.h"
#include "core/renderer/ecs/node.h"
#include "deck.h"

namespace ObsidianEdge {
enum class Player : std::int8_t { House, User };

class GameMaster : public Node {
public:
    // ------------------------------------ Base Begin ------------------------------------

    GameMaster();
    ~GameMaster() override;

    GameMaster(const GameMaster &other) = delete;
    GameMaster(GameMaster &&other) noexcept = delete;

    auto operator=(const GameMaster &other) -> GameMaster & = delete;
    auto operator=(GameMaster &&other) noexcept -> GameMaster & = delete;

    [[nodiscard]] auto duplicate() const -> std::shared_ptr<Entity> override;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

    OE_SETUP_ENTITY_TYPE_DEC

    // ------------------------------------- Base End -------------------------------------

    void setupGame();
    void drawGame();
    void drawEndGame();

    void userHit();
    void userStay();

    void houseTurn();

    void houseWin();
    void userWin();

    [[nodiscard]] auto getDeckHighestScore(Deck &deck) const -> unsigned int;
    void addCardToDeckFromMasterDeck(Deck &deck);

private:
    void drawHouseHand(bool reveal = false);
    void drawUserHand();

    void drawWinScreen();

private:
    bool playerWinLast = false;
    float showEndGameScreen = 0.0f;

    Deck masterDeck;

    ControlledDeck houseCards;
    ControlledDeck userCards;

    unsigned int houseWinCount = 0;
    unsigned int userWinCount = 0;
};
} // namespace ObsidianEdge
