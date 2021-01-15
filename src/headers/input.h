#pragma once
#include <SDL2/SDL.h>
#include <string>
namespace Input
{
    enum key
    {
        ARROW_LEFT = SDL_SCANCODE_LEFT,
        ARROW_RIGHT = SDL_SCANCODE_RIGHT,
        ARROW_DOWN = SDL_SCANCODE_DOWN,
        RIGHT_CTR = SDL_SCANCODE_RCTRL,
        A = SDL_SCANCODE_A,
        S = SDL_SCANCODE_S,
        D = SDL_SCANCODE_D,
        LEFT_CTR = SDL_SCANCODE_LCTRL
    };
    class input
    {
        const Uint8 *KeyboardState = SDL_GetKeyboardState(NULL);

        bool LeftArrow;
        bool RightArrow;
        bool DownArrow;
        bool RightCTRL;
        bool A;
        bool D;
        bool S;
        bool LeftCTRL;

        void GetInput();

    public:
        input();
        bool ReturnInput(std::string select);
    };
} // namespace Input