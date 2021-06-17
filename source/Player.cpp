//
// Created by mikhail on 5/20/21.
//

#include "../include/Player.h"

#include <utility>
#include <algorithm>
#include <iostream>
#include "../include/FileManager.h"
#include "../include/WindowManager.h"
#include "../include/ResourceLoader.h"

Player::Player(std::string p_color, WindowManager *p_windowManager) : m_windowManager(p_windowManager),
                                                                      m_color(std::move(p_color)), m_health(100),
                                                                      m_damage(1), m_status(IDLE) {
//    for (int i = 0; i <= 4; ++i) {
//        std::transform(m_color.begin(), m_color.end(), m_color.begin(), ::toupper);
//        for (const std::string &file : FileManager::getInstance()->getFiles(
//                "../assets/" + m_color + "/" + playerStatusToString(i))) {
//            std::cout << file << std::endl;
//            m_textures[i].push_back(ResourceLoader::getInstance()->loadTexture(file, m_windowManager->getRenderer()));
//        }
//
//    }
    std::transform(m_color.begin(), m_color.end(), m_color.begin(), ::toupper);

    m_sprite = new type::Sprite("../assets/" + m_color, {100, 100});
}

std::string Player::playerStatusToString(int status) {
    switch (status) {
        case 0:
            return "Idle";
        case 1:
            return "Punch";
        case 2:
            return "Blocking";
        case 3:
            return "KO";
        default:
            return std::string();
    }
}

void Player::update() {

}

void Player::draw() {
    auto pos = m_sprite->getPosition();

    if (m_windowManager->draw(m_textures[m_status][m_statusCounter], nullptr, &pos) != 0) {
        std::cout << "Error: Unable to draw texture" << std::endl;
    }
}
