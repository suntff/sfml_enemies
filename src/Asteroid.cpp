#include "Asteroid.hpp"

namespace msp {

    bool Asteroid::Setup(float x, float y) {
        this->x = x;
        this->y = y;

        if (!textureAsteroid.loadFromFile("assets\\asteroid.png")) {
            std::cerr << "Error while loading asteroid.png" << std::endl;
            return false;
        }
        spriteAsteroid.setTexture(textureAsteroid);

        spriteAsteroid.setScale(scaleFactor, scaleFactor);
        spriteAsteroid.setOrigin(textureAsteroid.getSize().x / 2, textureAsteroid.getSize().y / 2);
        spriteAsteroid.setPosition(x, y);
        return true;
    }

    sf::Sprite Asteroid::Get() {
        return spriteAsteroid;
    }

}
