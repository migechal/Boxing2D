//
// Created by mikhail on 5/20/21.
//

#ifndef BOXING2D_2_PLAYER_H
#define BOXING2D_2_PLAYER_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "Types.h"

enum PlayerStatus{
    IDLE = 0,
    PUNCHING = 1,
    BLOCKING = 2,
    KO = 3
};

class Player {
    std::vector<SDL_Texture*> m_textures[4];
    size_t m_health, m_damage, m_status;
    std::string m_color;
    type::Sprite sprite;
public:
    Player(std::string p_color);
};


#endif //BOXING2D_2_PLAYER_H
