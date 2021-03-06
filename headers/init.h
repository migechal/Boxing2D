#pragma once
#include "player.h"
#include <string>
#include <SDL2/SDL_mixer.h>
class InitPhase
{
    Mix_Chunk *WAVloader(std::string file);
    SDL_Surface *background_;

public:
    InitPhase(SDL_Surface *background);
    void LoadAllIMG(std::string path, Player &p1, Player &p2);
    SDL_Surface* getBackground(std::string path);
    void SetupSound();
    void LoadAllSound(std::string path, std::vector<Mix_Chunk *> sounds);
    int getSettingsFromJson(std::string path, std::string tree, std::string child);
};