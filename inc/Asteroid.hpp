#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace msp {

    class Asteroid {
        float x, y;
        sf::Texture textureAsteroid;
        sf::Sprite spriteAsteroid;
        float scaleFactor = 0.1f;

    public:
        Asteroid() = default;
        bool Setup(float x, float y);
        sf::Sprite Get();
    };

}
