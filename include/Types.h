//
// Created by mikhail on 5/20/21.
//

#ifndef BOXING2D_2_TYPES_H
#define BOXING2D_2_TYPES_H
#include <vector>
#include <SDL2/SDL.h>

namespace type{
    struct Vector2i{
        int x, y;
        Vector2i(int p_x, int p_y);
    };
    class Sprite{
        Vector2i m_position;
        std::vector<SDL_Texture*> textures;
    public:
        //Setter
        void setPosition(Vector2i p_newPos);

        //Changer
        void changePosition(Vector2i p_change);

        //Getter
        Vector2i getPosition();

        //Functions
        int updateTexture();
        int update();

        //Constructor
        Sprite();
    };
}


#endif //BOXING2D_2_TYPES_H
