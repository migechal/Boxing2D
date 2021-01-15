#include "player.h"
#pragma once
#include "player.h"

#include <iostream>
class DebugMode
{
public:
    int returnHP(Player player);
    int returnPunchIT(Player player);
    int returnBlockIT(Player player);
    int returnCurrentDMG(Player player);
    void printMSG(std::string msg);
};
