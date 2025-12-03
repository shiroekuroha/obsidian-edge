#pragma once

#include "deck.h"

namespace ObsidianEdge {
class GameMaster;

enum class DeckDrawMode : std::int8_t {
    ShowAll = 0,
    HideAll,
    ShowFirst,
};

/**
 * @brief Puppet class
 */
class ControlledDeck : public Deck {
public:
    // ------------------------------------ Base Begin ------------------------------------

    ControlledDeck(GameMaster *gameMaster);
    ~ControlledDeck() override;

    ControlledDeck(const ControlledDeck &other) = delete;
    ControlledDeck(ControlledDeck &&other) noexcept = delete;

    auto operator=(const ControlledDeck &other) -> ControlledDeck & = delete;
    auto operator=(ControlledDeck &&other) noexcept -> ControlledDeck & = delete;

    [[nodiscard]] auto duplicate() const -> std::shared_ptr<Entity> override;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

    OE_SETUP_ENTITY_TYPE_DEC

    // ------------------------------------- Base End -------------------------------------

    void drawCards(Vector2 showAreaOrigin, float showAreaWidth, DeckDrawMode drawMode);
    void drawCard(const Card &card, Vector2 position, bool hideCard);

private:
    gsl::not_null<GameMaster *> gameMaster;
    bool hideCards = false;
};
} // namespace ObsidianEdge
