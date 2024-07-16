#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#define max_buttons 4
#define max_level_buttons 6

namespace msp {
    class Menu {
        int window_width;
        int window_height;
        sf::Texture textureBackground;
        sf::Sprite spriteBackground;
        sf::Font font;
        sf::Text buttons[max_buttons];
        sf::Text level_buttons[max_level_buttons];
        int current_button;
        int current_level_button;

    public:
        bool Setup();
        void Move_up(bool game_available);
        void Move_up_level();
        void Move_down(bool game_available);
        void Move_down_level();
        void Draw_buttons(sf::RenderWindow& window, bool game_available);
        void Draw_level_buttons(sf::RenderWindow& window);
        void Draw_background_menu(sf::RenderWindow& window);
        int Get_current_button();
        sf::Color Get_current_button_colour();
        sf::Color Get_current_level_button_colour();
        int Get_button_count();
        bool Is_mouse_over_button(sf::Vector2i mouse_position, int button_index);
        void Set_button_colour(int button_index, sf::Color color);
        void Set_current_button(int button_index);
        int Get_current_level_button();
        void Set_level_current_button(int level_button_index);
        void Set_level_button_colour(int level_button_index, sf::Color color);
        bool Is_mouse_over_level_button(sf::Vector2i mouse_position, int level_button_index);
        int Get_level_button_count();
    };
}

