#include "headers/debugmodule.h"
#include "headers/player.h"
#include <iostream>
#include <string>

int DebugMode::returnHP(Player player) { return player.HP; }
int DebugMode::returnPunchIT(Player player) { return player.PT; }
int DebugMode::returnBlockIT(Player player) { return player.BT; }
int DebugMode::returnCurrentDMG(Player player) { return player.CTMG; }
void DebugMode::printMSG(std::string msg) { std::cout << "\033[1;31m[+]  \033[0m" << msg << std::endl; }