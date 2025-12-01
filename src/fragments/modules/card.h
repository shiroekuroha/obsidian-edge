#pragma once

#include "core/renderer/ecs/node2d.h"
#include "core/renderer/ecs/node2d/image.h"
#include "core/renderer/ecs/node2d/rectangle.h"

namespace ObsidianEdge {
static constexpr unsigned int s_cardValueLimit = 52;
static constexpr unsigned int s_cardRankLimit = 13;

enum class CardRank : std::uint8_t {
    // Card Name
    N_Ace = 0,
    N_02,
    N_03,
    N_04,
    N_05,
    N_06,
    N_07,
    N_08,
    N_09,
    N_10,
    Jack,
    Queen,
    King,
};

enum class CardSuit : std::uint8_t {
    // Suit Name
    Hearts,   // [39, 51]
    Diamonds, // [26, 38]
    Clubs,    // [13, 25]
    Spade     // [00, 12]
};

class Card : public Rectangle {
public:
    // ------------------------------------ Base Begin ------------------------------------

    Card(const char *name = "Node2D Card");
    ~Card() override;

    Card(const Card &other);
    Card(Card &&other) noexcept;

    auto operator=(const Card &other) -> Card &;
    auto operator=(Card &&other) noexcept -> Card &;

    [[nodiscard]] auto duplicate() const -> std::shared_ptr<Entity> override;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

    OE_SETUP_ENTITY_TYPE_DEC

    // ------------------------------------- Base End -------------------------------------

    Card(unsigned int cardValue, Vector3 position = Vector3(0.0f), float rotation = 0.0f, Vector3 scale = Vector3(1.0f),
         bool hideCard = false);

    void setCardValue(unsigned int cardValue);
    [[nodiscard]] auto getCardValue() const -> unsigned int;

    [[nodiscard]] auto getCardRank() const -> CardRank;
    [[nodiscard]] auto getCardSuit() const -> CardSuit;

    [[nodiscard]] auto getCardName() const -> std::string;
    auto getCardObject() -> std::shared_ptr<Image>;

    constexpr static const float cardSize_x = 140.0f;
    constexpr static const float cardSize_y = 200.0f;
    constexpr static const float suitSize_x = 40.0f;
    constexpr static const float suitSize_y = 40.0f;

private:
    unsigned int m_cardValue = 0; // [0, 51] or 0 <= x <= 51;
    bool m_hideCard = false;
};
} // namespace ObsidianEdge
