#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <bits/stdc++.h>
#include <time.h>
#include <unistd.h>

#include "headers/input.h"
#include "headers/init.h"
#include "headers/gamebase.h"
#include "headers/debugmodule.h"
#include "headers/player.h"
#include "headers/loading.h"

#define CHECK_RESULT(fnc)                                                   \
  {                                                                         \
    auto res = fnc;                                                         \
    if (!res)                                                               \
    {                                                                       \
      std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error(" \
                << SDL_GetError() << ")  err: " << res << " in " << #fnc    \
                << std::endl;                                               \
      exit(-2);                                                             \
    }                                                                       \
  }

const int PUNCHFRAME = 60;
const int movement = 5;
const int dist = 160;
const int hd = 5;
const int DefHP = 100;
//
SDL_Surface *screen = nullptr;
SDL_Surface *background = nullptr;
SDL_Window *window = nullptr;
struct Point2D
{
  int x;
  int y;
};

int main(int argc, char **argv)
{
  const int MAX = 5;
  std::string splashscreen = loading::GetResourcePath(argv[0]) + "main/assets/SplashScreen.bmp";
  SDL_Surface *splashScreenSurface = SDL_LoadBMP(splashscreen.c_str());
  SDL_Window *loadingScreen = SDL_CreateWindow("Loading...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
  SDL_Surface *loadingScreenSurface = SDL_GetWindowSurface(loadingScreen);
  CHECK_RESULT(splashScreenSurface);
  SDL_Color textColor = {0, 17, 255};
  loading::SplashScreen splash(loadingScreenSurface, MAX, 1280, 720, splashScreenSurface);
  splash.drawSplash("Debug Module Initialization", textColor);
  CHECK_RESULT(!SDL_UpdateWindowSurface(loadingScreen));
  DebugMode DBM;

  splash.drawSplash("InitPhase Module Initialization", textColor);
  SDL_UpdateWindowSurface(loadingScreen);

  InitPhase IPH(background);

  splash.drawSplash("Input Module Initialization", textColor);
  SDL_UpdateWindowSurface(loadingScreen);

  Input::input in;

  splash.drawSplash("Main Start Initialization", textColor);
  SDL_UpdateWindowSurface(loadingScreen);

  DBM.printMSG("Main start");
  Player Red;
  Player Blue;
  Red.color = "Red";
  Blue.color = "Blue";
  Red.pos.x = 1400;
  Red.pos.y = 600;
  Red.pos.w = Blue.pos.w = 499;
  Red.pos.h = Blue.pos.h = 489;
  Blue.pos.x = 0;
  Blue.pos.y = 600;

  splash.drawSplash("Getting Resources...", textColor);
  SDL_UpdateWindowSurface(loadingScreen);
  usleep(300000);

  std::string pathResources = loading::GetResourcePath(argv[0]);
  std::cout << "Resources path=" << pathResources << std::endl;
  splash.drawSplash("Creating Main Window", textColor);
  const int FrameTime =
      IPH.getSettingsFromJson(pathResources, "GameSettings", "fps");
  std::cout << "FPS: " << FrameTime << std::endl;
  Point2D WindowSize;
  WindowSize.x =
      IPH.getSettingsFromJson(pathResources, "Screen", "Resolution x");
  WindowSize.y =
      IPH.getSettingsFromJson(pathResources, "Screen", "Resolution y");
  IPH.LoadAllIMG(pathResources, Blue, Red);
  background = IPH.getBackground(pathResources);

  splash.~SplashScreen();
  SDL_UpdateWindowSurface(loadingScreen);
  SDL_DestroyWindow(loadingScreen);

  usleep(30000);

  window = SDL_CreateWindow("Boxing2D", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, WindowSize.x,
                            WindowSize.y, SDL_WINDOW_SHOWN);
  screen = SDL_GetWindowSurface(window);
  CHECK_RESULT(window); //! Test if variables are NULL or not.
  CHECK_RESULT(screen);

  GameBase GB(background, screen, window, DefHP);
  bool running = true;
  bool playing = false;
  SDL_Event e;

  while (running)
  {
    GB.clearScreen(); //* Clear screen
    // auto startFrameTime = SDL_GetTicks();  //* Get current ticks
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        SDL_Quit();
        running = false;
      }

      if (e.type == SDL_KEYDOWN)
      {
        if (e.key.keysym.sym == SDLK_ESCAPE)
        {
          SDL_Quit();
          running = false;
        }
      }
    }
    // Reset clocks
    if (playing)
    {
      Red.punch = (in.ReturnInput("RightCTRL")) ? true : false;
      Red.block = (in.ReturnInput("DownArrow")) ? true : false;
      Blue.punch = (in.ReturnInput("LeftCTRL")) ? true : false;
      Blue.block = (in.ReturnInput("S")) ? true : false;
      //! Actual Input code and such goes here
      if (!Blue.punch)
      {
        Blue.ableToDoDamage = true;
      }
      if (!Blue.punch && !Blue.block)
      {
        if (in.ReturnInput("D") &&
            Blue.pos.x + movement < Red.pos.x - Red.F1->w + dist)
        {
          Blue.pos.x += movement;
        }
        if (in.ReturnInput("A") && Blue.pos.x > 0)
        {
          Blue.pos.x -= movement;
        }
        GB.PrintPlayer(Blue, 1);
      }
      else if (Blue.punch && !Blue.block)
      {
        GB.PrintPlayer(Blue, 2);
        Blue.punch = false;
        if (Red.pos.x - movement < Blue.pos.x + Blue.F1->w - dist && Blue.ableToDoDamage)
        {
          int hp = GB.decreaseHP(Red, Blue);
          Blue.CTMG = 1;
          DBM.printMSG("Red HP: " + std::to_string(hp));
          Blue.ableToDoDamage = false;
        }
      }
      else if (!Blue.punch && Blue.block)
      {
        GB.PrintPlayer(Blue, 3);
        Blue.block = true;
      }
      else if (Blue.punch && Blue.block)
      {
        Blue.block = false;
        Blue.punch = false;
        Blue.ableToDoDamage = true;
        GB.PrintPlayer(Blue, 1);
      }
      if (!Red.punch)
      {
        Red.ableToDoDamage = true;
      }
      if (!Red.punch && !Red.block)
      {
        if (in.ReturnInput("LeftArrow") &&
            Red.pos.x - movement > Blue.pos.x + Blue.F1->w - dist)
        {
          Red.pos.x -= movement;
        }
        if (in.ReturnInput("RightArrow") && Red.pos.x < 1920 - Red.F1->w)
        {
          Red.pos.x += movement;
        }
        GB.PrintPlayer(Red, 1);
      }
      else if (Red.punch && !Red.block)
      {
        GB.PrintPlayer(Red, 2);
        Red.punch = false;
        if (Red.pos.x - movement < Blue.pos.x + Blue.F1->w - dist &&
            Red.ableToDoDamage)
        {
          int hp = GB.decreaseHP(Blue, Red);
          Red.CTMG = 1;
          DBM.printMSG("Blue HP: " + std::to_string(hp));
          Red.ableToDoDamage = false;
        }
      }
      else if (!Red.punch && Red.block)
      {
        GB.PrintPlayer(Red, 3);
        Red.block = true;
      }
      else if (Red.punch && Red.block)
      {
        Red.punch = false;
        Red.block = false;
        Red.ableToDoDamage = true;
        GB.PrintPlayer(Red, 1);
      }
      // CHECK FOR KO
      if (Red.HP <= 0)
      {
        GB.changeKOer(Blue);
        GB.PrintPlayer(Red, 4);
        break;
      }
      if (Blue.HP <= 0)
      {
        GB.changeKOer(Red);
        GB.PrintPlayer(Blue, 4);
        break;
      }
      //Draw hp bar for players
      GB.drawHPBar('L', 100, 100, Blue.HP, 0, 0, 255, 5);
      GB.drawHPBar('R', WindowSize.x - DefHP * 5 - 100, 100, Red.HP, 255, 0, 0, 5);
      GB.updateScreen(); //Update screen}
    }
    else{
      
    }
  }