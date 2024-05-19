#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
namespace mt
{

	class Enemies
	{
	protected:
		float m_x, m_y;
		float m_vx, m_vy;
		float m_r;
		sf::Texture m_textureEnemies;
		sf::Sprite m_spriteEnemies;
	public:
		Enemies() = default;
		virtual ~Enemies() {}

		bool Setup(float x, float y, float vx, float vy,
			const std::string& texturePath, float scaleFactor)
		{
			m_x = x;
			m_y = y;
			m_vx = vx;
			m_vy = vy;

			// ???????? ???????? ????
			if (!m_textureEnemies.loadFromFile(texturePath))
			{
				std::cout << "Error while loading " << texturePath << std::endl;
				return false;
			}
			m_spriteEnemies.setTexture(m_textureEnemies);

			m_spriteEnemies.setScale(scaleFactor, scaleFactor);
			m_spriteEnemies.setOrigin(m_textureEnemies.getSize().x / 2, m_textureEnemies.getSize().y / 2);
			m_spriteEnemies.setPosition(m_x, m_y);
			//m_spriteShip.setRotation(m_alpha);

			if (m_textureEnemies.getSize().x > m_textureEnemies.getSize().y)
				m_r = scaleFactor * m_textureEnemies.getSize().x / 2;
			else
				m_r = scaleFactor * m_textureEnemies.getSize().y / 2;
		}

		sf::Sprite Get()
		{
			return m_spriteEnemies;
		}

		void Move(float dt)
		{
			m_x += m_vx * dt;
			m_y += m_vy * dt;
			m_spriteEnemies.setPosition(m_x, m_y);
		}

		virtual void Attack() = 0;
		virtual void SpecialAbility(float x, float y, std::vector<Enemies*>& m_enemiesObjects,
			bool& flag_meteorit_visible, sf::Clock& clock_meteorit, Enemies*& obj) = 0;


	};
}