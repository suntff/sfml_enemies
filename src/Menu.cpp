#include "Menu.hpp"

namespace msp {
    bool Menu::Setup() {
        window_width = sf::VideoMode::getDesktopMode().width;
        window_height = sf::VideoMode::getDesktopMode().height;

        if (!textureBackground.loadFromFile("assets/background_menu.jpg")) {
            std::cerr << "Error while loading background_menu.jpg" << std::endl;
            return false;
        }
        spriteBackground.setTexture(textureBackground);

        if (!font.loadFromFile("assets/Honk-Regular.ttf")) {
            std::cerr << "Error while loading Honk-Regular.ttf" << std::endl;
            return false;
        }

        buttons[0].setFont(font);
        buttons[0].setFillColor(sf::Color::White);
        buttons[0].setString("Continue");
        buttons[0].setPosition(window_width / 2, window_height / (max_buttons + 1) * 1);

        buttons[1].setFont(font);
        buttons[1].setFillColor(sf::Color::White);
        buttons[1].setString("New game");
        buttons[1].setPosition(window_width / 2, window_height / (max_buttons + 1) * 2);

        buttons[2].setFont(font);
        buttons[2].setFillColor(sf::Color::White);
        buttons[2].setString("Levels");
        buttons[2].setPosition(window_width / 2, window_height / (max_buttons + 1) * 3);

        buttons[3].setFont(font);
        buttons[3].setFillColor(sf::Color::White);
        buttons[3].setString("Exit");
        buttons[3].setPosition(window_width / 2, window_height / (max_buttons + 1) * 4);

        current_button = max_buttons - 1;

        level_buttons[0].setFont(font);
        level_buttons[0].setFillColor(sf::Color::White);
        level_buttons[0].setString("1");
        level_buttons[0].setPosition(window_width / 2, window_height / (max_level_buttons + 1) * 1);

        level_buttons[1].setFont(font);
        level_buttons[1].setFillColor(sf::Color::White);
        level_buttons[1].setString("2");
        level_buttons[1].setPosition(window_width / 2, window_height / (max_level_buttons + 1) * 2);

        level_buttons[2].setFont(font);
        level_buttons[2].setFillColor(sf::Color::White);
        level_buttons[2].setString("3");
        level_buttons[2].setPosition(window_width / 2, window_height / (max_level_buttons + 1) * 3);

        level_buttons[3].setFont(font);
        level_buttons[3].setFillColor(sf::Color::White);
        level_buttons[3].setString("4");
        level_buttons[3].setPosition(window_width / 2, window_height / (max_level_buttons + 1) * 4);

        level_buttons[4].setFont(font);
        level_buttons[4].setFillColor(sf::Color::White);
        level_buttons[4].setString("5");
        level_buttons[4].setPosition(window_width / 2, window_height / (max_level_buttons + 1) * 5);

        level_buttons[5].setFont(font);
        level_buttons[5].setFillColor(sf::Color::White);
        level_buttons[5].setString("Come back");
        level_buttons[5].setPosition(window_width / 2, window_height / (max_level_buttons + 1) * 6);

        current_level_button = max_level_buttons - 1;

        return true;
    }

    void Menu::Move_up(bool game_available) {
        buttons[current_button].setFillColor(sf::Color::White);
        int min_button = game_available ? 0 : 1;
        if (current_button - 1 >= min_button) {
            current_button--;
        }
        else {
            current_button = max_buttons - 1;
        }
        buttons[current_button].setFillColor(sf::Color::Green);
    }

    void Menu::Move_up_level() {
        level_buttons[current_level_button].setFillColor(sf::Color::White);
        if (current_level_button - 1 >= 0) {
            current_level_button--;
        }
        else {
            current_level_button = max_level_buttons - 1;
        }
        level_buttons[current_level_button].setFillColor(sf::Color::Green);
    }

    void Menu::Move_down(bool game_available) {
        buttons[current_button].setFillColor(sf::Color::White);
        int min_button = game_available ? 0 : 1;
        if (current_button + 1 < max_buttons) {
            current_button++;
        }
        else {
            current_button = min_button;
        }
        buttons[current_button].setFillColor(sf::Color::Green);
    }

    void Menu::Move_down_level() {
        level_buttons[current_level_button].setFillColor(sf::Color::White);
        if (current_level_button + 1 < max_level_buttons) {
            current_level_button++;
        }
        else {
            current_level_button = 0;
        }
        level_buttons[current_level_button].setFillColor(sf::Color::Green);
    }

    void Menu::Draw_buttons(sf::RenderWindow& window, bool game_available) {
        if (game_available) {
            window.draw(buttons[0]);
        }
        for (int i = 1; i < max_buttons; i++) {
            window.draw(buttons[i]);
        }
    }

    void Menu::Draw_level_buttons(sf::RenderWindow& window) {
        for (int i = 0; i < max_level_buttons; i++) {
            window.draw(level_buttons[i]);
        }
    }

    void Menu::Draw_background_menu(sf::RenderWindow& window) {
        window.draw(spriteBackground);
    }

    int Menu::Get_current_button() {
        return current_button;
    }

    sf::Color Menu::Get_current_button_colour() {
        return buttons[current_button].getFillColor();
    }

    sf::Color Menu::Get_current_level_button_colour() {
        return level_buttons[current_level_button].getFillColor();
    }

    int Menu::Get_button_count() {
        return max_buttons;
    }

    bool Menu::Is_mouse_over_button(sf::Vector2i mouse_position, int button_index) {
        sf::FloatRect button_bounds = buttons[button_index].getGlobalBounds();
        return button_bounds.contains(static_cast<sf::Vector2f>(mouse_position));
    }

    void Menu::Set_button_colour(int button_index, sf::Color color) {
        buttons[button_index].setFillColor(color);
    }

    void Menu::Set_current_button(int button_index) {
        current_button = button_index;
    }

    int Menu::Get_current_level_button() {
        return current_level_button;
    }

    void Menu::Set_level_current_button(int level_button_index) {
        current_level_button = level_button_index;
    }

    void Menu::Set_level_button_colour(int level_button_index, sf::Color color) {
        level_buttons[level_button_index].setFillColor(color);
    }

    bool Menu::Is_mouse_over_level_button(sf::Vector2i mouse_position, int level_button_index) {
        sf::FloatRect level_button_bounds = level_buttons[level_button_index].getGlobalBounds();
        return level_button_bounds.contains(static_cast<sf::Vector2f>(mouse_position));
    }

    int Menu::Get_level_button_count() {
        return max_level_buttons;
    }
}

