#include <pch.h>

#include <memory>

#include "card.h"
#include "core/event/event_mouse.h"
#include "core/log/log.h"
#include "core/renderer/ecs/node2d/image.h"
#include "core/renderer/render_engine.h"
#include <glm/gtc/matrix_transform.hpp>

namespace ObsidianEdge {
Card::Card(const char *name) : Rectangle(name) {}

Card::~Card() = default;

Card::Card(const Card &other) { *this = other; };

Card::Card(Card &&other) noexcept { *this = std::move(other); }

auto Card::operator=(const Card &other) -> Card & {
    m_cardValue = other.m_cardValue;
    m_hideCard = other.m_hideCard;

    return *this;
}

auto Card::operator=(Card &&other) noexcept -> Card & {
    m_cardValue = other.m_cardValue;
    m_hideCard = other.m_hideCard;

    return *this;
}

auto Card::duplicate() const -> std::shared_ptr<Entity> { return Entity::duplicateTyped<Card>(*this); }

void Card::onAttach() {
    addChild(getCardObject());

    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}

void Card::onDetach() {
    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}

void Card::onUpdate(float delta) {}

void Card::onEvent(Event &event) {}

OE_SETUP_ENTITY_TYPE_DEF(Card, Image)

Card::Card(unsigned int cardValue, Vector3 position, float rotation, Vector3 scale, bool hideCard)
    : Rectangle(position, rotation, scale, {cardSize_x, cardSize_y}, {1.0f, 1.0f, 1.0f, 1.0f}), m_hideCard(hideCard) {
    setCardValue(cardValue);
}

void Card::setCardValue(unsigned int cardValue) {
    if (cardValue < s_cardValueLimit) {
        m_cardValue = cardValue;

        if (isPartOfEngine()) {
            getRenderEngine().reload();
        }
    } else {
        OE_ASSERT("Card value exceeded values allowed: card value({0})", m_cardValue);
        throw std::runtime_error("Card value exceeded values allowed");
    }
}

auto Card::getCardValue() const -> unsigned int { return m_cardValue; }

auto Card::getCardRank() const -> CardRank { return static_cast<CardRank>(m_cardValue % s_cardRankLimit); }

auto Card::getCardSuit() const -> CardSuit { return static_cast<CardSuit>(m_cardValue / s_cardRankLimit); }

auto Card::getCardName() const -> std::string {
    std::string final = "";

    switch (getCardRank()) {
    case CardRank::N_Ace:
        final = "Ace";
        break;
    case CardRank::N_02:
        final = "2";
        break;
    case CardRank::N_03:
        final = "3";
        break;
    case CardRank::N_04:
        final = "4";
        break;
    case CardRank::N_05:
        final = "5";
        break;
    case CardRank::N_06:
        final = "6";
        break;
    case CardRank::N_07:
        final = "7";
        break;
    case CardRank::N_08:
        final = "8";
        break;
    case CardRank::N_09:
        final = "9";
        break;
    case CardRank::N_10:
        final = "10";
        break;
    case CardRank::Jack:
        final = "Jack";
        break;
    case CardRank::Queen:
        final = "Queen";
        break;
    case CardRank::King:
        final = "King";
        break;
    }

    final += " of ";

    switch (getCardSuit()) {
    case CardSuit::Hearts:
        final += "Hearts";
        break;
    case CardSuit::Diamonds:
        final += "Diamonds";
        break;
    case CardSuit::Clubs:
        final += "Clubs";
        break;
    case CardSuit::Spade:
        final += "Spade";
        break;
    }

    return final;
}

auto Card::getCardObject() -> std::shared_ptr<Image> {
    if (m_hideCard) {
        std::shared_ptr<Image> main(new
                                    // Longer
                                    Image(Vector3(0.0f), 0.0f, Vector3(1.0f), {cardSize_x, cardSize_y}, {1.0, 1.0f, 1.0f, 1.0f},
                                          Texture("textures/cards/back.png")));

        return main;
    }

    std::string cardTexturePath;
    std::string suitTexturePath;
    Vector4 tintColor = {};

    switch (getCardRank()) {
    case CardRank::N_Ace:
        cardTexturePath = "textures/cards/ace.png";
        break;

    case CardRank::N_02:
        cardTexturePath = "textures/cards/2.png";
        break;

    case CardRank::N_03:
        cardTexturePath = "textures/cards/3.png";
        break;

    case CardRank::N_04:
        cardTexturePath = "textures/cards/4.png";
        break;

    case CardRank::N_05:
        cardTexturePath = "textures/cards/5.png";
        break;

    case CardRank::N_06:
        cardTexturePath = "textures/cards/6.png";
        break;

    case CardRank::N_07:
        cardTexturePath = "textures/cards/7.png";
        break;

    case CardRank::N_08:
        cardTexturePath = "textures/cards/8.png";
        break;

    case CardRank::N_09:
        cardTexturePath = "textures/cards/9.png";
        break;

    case CardRank::N_10:
        cardTexturePath = "textures/cards/10.png";
        break;

    case CardRank::Jack:
        cardTexturePath = "textures/cards/alt/jack.png";
        break;

    case CardRank::Queen:
        cardTexturePath = "textures/cards/alt/queen.png";
        break;

    case CardRank::King:
        cardTexturePath = "textures/cards/alt/king.png";
        break;
    }

    switch (getCardSuit()) {
    case CardSuit::Hearts:
        tintColor = {1.0f, 0.0f, 0.0f, 1.0f};
        suitTexturePath = "textures/cards/heart.png";
        break;
    case CardSuit::Diamonds:
        tintColor = {1.0f, 0.0f, 0.0f, 1.0f};
        suitTexturePath = "textures/cards/diamond.png";
        break;
    case CardSuit::Clubs:
        tintColor = {0.0f, 0.0f, 0.0f, 1.0f};
        suitTexturePath = "textures/cards/club.png";
        break;
    case CardSuit::Spade:
        tintColor = {0.0f, 0.0f, 0.0f, 1.0f};
        suitTexturePath = "textures/cards/spade.png";
        break;
    }

    std::shared_ptr<Image> main(
        new
        // Longer
        Image(Vector3(0.0f), 0.0f, Vector3(1.0f), {cardSize_x, cardSize_y}, tintColor, Texture(cardTexturePath.c_str())));

    std::shared_ptr<Image> sub(
        new
        // Longer
        Image({cardSize_x / 2 - suitSize_x / 2, cardSize_y / 2 - suitSize_y / 2, 1.0f}, 0.0f, {1.0f, 1.0f, 1.0f},
              {suitSize_x, suitSize_y}, tintColor, Texture(suitTexturePath.c_str())));

    main->addChild(sub);

    return main;
}

} // namespace ObsidianEdge
