#include <SDL2/SDL.h>
#include "headers/input.h"
#include <string>

Input::input::input()
{
    LeftArrow = false;
    RightArrow = false;
    DownArrow = false;
    RightCTRL = false;
    A = false;
    D = false;
    S = false;
    LeftCTRL = false;
}
bool Input::input::ReturnInput(std::string select)
{
    GetInput();
    if (select == "A")
    {
        return A;
    }
    if (select == "S")
    {
        return S;
    }
    if (select == "D")
    {
        return D;
    }
    if (select == "LeftCTRL")
    {
        return LeftCTRL;
    }
    if (select == "RightCTRL")
    {
        return RightCTRL;
    }
    if (select == "DownArrow")
    {
        return DownArrow;
    }
    if (select == "LeftArrow")
    {
        return LeftArrow;
    }
    if (select == "RightArrow")
    {
        return RightArrow;
    }
    else
    {
        perror("Wrong Input String");
        return -1;
    }
}

void Input::input::GetInput()
{
    LeftArrow = KeyboardState[key::ARROW_LEFT];
    RightArrow = KeyboardState[key::ARROW_RIGHT];
    DownArrow = KeyboardState[key::ARROW_DOWN];
    RightCTRL = KeyboardState[key::RIGHT_CTR];
    A = KeyboardState[key::A];
    D = KeyboardState[key::D];
    S = KeyboardState[key::S];
    LeftCTRL = KeyboardState[key::LEFT_CTR];
}
