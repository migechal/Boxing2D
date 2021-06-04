//
// Created by migecha on 5/22/21.
//

#ifndef BOXING2D_RESOURCELOADER_H
#define BOXING2D_RESOURCELOADER_H


#include <cstdio>
#include <SDL2/SDL_system.h>
#include <string>

class ResourceLoader {
    static ResourceLoader* m_instance;
public:
    static ResourceLoader* getInstance();

    SDL_Texture *loadTexture(const std::string &location, SDL_Renderer *renderer);
};


#endif //BOXING2D_RESOURCELOADER_H
