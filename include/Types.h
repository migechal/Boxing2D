//
// Created by mikhail on 5/20/21.
//

#ifndef BOXING2D_2_TYPES_H
#define BOXING2D_2_TYPES_H
#include <vector>
#include <SDL2/SDL.h>

namespace type{
    struct Vector2i {
        int x, y;

        Vector2i(int p_x, int p_y);

        Vector2i operator+(const Vector2i &p_change) const;

        void operator+=(const Vector2i &p_change);
    };

    class Sprite {
        Vector2i m_position;
        int m_counter{};
        std::vector<std::vector<SDL_Texture *>> textures;
    public:
        //Setter
        void setPosition(Vector2i p_newPos);

        //Changer
        void changePosition(Vector2i p_change);

        //Getter
        SDL_Rect getPosition() const;

        //Functions
        int updateTexture();

        //Constructor
        Sprite(const std::string &p_baseSpriteAssetDir, type::Vector2i p_position);
    };
}


#endif //BOXING2D_2_TYPES_H
