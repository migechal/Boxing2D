#pragma once
#include "player.h"
#include <string>
#include <SDL2/SDL_mixer.h>
class InitPhase
{
    SDL_Surface *BMPloader(std::string file);
    Mix_Chunk *WAVloader(std::string file);
    SDL_Surface *background_;

public:
    InitPhase(SDL_Surface *background);
    std::string GetResourcePath(std::string applicationPath);
    void LoadAllIMG(std::string path, Player &p1, Player &p2);
    void SetupSound();
    void LoadAllSound(std::string path, std::vector<Mix_Chunk *> sounds);
    int getSettingsFromJson(std::string path, std::string tree, std::string child);
};