#pragma once
#include <Enemies.hpp>
#include <Bullet.hpp>
namespace mt
{
	class Komet: public mt::Enemies
	{
	public:
		Komet() = default;
		virtual ~Komet() {}

		void Attack() override
		{
			std::cout << "Attack" << std::endl;
			
		}
		void SpecialAbility(float x, float y, std::vector<Enemies*>& m_enemiesObjects,
			bool& flag_meteorit_visible, sf::Clock& clock_meteorit, Enemies*& obj) override
		{
			m_x = x;
			m_y = y;
			m_spriteEnemies.setPosition(m_x, m_y);
		}

	};
}