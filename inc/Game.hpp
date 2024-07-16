#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Asteroid.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "Enemies.hpp"
#include "Enemy1.hpp"
#include "Enemy2.hpp"
#include "Enemy3.hpp"
#include "Menu.hpp"

namespace msp {

    const float pi = acos(-1);

    class Game {
        int window_width;
        int window_height;
        std::string capture;
        sf::RenderWindow window;
        sf::Texture textureBackground;
        sf::Sprite spriteBackground;
        sf::Texture textureStation;
        sf::Sprite spriteStation;
        sf::Font font;
        sf::Text fpsText;
        sf::Text winText;
        sf::Text loseText;
        std::vector<sf::Text> healthText;
        Ship ship;
        Menu menu;
        bool menu_available = true;
        Enemy1 enemy1;
        Enemy2 enemy2;
        Enemy3 enemy3;
        Asteroid* asteroids; int count_asteroid;
        sf::Vector2f v_enemy1;
        sf::Vector2f v_enemy2;
        sf::Vector2f v_enemy3;
        sf::SoundBuffer buffer_win; sf::SoundBuffer buffer_lose; sf::SoundBuffer buffer_menu;
        sf::Sound sound_win; sf::Sound sound_lose; sf::Sound sound_menu;
        bool is_sound_win_play = false; bool is_sound_lose_play = false;
        bool once_is_sound_win_play = false; bool once_is_sound_lose_play = false;
        bool is_game_over_soon = false;
        int size_bullets = 100;
        int count_bullets = 0;
        Bullet* bullets = new Bullet[size_bullets];
        bool is_bullet_available = true;
        bool flag_meteorit_visible = true;
        std::vector<Enemies*> enemiesObjects;
        //std::vector<int> enemies_health = { 2,2,2 };
        std::vector<bool> collision_with_enemy = { false,false,false };
        std::vector<sf::Vector2f> v_enemy;
        bool is_lose = false; bool is_win = false;
        bool should_game_restart = false; bool once_should_game_restart = false;
        bool game_available = false;
        int level = 1; bool menu_level_available = false;
        int cur_button = -1;
    public:
        Game(const std::string& capture);
        ~Game();

        bool Setup();

        void Increase_size_bullets();
        bool Are_bullet_collision_with_enemy(Bullet& obj1, Enemies& obj2);
        bool Are_bullet_collision_with_asteroid(Bullet& obj1, Asteroid& obj2);
        bool Are_enemy_collision_with_statoin(Enemies& obj1);

        void Remove_enemies(int i);
        void Remove_bullet(int i) ;
        void Restart();


        void LifeCycle();


    };
}

