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
#define movement 5
#define dist 160
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
SDL_Surface* screen = nullptr;
SDL_Surface* background = nullptr;
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
  int HP = 100;
  int CTMG;
  int PT;
  int BT;
  SDL_Surface* F1;
  SDL_Surface* F2;
  SDL_Surface* F3;
  bool punch;
  bool block;
  SDL_Rect pos;
  std::chrono::_V2::system_clock::time_point punchTimer =
    std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> PunchDif;
  vector<SDL_Surface*> KOP;
};
Player KOer;
class InitPhase {
  SDL_Surface* BMPloader(string file) {
    // SDL_Log(file.c_str(), " Has been loaded successfullys.");
    SDL_Surface* bp = SDL_LoadBMP(file.c_str());
    CHECK_RESULT(bp);
    return bp;
  }

public:
  string GetResourcePath(string applicationPath) {
    auto envResourcePath = getenv("PATH_TO_BOXING2D_RESOURCES");
    cout << "envResourcePath:  " << (envResourcePath ? envResourcePath : "NULL")
      << endl;
    if (envResourcePath != nullptr) {
      applicationPath.assign(envResourcePath);
      if (applicationPath.back() != '/') {
        applicationPath += "/";
      }
    }
    else {
      while (applicationPath.back() != '/') {
        applicationPath.pop_back();
      }
    }
    return applicationPath + "";
  }
  void LoadAllFiles(string path, Player& p1, Player& p2) {
    background = BMPloader(path + "main/assets/Ring.bmp");
    p1.F1 = BMPloader(path + "main/assets/BLUE/Idle/Blue_Idle.bmp");
    p1.F2 =
      BMPloader(path + "main/assets/BLUE/PunchRight/Blue-Punch-Right-4.bmp");
    p1.F3 = BMPloader(path + "main/assets/BLUE/Blocking/Blocking.bmp");
    p2.F1 = BMPloader(path + "main/assets/RED/Idle/Red_Idle.bmp");
    p2.F2 = BMPloader(path + "main/assets/RED/PunchRight/Punch-4.bmp");
    p2.F3 = BMPloader(path + "main/assets/RED/Blocking/Blocking-0.bmp");
    for (auto i = 0; i < 10; i++) {
      p1.KOP.push_back(
        BMPloader(path + "main/assets/BLUE/KO/KO-" + to_string(i) + ".bmp"));
      p2.KOP.push_back(
        BMPloader((path + "main/assets/RED/KO/KO-" + to_string(i) + ".bmp")));
    }
  }

  int getSettingsFromJson(string path, string tree, string child) {
    string pathSettings = path + "main/settings/config.json";
    std::cout << "Settings from " << pathSettings << std::endl;
    int num;
    namespace pt = boost::property_tree;
    pt::ptree loadPtreeRoot;
    pt::read_json(pathSettings, loadPtreeRoot);
    pt::ptree temp;
    pt::ptree tsize;
    string type;
    //! Get child of file
    temp = loadPtreeRoot.get_child(tree);
    tsize = temp.get_child(child);
    num = tsize.get_value<int>();
    return num;
  }
} IPH;
class DebugMode {
public:
  int returnHP(Player player) { return player.HP; }
  int returnPunchIT(Player player) { return player.PT; }
  int returnBlockIT(Player player) { return player.BT; }
  int returnCurrentDMG(Player player) { return player.CTMG; }
  void printMSG(string msg) { cout << "\033[1;31m[+]  \033[0m" << msg << endl; }
} DBM;

class GameBase {
  bool checkBlock(Player* player) {
    if (player.block) { cout << "true" << endl; }
    else { cout << "false" << endl; }
    return player.block;
  }

  void updateWindow(SDL_Window* window) {
    CHECK_RESULT(!SDL_UpdateWindowSurface(window));
  }
  void printKO(Player KOd, Player KOer, SDL_Surface* screen,
    SDL_Window* window) {
    for (int i = 0; i != 9; i++) {
      updateWindow(window);
      clearScreen(screen);
      PrintPlayer(KOer, 1, window);
      CHECK_RESULT(!SDL_BlitSurface(KOd.KOP[i], NULL, screen, &KOd.pos));
      SDL_Delay(60);
    }
  }

public:
  void clearTerm(int lines) {
    for (int i = 0; i < lines; i++) {
      cout << endl;
    }
  }

  void clearScreen(SDL_Surface* screen) {
    CHECK_RESULT(!SDL_BlitSurface(background, NULL, screen, NULL));
  }
  void updateScreen(SDL_Window* window) { updateWindow(window); }

  void PrintPlayer(Player player, int F, SDL_Window* window) {
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
      printKO(player, KOer, screen, window);
      break;
    default:
      DBM.printMSG("Invalid case");
    }
  }
  int decreaseHP(Player& player, int dmg = 5) {
    player.HP -= checkBlock(player) ? 0 : dmg;
    return player.HP;
  }
} GB;

class input {
  const Uint8* KeyboardState = SDL_GetKeyboardState(NULL);

  bool LeftArrow;
  bool RightArrow;
  bool DownArrow;
  bool RightCTRL;
  bool A;
  bool D;
  bool S;
  bool LeftCTRL;

  void GetInput() {
    LeftArrow = KeyboardState[key::ARROW_LEFT];
    RightArrow = KeyboardState[key::ARROW_RIGHT];
    DownArrow = KeyboardState[key::ARROW_DOWN];
    RightCTRL = KeyboardState[key::RIGHT_CTR];
    A = KeyboardState[key::A];
    D = KeyboardState[key::D];
    S = KeyboardState[key::S];
    LeftCTRL = KeyboardState[key::LEFT_CTR];
  }

public:
  input() {
    LeftArrow = false;
    RightArrow = false;
    DownArrow = false;
    RightCTRL = false;
    A = false;
    D = false;
    S = false;
    LeftCTRL = false;
  }
  bool ReturnInput(string select) {
    GetInput();
    if (select == "A") {
      return A;
    }
    if (select == "S") {
      return S;
    }
    if (select == "D") {
      return D;
    }
    if (select == "LeftCTRL") {
      return LeftCTRL;
    }
    if (select == "RightCTRL") {
      return RightCTRL;
    }
    if (select == "DownArrow") {
      return DownArrow;
    }
    if (select == "LeftArrow") {
      return LeftArrow;
    }
    if (select == "RightArrow") {
      return RightArrow;
    }
    else {
      perror("Wrong Input String");
      return -1;
    }
  }
} in;

int main(int argc, char** argv) {
  DBM.printMSG("Main start");
  Player Red;
  Player Blue;
  Red.pos.x = 1400;
  Red.pos.y = 600;
  Red.pos.w = Blue.pos.w = 499;
  Red.pos.h = Blue.pos.h = 489;
  Blue.pos.x = 0;
  Blue.pos.y = 600;

  string pathResources = IPH.GetResourcePath(argv[0]);
  GB.clearTerm(1);

  std::cout << "Resources path=" << pathResources << std::endl;
  GB.clearTerm(1);

  const int FrameTime =
    IPH.getSettingsFromJson(pathResources, "GameSettings", "fps");
  std::cout << "FPS: " << FrameTime << std::endl;
  Point2D WindowSize;
  WindowSize.x =
    IPH.getSettingsFromJson(pathResources, "Screen", "Resolution x");
  WindowSize.y =
    IPH.getSettingsFromJson(pathResources, "Screen", "Resolution y");
  GB.clearTerm(1);
  IPH.LoadAllFiles(pathResources, Blue, Red);
  SDL_Window* window = SDL_CreateWindow("Boxing2D", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, WindowSize.x,
    WindowSize.y, SDL_WINDOW_SHOWN);
  screen = SDL_GetWindowSurface(window);
  CHECK_RESULT(screen);
  CHECK_RESULT(window);  //! Test if variables are NULL or not.
  chrono::duration<double> timepunch = chrono::duration<double>(0.5);
  bool running = true;
  SDL_Event e;

  while (running) {
    GB.clearScreen(screen);                //* Clear screen
    auto startFrameTime = SDL_GetTicks();  //* Get current ticks
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
    // Reset clocks
    Red.PunchDif = std::chrono::high_resolution_clock::now() - Red.punchTimer;
    Blue.PunchDif = std::chrono::high_resolution_clock::now() - Blue.punchTimer;

    Red.punch = (in.ReturnInput("RightCTRL")) ? true : false;
    Red.block = (in.ReturnInput("DownArrow")) ? true : false;
    Blue.punch = (in.ReturnInput("LeftCTRL")) ? true : false;
    Blue.block = (in.ReturnInput("S")) ? true : false;
    //! Actual Input code and such goes here
    if (!Blue.punch && !Blue.block) {
      if (in.ReturnInput("D") &&
        Blue.pos.x + movement < Red.pos.x - Red.F1->w + dist) {
        Blue.pos.x += movement;
      }
      if (in.ReturnInput("A") && Blue.pos.x > 0) {
        Blue.pos.x -= movement;
      }
      GB.PrintPlayer(Blue, 1, window);
    }
    else if (Blue.punch && !Blue.block) {
      GB.PrintPlayer(Blue, 2, window);
      Blue.punch = false;
      if (Red.pos.x - movement < Blue.pos.x + Blue.F1->w - dist &&
        Blue.PunchDif > timepunch) {
        DBM.printMSG("Red HP: " + to_string(GB.decreaseHP(Blue)));
        Blue.punchTimer = std::chrono::high_resolution_clock::now();
      }
    }
    else if (!Blue.punch && Blue.block) {
      GB.PrintPlayer(Blue, 3, window);
      Blue.block = true;
      if (Blue.block) { cout << "true" << endl; }
      else { cout << "false" << endl; }
    }
    else {
      Blue.block = false;
      Blue.punch = false;
      GB.PrintPlayer(Blue, 1, window);
    }
    if (!Red.punch) {
      if (in.ReturnInput("LeftArrow") &&
        Red.pos.x - movement > Blue.pos.x + Blue.F1->w - dist) {
        Red.pos.x -= movement;
      }
      if (in.ReturnInput("RightArrow") && Red.pos.x < 1920 - Red.F1->w) {
        Red.pos.x += movement;
      }
      GB.PrintPlayer(Red, 1, window);
    }
    else {
      GB.PrintPlayer(Red, 2, window);
      Red.punch = false;
      if (Red.pos.x - movement < Blue.pos.x + Blue.F1->w - dist &&
        Red.PunchDif > timepunch) {
        DBM.printMSG("Blue HP: " + to_string(GB.decreaseHP(Red)));
        Red.punchTimer = std::chrono::high_resolution_clock::now();
      }
    }
    // CHECK FOR KO
    if (Red.HP <= 0) {
      KOer = Red;
      GB.PrintPlayer(Blue, 4, window);
      break;
    }
    if (Blue.HP <= 0) {
      KOer = Blue;
      GB.PrintPlayer(Red, 4, window);
      break;
    }
    GB.updateScreen(window);
  }
}