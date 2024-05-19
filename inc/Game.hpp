#pragma once
#include <string>
#include <thread>
#include <iostream>
#include <Ship.hpp>
#include <Bullet.hpp>
#include <SpaceObject.hpp>
#include <UFO.hpp>
#include <Destroyer.hpp>
#include <SFML/Audio.hpp>
#include <Enemies.hpp>
#include <Komet.hpp>
#include <Meteorit.hpp>
#include <Circle.hpp>

namespace mt
{

	const float pi = acos(-1);

	class Game
	{
		int m_width;
		int m_height;
		std::string m_capture;
		mt::Circle* m_c;
		int m_n;
		sf::RenderWindow m_window;
		sf::Texture m_textureBackground;
		sf::Sprite m_spriteBackground;
		sf::Font m_font;
		sf::Text m_fpsText;
		Ship m_ship;
		bool isVisible = true;
		bool isTouchBorder = true;
		Komet m_komet;
		UFO ufo;
		Destroyer destroyer;

		sf::SoundBuffer buffer;
		sf::Sound sound;

		bool m_pressedR = false;
		bool flag_meteorit_visible = true;
		bool m_pressedQ = false;
		std::vector<Enemies*> m_enemiesObjects;
		std::vector<SpaceObject*> m_spaceObjects;

		Enemies* obj;

	public:
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		~Game()
		{
			for (int i = 0; i < m_spaceObjects.size(); i++)
				delete m_spaceObjects[i];

			delete[] m_c;
		}

		bool Setup(int n)
		{
			m_n = n;
			// Ñîçäàíèå îêíà
			m_window.create(sf::VideoMode(m_width, m_height), m_capture);

			if (!buffer.loadFromFile("assets\\3.wav"))
				return -1;
			sound.setBuffer(buffer);

			// Çàãðóçêà òåêñòóðû ôîíà
			if (!m_textureBackground.loadFromFile("assets\\background.jpg"))
			{
				std::cout << "Error while loading background.jpg" << std::endl;
				return false;
			}
			m_spriteBackground.setTexture(m_textureBackground);

			// Çàãðóçêà øðèôòà
			if (!m_font.loadFromFile("assets\\AGENCYB.TTF"))
			{
				std::cout << "Error while loading AGENCYB.TTF" << std::endl;
				return false;
			}
			m_fpsText.setFont(m_font);

			// Ñîçäàíèå êîðàáëÿ èãðîêà
			if (!m_ship.Setup(100, 100))
				return false;

			srand(time(0));

			m_c = new mt::Circle[m_n];
			for (int i = 0; i < m_n; i++)
			{
				int r = rand() % 100 + 10;
				int x = rand() % (1000 - 2 * r) + r;
				int y = rand() % (600 - 2 * r) + r;
				int v = rand() % 50 + 100;
				float alfa = rand() % 7;
				m_c[i].Setup(x, y, r, v, alfa);
			}

			m_spaceObjects.push_back(new UFO);
			m_spaceObjects[0]->Setup(400, 400, 1, 0, "assets\\ufo.png", 1.0f);

			m_spaceObjects.push_back(new Destroyer);
			m_spaceObjects[1]->Setup(600, 600, 0, 1, "assets\\destroyer.png", 0.3f);

			m_spaceObjects.push_back(new Destroyer);
			m_spaceObjects[2]->Setup(900, 900, 0, 1, "assets\\destroyer.png", 0.3f);

			m_enemiesObjects.push_back(new Komet);
			m_enemiesObjects[0]->Setup(700, 700, -10, -10, "assets\\komet.png", 0.3f);

			m_enemiesObjects.push_back(new Meteorit);
			m_enemiesObjects[1]->Setup(1000, 500, -10, 10, "assets\\meteorit.png", 0.1f);
		}

		void TouchBorder(Circle& obj)
		{
			float x = obj.X();
			float y = obj.Y();
			float r = obj.R();

			//std::cout << x << " " << y << std::endl;

			if (isTouchBorder)
			{
				isTouchBorder = false;

				if (x + r >= m_width || x - r <= 0)
				{
					obj.Alfa(pi - obj.Alfa());
				}

				if (y + r >= m_height || y - r <= 0)
				{
					obj.Alfa(2 * pi - obj.Alfa());
				}

			}
			else
			{
				if (x + r + 20 <= m_width || x - r - 20 >= 0)
				{
					isTouchBorder = true;
				}

				if (y + r + 20 <= m_height || y - r - 20 >= 0)
				{
					isTouchBorder = true;
				}
			}

		}

		void Collision(int i)
		{
			Circle& c = m_c[i];
			float dist = sqrt(pow(m_ship.X() - c.X(), 2) + pow(m_ship.Y() - c.Y(), 2));
			if (m_ship.R() + c.R() >= dist)
			{
				std::cout << "Collision " << m_ship.V() << std::endl;
				isVisible = false;
			}
		}
		void Unable() {
			//clock_meteorit_1.restart();
			obj = m_enemiesObjects[1];
			m_enemiesObjects.erase(m_enemiesObjects.begin()+1);

		}
		void Able() {
			m_enemiesObjects.insert(m_enemiesObjects.begin() + 1, obj);

		}
		void LifeCycle()
		{
			sf::Clock clock;
			sf::Clock clock_meteorit;
			while (m_window.isOpen())
			{
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();
					if (event.type == sf::Event::TextEntered)
						if (static_cast<char>(event.text.unicode) == 't')
							sound.play();
				}
				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();
				// Îáðàáîòêà êëàâèàòóðû TODO
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					m_ship.setVelocity(1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					m_ship.setVelocity(-1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					m_ship.Rotate(-0.5);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					m_ship.Rotate(0.5);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (!m_ship.BulletAvailable())
						m_ship.Attack();
					destroyer.Attack();
				}
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					if (!m_pressedR)
					{
						m_pressedR = true;
						m_ship.BulletReset();
						ufo.Attack();
						sound.play();
					}
				}
				else
					m_pressedR = false;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
					if (!m_pressedQ) {
						m_pressedQ = true;
						int min_dist = 10000; int min_ind = 0;
						for (int i = 0; i < m_spaceObjects.size(); i++) {
							float dist = std::hypot(m_spaceObjects[i]->Get().getPosition().x - m_enemiesObjects[0]->Get().getPosition().x,
								m_spaceObjects[i]->Get().getPosition().y - m_enemiesObjects[0]->Get().getPosition().y);
							if (min_dist > dist) {
								min_dist = dist;
								min_ind = i;
							}
						}
						m_enemiesObjects[0]->SpecialAbility(m_spaceObjects[min_ind]->Get().getPosition().x, m_spaceObjects[min_ind]->Get().getPosition().y,
							m_enemiesObjects, flag_meteorit_visible, clock_meteorit, obj);
					}

				}
				else
					m_pressedQ = false;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && flag_meteorit_visible)
				{
					m_enemiesObjects[1]->SpecialAbility(0,0,m_enemiesObjects,flag_meteorit_visible,clock_meteorit,obj);
				}
				if (!flag_meteorit_visible && clock_meteorit.getElapsedTime().asSeconds() > 1) {
					m_enemiesObjects.insert(m_enemiesObjects.begin() + 1, obj);
					flag_meteorit_visible = true;
				}

				//float dt = clock.getElapsedTime().asSeconds();
				//clock.restart();
				// Ëîãèêà
				/*if (1 / fps > dt)
				{
					sf::Time t = sf::seconds(1 / fps - dt);
					sf::sleep(t);
				}*/
				//dt = clock.getElapsedTime().asSeconds();
				//clock.restart();

				// Ïåðåìåùåíèå øàðèêà

				//for (int i = 0; i < m_n; i++)
				//	TouchBorder(m_c[i]);

				for (int i = 0; i < m_n; i++)
				{
					float x = m_c[i].X();
					float y = m_c[i].Y();
					float r = m_c[i].R();
					float v = m_c[i].V();
					float alfa = m_c[i].Alfa();

					float x_s = x + v * cos(alfa) * dt;
					float y_s = y + v * sin(alfa) * dt;


					bool collision = false;
					if (x_s + r >= m_width)
					{
						m_c[i].Alfa(pi - m_c[i].Alfa());
						m_c[i].X(m_width - r);
						collision = true;
					}

					if (x_s - r <= 0)
					{
						m_c[i].Alfa(pi - m_c[i].Alfa());
						m_c[i].X(r);
						collision = true;
					}

					if (y_s + r >= m_height)
					{
						m_c[i].Alfa(2 * pi - m_c[i].Alfa());
						m_c[i].Y(m_height - r);
						collision = true;
					}

					if (y_s - r <= 0)
					{
						m_c[i].Alfa(2 * pi - m_c[i].Alfa());
						m_c[i].Y(r);
						collision = true;
					}

					if (!collision)
					{
						m_c[i].X(x_s);
						m_c[i].Y(y_s);
					}
				}

				//for (int i = 0; i < m_n; i++)
				//	m_c[i].Move(dt);

				//for (int i = 0; i < m_n; i++)
				//	Collision(i);

				// Ïåðåìåùåíèå êîðàáëÿ
				m_ship.Move(dt);

				for (int i = 0; i < m_spaceObjects.size(); i++)
				{
					m_spaceObjects[i]->Move(dt);
				}

				m_enemiesObjects[0]->Move(dt);
				if (m_enemiesObjects.size()>1)
				   m_enemiesObjects[1]->Move(dt);
				m_fpsText.setString(std::to_string(1 / dt));

				// Îòîáðàæåíèå
				m_window.clear();
				m_window.draw(m_spriteBackground);
				m_window.draw(m_fpsText);
				for (int i = 0; i < m_n; i++)
					m_window.draw(m_c[i].Get());

				//std::cout << m_ship.BulletAvailable() << std::endl;

				for (int i = 0; i < m_spaceObjects.size(); i++)
				{
					m_window.draw(m_spaceObjects[i]->Get());
				}
				for (int i = 0; i < m_enemiesObjects.size(); i++)
				{
					m_window.draw(m_enemiesObjects[i]->Get());
				}

				if (m_ship.BulletAvailable())
					m_window.draw(m_ship.GetBullet());
				if (isVisible)
					m_window.draw(m_ship.Get());
				m_window.display();
			}
		}
	};

}