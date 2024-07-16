#include "Enemies.hpp"

namespace msp
{

	bool Enemies::Setup(float x, float y, float vx, float vy,
		const std::string& texturePath, float scaleFactor)
	{
		this->x = x;
		this->y = y;
		this->vx = vx;
		this->vy = vy;

		if (!m_textureEnemies.loadFromFile(texturePath))
		{
			std::cout << "Error while loading " << texturePath << std::endl;
			return false;
		}
		m_spriteEnemies.setTexture(m_textureEnemies);

		m_spriteEnemies.setScale(scaleFactor, scaleFactor);
		m_spriteEnemies.setOrigin(m_textureEnemies.getSize().x / 2, m_textureEnemies.getSize().y / 2);
		m_spriteEnemies.setPosition(x, y);

		if (m_textureEnemies.getSize().x > m_textureEnemies.getSize().y)
			m_r = scaleFactor * m_textureEnemies.getSize().x / 2;
		else
			m_r = scaleFactor * m_textureEnemies.getSize().y / 2;

		return true;
	}

	sf::Sprite Enemies::Get()
	{
		return m_spriteEnemies;
	}

	void Enemies::Move(float dt)
	{
		x += vx * dt;
		y += vy * dt;
		m_spriteEnemies.setPosition(x, y);
	}

	void Enemies::Health(int level)
	{
		health -= 0.5 * health_start / level;
	}

	int Enemies::Get_health()
	{
		return health;
	}

}
