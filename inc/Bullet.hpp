#pragma once
#include <SFML/Graphics.hpp>

namespace msp
{

	class Bullet
	{
		float r;
		float x, y;
		float v;
		sf::CircleShape m_shape;
		float alpha;

	public:
		Bullet() = default;

		Bullet(float x, float y, float r, float v, float alpha);

		void Setup(float x, float y, float r, float v, float alpha);

		sf::CircleShape Get();

		float X();
		void X(float value);
		void Y(float value);
		float Y();
		float R();
		float V();
		void V(float value);
		void Move(float dt);
		void setVelocity(float dv, float dt);
	};

}

