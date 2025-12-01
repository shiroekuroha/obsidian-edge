#pragma once

#include "card.h"
#include "core/renderer/ecs/node.h"

namespace ObsidianEdge {
class Deck : public Node {
public:
    // ------------------------------------ Base Begin ------------------------------------

    Deck(const char *name = "Deck");
    ~Deck() override;

    Deck(const Deck &other);
    Deck(Deck &&other) noexcept;

    auto operator=(const Deck &other) -> Deck &;
    auto operator=(Deck &&other) noexcept -> Deck &;

    [[nodiscard]] auto duplicate() const -> std::shared_ptr<Entity> override;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

    OE_SETUP_ENTITY_TYPE_DEC

    // ------------------------------------- Base End -------------------------------------

    void genDefaultDeck();

    [[nodiscard]] auto isEmpty() const -> bool;
    [[nodiscard]] auto getNext() const -> Card;
    [[nodiscard]] auto getCard(unsigned int index) const -> Card;
    [[nodiscard]] auto count() const -> unsigned int;

    // Push Back
    void pushCard(const Card &card);
    // Pop Front
    void popCard();

    void clear();
    void shuffle();

private:
    std::string m_name = "";
    std::vector<Card> m_cards = {};
};
} // namespace ObsidianEdge
