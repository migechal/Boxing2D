#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <time.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#define IMGUI_IMPLEMENTATION
#include "imgui/imgui.h"
#include "imgui/imgui_sdl.h"

#ifdef IMGUI_IMPLEMENTATION
#include <iterator>

#include "imgui/imgui.cpp"
#include "imgui/imgui_demo.cpp"
#include "imgui/imgui_draw.cpp"
#include "imgui/imgui_widgets.cpp"
#endif
using namespace std;
#define PUNCHFRAME 60
#define movment 10
#define dist 360
#define hd 5

#define CHECK_RESULT(fnc)                                                   \
  {                                                                         \
    auto res = fnc;                                                         \
    if (!res) {                                                             \
      std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error(" \
                << SDL_GetError() << ")  err: " << res << " in " << #fnc    \
                << std::endl;                                               \
      exit(-2);                                                             \
    }                                                                       \
  }

//
SDL_Surface *screen = nullptr;
SDL_Surface *background = nullptr;
struct Point2D {
  int x;
  int y;
};

enum key {
  ARROW_LEFT = SDL_SCANCODE_LEFT,
  ARROW_RIGHT = SDL_SCANCODE_RIGHT,
  ARROW_DOWN = SDL_SCANCODE_DOWN,
  RIGHT_CTR = SDL_SCANCODE_RCTRL,
  A = SDL_SCANCODE_A,
  S = SDL_SCANCODE_S,
  D = SDL_SCANCODE_D,
  LEFT_CTR = SDL_SCANCODE_LCTRL
};
struct Player {
  int HP;
  int CTMG;
  int PT;
  int BT;
  SDL_Surface *F1;
  SDL_Surface *F2;
  SDL_Surface *F3;
  SDL_Rect pos;
  vector<SDL_Surface *> KOP;
};
class InitPhase {
  SDL_Surface *BMPloader(string file) {
    // SDL_Log(file.c_str(), " Has been loaded successfullys.");
    SDL_Surface *bp = SDL_LoadBMP(file.c_str());
    CHECK_RESULT(bp);
    return bp;
  }

 public:
  string GetResourcePath(string applicationPath) {
    auto envResourcePath = getenv("PATH_TO_2DBOXING_RESOURCES");
    cout << "envResourcePath:  " << envResourcePath << endl;
    if (envResourcePath != nullptr) {
      applicationPath.assign(envResourcePath);
      if (applicationPath.back() != '/') {
        applicationPath += "/";
      }
    } else {
      while (applicationPath.back() != '/') {
        applicationPath.pop_back();
      }
    }
    return applicationPath + "main/";
  }
  void LoadAllFiles(string path, Player &p1, Player &p2) {
    background = BMPloader(path + "assets/Ring.bmp");
    p1.F1 = BMPloader(path + "assets/BLUE/Idle/Blue_Idle.bmp");
    p1.F2 = BMPloader(path + "assets/BLUE/PunchRight/Blue-Punch-Right-4.bmp");
    p1.F3 = BMPloader(path + "assets/BLUE/Blocking/Blocking.bmp");
    p2.F1 = BMPloader(path + "assets/RED/Idle/Red_Idle.bmp");
    p2.F2 = BMPloader(path + "assets/RED/PunchRight/Punch-4.bmp");
    p2.F3 = BMPloader(path + "assets/RED/Blocking/Blocking-0.bmp");
    for (auto i = 0; i < 10; i++) {
      p1.KOP.push_back(
          BMPloader(path + "assets/BLUE/KO/KO-" + to_string(i) + ".bmp"));
      p2.KOP.push_back(
          BMPloader((path + "assets/RED/KO/KO-" + to_string(i) + ".bmp")));
    }
  }

  Point2D getSettings(string path) {
    string pathSettings = path + "settings/config.json";
    std::cout << "getSettings from " << pathSettings << std::endl;

    Point2D P2D;
    namespace pt = boost::property_tree;
    pt::ptree loadPtreeRoot;
    pt::read_json(pathSettings, loadPtreeRoot);
    pt::ptree temp;
    pt::ptree tsizex;
    pt::ptree tsizey;
    pt::ptree ttype;
    string type;
    //! Get child of file
    temp = loadPtreeRoot.get_child("Screen");
    tsizex = temp.get_child("Resolution x");
    tsizey = temp.get_child("Resolution y");
    ttype = temp.get_child("Type");
    P2D.x = tsizex.get_value<int>();
    P2D.y = tsizey.get_value<int>();
    type = ttype.get_value<string>();
    return P2D;
  }
} IPH;
class DebugMode {
 public:
  int returnHP(Player player) { return player.HP; }
  int returnPunchIT(Player player) { return player.PT; }
  int returnBlockIT(Player player) { return player.BT; }
  int returnCurrentDMG(Player player) { return player.CTMG; }
};

class GameBase {
  int ChangeHP(int &PlayerHP, int addition = -5) {
    PlayerHP += addition;
    return PlayerHP;
  }
  void updateWindow(SDL_Window *window) {
    CHECK_RESULT(!SDL_UpdateWindowSurface(window));
  }
  void printKO(Player KOd, Player player, SDL_Surface *screen,
               SDL_Window *window) {
    for (int i = 0; i != 9; i++) {
      CHECK_RESULT(!SDL_BlitSurface(KOd.KOP[i], NULL, screen, &KOd.pos));
      CHECK_RESULT(!SDL_BlitSurface(player.F1, NULL, screen, &KOd.pos));
      updateWindow(window);
      SDL_Delay(60);
    }
  }

 public:
  void clearScreen(SDL_Surface *screen) {
    CHECK_RESULT(!SDL_BlitSurface(background, NULL, screen, NULL));
  }
  void updateScreen(SDL_Window *window) { updateWindow(window); }
  void PrintPlayer(Player player, int F, SDL_Window *window, Player nmp) {
    switch (F) {
      case 1:
        SDL_BlitSurface(player.F1, NULL, screen, &player.pos);
        break;
      case 2:
        SDL_BlitSurface(player.F2, NULL, screen, &player.pos);
        break;
      case 3:
        SDL_BlitSurface(player.F3, NULL, screen, &player.pos);
        break;
      case 4:
        printKO(player, nmp, screen, window);
        break;
    }
  }
} GB;

class input {
  const Uint8 *KeyboardState = SDL_GetKeyboardState(NULL);

 public:
  bool LeftArrow = false;
  bool RightArrow = false;
  bool DownArrow = false;
  bool RightCTRL = false;
  bool Left = false;
  bool Right = false;
  bool Down = false;
  bool LeftCTRL = false;
  input() {
    LeftArrow = KeyboardState[key::ARROW_LEFT];
    RightArrow = KeyboardState[key::ARROW_RIGHT];
    DownArrow = KeyboardState[key::ARROW_DOWN];
    RightCTRL = KeyboardState[key::RIGHT_CTR];
    Left = KeyboardState[key::A];
    Right = KeyboardState[key::D];
    Down = KeyboardState[key::S];
    LeftCTRL = KeyboardState[key::LEFT_CTR];
  }
} in;
int main(int argc, char **argv) {
  Player Red;
  Player Blue;
  string pathResources = IPH.GetResourcePath(argv[0]);
  std::cout << "Resources path=" << pathResources << std::endl;

  Point2D WindowSize = IPH.getSettings(pathResources);

  IPH.LoadAllFiles(pathResources, Blue, Red);
  SDL_Window *window = SDL_CreateWindow("Boxing2D", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, WindowSize.x,
                                        WindowSize.y, SDL_WINDOW_SHOWN);
  screen = SDL_GetWindowSurface(window);
  CHECK_RESULT(screen);
  CHECK_RESULT(window);  //! Test if variables are NULL or not.
  bool running = true;
  SDL_Event e;
  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        SDL_Quit();
        running = false;
      }
      if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_ESCAPE) {
          SDL_Quit();
          running = false;
        }
      }
    }
    //*
    GB.clearScreen(screen);
    GB.updateScreen(window);
  }
}