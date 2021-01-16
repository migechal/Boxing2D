#include "headers/init.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#define CHECK_RESULT(fnc)                                                         \
    {                                                                             \
        auto res = fnc;                                                           \
        if (!res)                                                                 \
        {                                                                         \
            std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error(" \
                      << SDL_GetError() << ")  err: " << res << " in " << #fnc    \
                      << std::endl;                                               \
            exit(-2);                                                             \
        }                                                                         \
    }

InitPhase::InitPhase(SDL_Surface *background)
{
    background_ = background;
}

void InitPhase::LoadAllIMG(std::string path, Player &p1, Player &p2)
{
    p1.F1 = BMPloader(path + "main/assets/BLUE/Idle/Blue_Idle.bmp");
    p1.F2 =
        BMPloader(path + "main/assets/BLUE/PunchRight/Blue-Punch-Right-4.bmp");
    p1.F3 = BMPloader(path + "main/assets/BLUE/Blocking/Blocking.bmp");
    p2.F1 = BMPloader(path + "main/assets/RED/Idle/Red_Idle.bmp");
    p2.F2 = BMPloader(path + "main/assets/RED/PunchRight/Punch-4.bmp");
    p2.F3 = BMPloader(path + "main/assets/RED/Blocking/Blocking-0.bmp");
    for (auto i = 0; i < 10; i++)
    {
        p1.KOP.push_back(
            BMPloader(path + "main/assets/BLUE/KO/KO-" + std::to_string(i) + ".bmp"));
        p2.KOP.push_back(
            BMPloader((path + "main/assets/RED/KO/KO-" + std::to_string(i) + ".bmp")));
    }
}

SDL_Surface* InitPhase::getBackground(std::string path){
    return BMPloader(path + "main/assets/Ring.bmp");
}

SDL_Surface *InitPhase::BMPloader(std::string file)
{
    SDL_Log(file.c_str(), " Has been loaded successfullys.");
    SDL_Surface *bp = SDL_LoadBMP(file.c_str());
    CHECK_RESULT(bp);
    return bp;
}
Mix_Chunk *InitPhase::WAVloader(std::string file)
{
    auto sound = Mix_LoadWAV(file.c_str());
    CHECK_RESULT(sound);
    return sound;
}

std::string InitPhase::GetResourcePath(std::string applicationPath)
{
    auto envResourcePath = getenv("PATH_TO_BOXING2D_RESOURCES");
    std::cout << "envResourcePath:  " << (envResourcePath ? envResourcePath : "NULL")
              << std::endl;
    if (envResourcePath != nullptr)
    {
        applicationPath.assign(envResourcePath);
        if (applicationPath.back() != '/')
        {
            applicationPath += "/";
        }
    }
    else
    {
        while (applicationPath.back() != '/')
        {
            applicationPath.pop_back();
        }
    }
    return applicationPath + "";
}

void InitPhase::SetupSound()
{
    CHECK_RESULT(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512));
    Mix_AllocateChannels(4);
}

void InitPhase::LoadAllSound(std::string path, std::vector<Mix_Chunk *> sounds)
{
    sounds.push_back(Mix_LoadWAV((path + "background.wav").c_str()));
}

int InitPhase::getSettingsFromJson(std::string path, std::string tree, std::string child)
{
    std::string pathSettings = path + "settings/config.json";
    std::cout << "Settings from " << pathSettings << std::endl;
    int num;
    namespace pt = boost::property_tree;
    pt::ptree loadPtreeRoot;
    pt::read_json(pathSettings, loadPtreeRoot);
    pt::ptree temp;
    pt::ptree tsize;
    std::string type;
    //! Get child of file
    temp = loadPtreeRoot.get_child(tree);
    tsize = temp.get_child(child);
    num = tsize.get_value<int>();
    return num;
}
