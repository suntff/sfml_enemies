#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

namespace msp
{

	class Enemies
	{
	protected:
		float x, y;
		float vx, vy;
		float m_r;
		int health_start = 120;
		int health = 120;
		sf::Texture m_textureEnemies;
		sf::Sprite m_spriteEnemies;

	public:
		Enemies() = default;
		virtual ~Enemies() {}

		bool Setup(float x, float y, float vx, float vy,
			const std::string& texturePath, float scaleFactor);

		sf::Sprite Get();

		void Move(float dt);
		void Health(int level);
		int Get_health();
		virtual void SpecialAbility() = 0;
	};

}
