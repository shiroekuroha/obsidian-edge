#include <pch.h>

#include "deck.h"

namespace ObsidianEdge {
Deck::Deck(const char *name) : m_name(name) {}

Deck::~Deck() = default;

Deck::Deck(const Deck &other) { *this = other; };

Deck::Deck(Deck &&other) noexcept { *this = std::move(other); }

auto Deck::operator=(const Deck &other) -> Deck & { return *this; }

auto Deck::operator=(Deck &&other) noexcept -> Deck & { return *this; }

auto Deck::duplicate() const -> std::shared_ptr<Entity> { return Entity::duplicateTyped<Deck>(*this); }

void Deck::onAttach() {}

void Deck::onDetach() {}

void Deck::onUpdate(float delta) {}

void Deck::onEvent(Event &event) {}

OE_SETUP_ENTITY_TYPE_DEF(Deck, Node)

void Deck::genDefaultDeck() {
    clear();

    for (unsigned int i = 0; i < s_cardValueLimit; i++)
        pushCard(Card(i));
}

auto Deck::isEmpty() const -> bool { return m_cards.empty(); }

auto Deck::getNext() const -> Card { return m_cards.front(); }

auto Deck::getCard(unsigned int index) const -> Card { return m_cards[index]; }

auto Deck::count() const -> unsigned int { return m_cards.size(); }

void Deck::pushCard(const Card &card) { m_cards.push_back(card); }

void Deck::popCard() { m_cards.erase(m_cards.begin()); }

void Deck::clear() { m_cards = {}; }

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 rng(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));

    std::shuffle(m_cards.begin(), m_cards.end(), rng);
}
} // namespace ObsidianEdge
