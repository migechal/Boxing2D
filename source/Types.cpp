//
// Created by mikhail on 5/20/21.
//

#include <string>
#include "../include/Types.h"

type::Vector2i::Vector2i(int p_x, int p_y) : x(p_x), y(p_y) {}

type::Vector2i type::Vector2i::operator+(const type::Vector2i &p_change) const {
    return {this->x - p_change.x, this->y - p_change.y};
}

void type::Vector2i::operator+=(const type::Vector2i &p_change) {
    this->x += p_change.x;
    this->y += p_change.y;
}

void type::Sprite::setPosition(type::Vector2i p_newPos) {
    m_position = p_newPos;
}

void type::Sprite::changePosition(type::Vector2i p_change) {

}

SDL_Rect type::Sprite::getPosition() const {
    SDL_Rect ret;
    ret.x = m_position.x;
    ret.y = m_position.y;
    return ret;
}

int type::Sprite::updateTexture() {
    return ++m_counter;
}

type::Sprite::Sprite(const std::string &p_baseSpriteAssetDir, type::Vector2i p_position) : m_position(p_position),
                                                                                           m_counter(0) {

}
