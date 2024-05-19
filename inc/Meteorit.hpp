#pragma once
#include <Enemies.hpp>
namespace mt
{
	class Meteorit : public mt::Enemies
	{
	public:
		Meteorit() = default;
		virtual ~Meteorit() {}

		void Attack() override
		{
			std::cout << "Attack" << std::endl;
		}
		void SpecialAbility(float x, float y, std::vector<Enemies*>& m_enemiesObjects,
			bool& flag_meteorit_visible, sf::Clock& clock_meteorit, Enemies*& obj) override{
					
		}
	};
}