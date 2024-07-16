#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <bullet.hpp>

namespace msp
{

	class Ship
	{
		const int bulletR = 10;
		float v_bullet = 200;

		float x, y;
		float alpha;
		float v;
		float r;
		sf::Texture textureShip;
		sf::Sprite spriteShip;
		float scaleFactor = 0.2f;

		Bullet bullet;

	public:
		Ship() = default;

		bool Setup(float x, float y)
		{
			this->x = x;
			this->y = y;
			alpha = 0;
			v = 0;
			if (!textureShip.loadFromFile("assets\\ship.png"))
			{
				std::cerr << "Error while loading ship.png" << std::endl;
				return false;
			}
			spriteShip.setTexture(textureShip);

			spriteShip.setScale(scaleFactor, scaleFactor);
			spriteShip.setOrigin(textureShip.getSize().x / 2, textureShip.getSize().y / 2);
			spriteShip.setPosition(x, y);
			spriteShip.setRotation(alpha);

			if (textureShip.getSize().x > textureShip.getSize().y)
				r = scaleFactor * textureShip.getSize().x / 2;
			else
				r = scaleFactor * textureShip.getSize().y / 2;

			//bullet.Setup(100, 100, 20, 10, 10);
		}




		void setVelocity(float dv,float dt)
		{
			v += dv*dt;
			//std::cerr << m_v << std::endl;
		}

		float V() { return v; }

		void Move(float dt)
		{
			bullet.Move(dt);
			float alphaRad = acos(-1) * alpha / 180;
			x += v * cos(alphaRad) * dt;
			y += v * sin(alphaRad) * dt;
			spriteShip.setPosition(x, y);
		}

		float R() { return r; }
		float X() { return x; }
		float Y() { return y; }

		void Rotate(float dalpha,float dt)
		{
			alpha += dalpha*dt;
			spriteShip.setRotation(alpha);
		}

		sf::Sprite Get()
		{
			return spriteShip;
		}


		sf::CircleShape GetBullet()
		{
			return bullet.Get();
		}
		float Alpha() { return alpha; };
	};

}