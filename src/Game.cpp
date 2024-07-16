#include <Game.hpp>

namespace msp {

    Game::Game(const std::string& capture) {
        this->capture = capture;
    }
    Game::~Game() {
        for (int i = 0; i < enemiesObjects.size(); i++)
            delete enemiesObjects[i];
        delete[] bullets;
        delete[] asteroids;
    }

    bool Game::Setup() {
        window_width = sf::VideoMode::getDesktopMode().width;
        window_height = sf::VideoMode::getDesktopMode().height;
        window.create(sf::VideoMode(window_width, window_height), capture);

        if (!menu.Setup()) {
            std::cerr << "Error while loading menu" << std::endl;
            return false;
        }

        if (!buffer_lose.loadFromFile("assets\\lose_game.flac")) {
            std::cerr << "Error while loading lose_game.flac" << std::endl;
            return false;
        }
        sound_lose.setBuffer(buffer_lose);
        if (!buffer_win.loadFromFile("assets\\win_game.wav")) {
            std::cerr << "Error while loading win_game.wav" << std::endl;
            return false;
        }
        sound_win.setBuffer(buffer_win);
        if (!buffer_menu.loadFromFile("assets\\menu_game.wav")) {
            std::cerr << "Error while loading menu_game.wav" << std::endl;
            return false;
        }
        sound_menu.setBuffer(buffer_menu);
        if (!textureBackground.loadFromFile("assets\\background.png")) {
            std::cerr << "Error while loading background.png" << std::endl;
            return false;
        }
        spriteBackground.setTexture(textureBackground);

        if (!textureStation.loadFromFile("assets\\station.png")) {
            std::cerr << "Error while loading station.png" << std::endl;
            return false;
        }
        spriteStation.setTexture(textureStation);
        spriteStation.setScale(0.25f, 0.25f);
        spriteStation.setOrigin(textureStation.getSize().x / 2, textureStation.getSize().y / 2);
        spriteStation.setPosition(window_width / 2, window_height / 2);
        count_asteroid = 3;
        if (!font.loadFromFile("assets\\Honk-Regular.ttf")) {
            std::cerr << "Error while loading Honk-Regular.ttf" << std::endl;
            return false;
        }
        healthText.resize(3);
        for (size_t i = 0; i < healthText.size(); i++) {
            healthText[i].setFont(font);
            healthText[i].setString("Health");
            healthText[i].setOrigin(healthText[i].getGlobalBounds().width / 2, healthText[i].getGlobalBounds().height / 2);
            healthText[i].setScale({ 0.7,0.7 });
        }
        fpsText.setFont(font);
        winText.setFont(font);
        winText.setString("You win");
        winText.setOrigin(winText.getGlobalBounds().width / 2, winText.getGlobalBounds().height / 2);
        winText.setPosition(window_width / 2, window_height / 2);
        winText.setScale({ 4,4 });
        loseText.setFont(font);
        loseText.setString("You lose");
        loseText.setOrigin(loseText.getGlobalBounds().width / 2, loseText.getGlobalBounds().height / 2);
        loseText.setPosition(window_width / 2, window_height / 2);
        loseText.setScale({ 4,4 });
        srand(time(0));
        asteroids = new Asteroid[count_asteroid];
        for (int i = 0; i < count_asteroid; i++)
        {
            int x = rand() % (window_width - 2 * 100) + 100;
            int y = rand() % (window_height - 2 * 100) + 100;
            asteroids[i].Setup(x, y);
        }



        if (!ship.Setup(window_width / 2, window_height / 2))
            return false;

        sf::Vector2f v1 = { spriteStation.getPosition().x - 50,(spriteStation.getPosition().y - 50) };
        sf::Vector2f v2 = { spriteStation.getPosition().x - (window_width - 50), spriteStation.getPosition().y - 50 };
        sf::Vector2f v3 = { spriteStation.getPosition().x - 50, spriteStation.getPosition().y - (window_height - 50) };
        float time = 10;
        sf::Vector2f v1_0 = v1 / time;
        sf::Vector2f v2_0 = v2 / time;
        sf::Vector2f v3_0 = v3 / time;
        long double pi = acos(-1);
        v_enemy = { v1_0 ,v2_0,v3_0 };


        enemiesObjects.push_back(new Enemy1);
        enemiesObjects[0]->Setup(50, 50, v_enemy[0].x, v_enemy[0].y, "assets\\enemy1.png", 0.2f);

        enemiesObjects.push_back(new Enemy2);
        enemiesObjects[1]->Setup(window_width - 50, 50, v_enemy[1].x, v_enemy[1].y, "assets\\enemy2.png", 0.2f);

        enemiesObjects.push_back(new Enemy3);
        enemiesObjects[2]->Setup(50, window_height - 50, v_enemy[2].x, v_enemy[2].y, "assets\\enemy3.png", 0.1f);

        return true;
    }

    void Game::Increase_size_bullets() {
        size_bullets = static_cast<int>(size_bullets * 1.5);
        Bullet* new_bullets = new Bullet[size_bullets];
        for (int i = 0; i < count_bullets; ++i) {
            new_bullets[i] = bullets[i];
        }
        delete[] bullets;
        bullets = new_bullets;
    }
    bool Game::Are_bullet_collision_with_enemy(Bullet& obj1, Enemies& obj2) {
        sf::FloatRect bounds_enemies = obj2.Get().getGlobalBounds();
        float width_enemy = bounds_enemies.width;
        float height_enemy = bounds_enemies.height;
        float center_x = bounds_enemies.left + width_enemy / 2;
        float center_y = bounds_enemies.top + height_enemy / 2;
        float hypot_enemy = std::hypot(width_enemy, height_enemy) / 2;
        float dist = std::hypot(obj1.Get().getPosition().x - obj2.Get().getPosition().x,
            obj1.Get().getPosition().y - obj2.Get().getPosition().y);
        return dist <= hypot_enemy + obj1.Get().getRadius();
    }
    bool Game::Are_bullet_collision_with_asteroid(Bullet& obj1, Asteroid& obj2) {
        sf::FloatRect bounds_asteroid = obj2.Get().getGlobalBounds();
        float width_asteroid = bounds_asteroid.width;
        float height_asteroid = bounds_asteroid.height;
        float center_x = bounds_asteroid.left + width_asteroid / 2;
        float center_y = bounds_asteroid.top + height_asteroid / 2;
        float hypot_asteroid = std::hypot(width_asteroid, height_asteroid) / 2;
        float dist = std::hypot(obj1.Get().getPosition().x - obj2.Get().getPosition().x,
            obj1.Get().getPosition().y - obj2.Get().getPosition().y);
        return dist <= hypot_asteroid + obj1.Get().getRadius();
    }
    bool Game::Are_enemy_collision_with_statoin(Enemies& obj1) {
        sf::FloatRect bounds_station = spriteStation.getGlobalBounds();
        float width_station = bounds_station.width;
        float height_station = bounds_station.height;
        float center_x_station = bounds_station.left + width_station / 2;
        float center_y_station = bounds_station.top + height_station / 2;
        float hypot_station = std::hypot(width_station, height_station) / 2;
        sf::FloatRect bounds_enemies = obj1.Get().getGlobalBounds();
        float width_enemy = bounds_enemies.width;
        float height_enemy = bounds_enemies.height;
        float center_x_enemy = bounds_enemies.left + width_enemy / 2;
        float center_y_enenmy = bounds_enemies.top + height_enemy / 2;
        float hypot_enemy = std::hypot(width_enemy, height_enemy) / 2;
        float dist = std::hypot(spriteStation.getPosition().x - obj1.Get().getPosition().x,
            spriteStation.getPosition().y - obj1.Get().getPosition().y);
        return dist <= hypot_enemy + hypot_station;
    }

    void Game::Remove_enemies(int i) {
        if (i >= 0 && i < enemiesObjects.size()) {
            delete enemiesObjects[i];
            enemiesObjects.erase(enemiesObjects.begin() + i);
            collision_with_enemy.erase(collision_with_enemy.begin() + i);
            v_enemy.erase(v_enemy.begin() + i);
            healthText.erase(healthText.begin() + i);
        }
    }
    void Game::Remove_bullet(int i) {
        if (i >= 0 && i < count_bullets) {
            for (int j = i; j < count_bullets - 1; j++) {
                bullets[j] = bullets[j + 1];
            }
            count_bullets--;
        }
    }
    void Game::Restart() {
        //menu_available = true;
        is_sound_win_play = false; is_sound_lose_play = false;
        once_is_sound_win_play = false; once_is_sound_lose_play = false;
        is_game_over_soon = false;
        size_bullets = 100;
        count_bullets = 0;
        is_bullet_available = true;
        flag_meteorit_visible = true;
        //std::vector<int> enemies_health = { 2,2,2 };
        collision_with_enemy = { false,false,false };
        is_lose = false; is_win = false;
        should_game_restart = false; once_should_game_restart = false;
        game_available = false;
        level = 1; menu_level_available = false;
        cur_button = -1;
        count_bullets = 0;
        delete[] bullets;
        bullets = new Bullet[size_bullets];
        flag_meteorit_visible = true;
        count_asteroid = 3;
        delete[] asteroids;
        asteroids = new Asteroid[count_asteroid];
        for (int i = 0; i < count_asteroid; i++) {
            int x = rand() % (window_width - 2 * 100) + 100;
            int y = rand() % (window_height - 2 * 100) + 100;
            asteroids[i].Setup(x, y);
        }

        ship.Setup(window_width / 2, window_height / 2);
        for (int i = 0; i < enemiesObjects.size(); i++)
            delete enemiesObjects[i];
        enemiesObjects.clear();
        sf::Vector2f v1 = { spriteStation.getPosition().x - 50,(spriteStation.getPosition().y - 50) };
        sf::Vector2f v2 = { spriteStation.getPosition().x - (window_width - 50), spriteStation.getPosition().y - 50 };
        sf::Vector2f v3 = { spriteStation.getPosition().x - 50, spriteStation.getPosition().y - (window_height - 50) };
        float time = 20;
        sf::Vector2f v1_0 = v1 / time;
        sf::Vector2f v2_0 = v2 / time;
        sf::Vector2f v3_0 = v3 / time;
        v_enemy = { v1_0 ,v2_0,v3_0 };
        collision_with_enemy = { false, false, false };
        healthText.clear();

        enemiesObjects.push_back(new Enemy1);
        enemiesObjects[0]->Setup(50, 50, v_enemy[0].x, v_enemy[0].y, "assets\\enemy1.png", 0.2f);

        enemiesObjects.push_back(new Enemy2);
        enemiesObjects[1]->Setup(window_width - 50, 50, v_enemy[1].x, v_enemy[1].y, "assets\\enemy2.png", 0.2f);

        enemiesObjects.push_back(new Enemy3);
        enemiesObjects[2]->Setup(50, window_height - 50, v_enemy[2].x, v_enemy[2].y, "assets\\enemy3.png", 0.1f);
        healthText.resize(enemiesObjects.size());
        for (size_t i = 0; i < healthText.size(); i++) {
            healthText[i].setFont(font);
            healthText[i].setString("Health");
            healthText[i].setOrigin(healthText[i].getGlobalBounds().width / 2, healthText[i].getGlobalBounds().height / 2);
            healthText[i].setScale({ 0.7, 0.7 });
        }
    }


    void Game::LifeCycle() {
        window.setVerticalSyncEnabled(true);
        sf::Clock clock;
        sf::Clock clock_fps;
        sf::Clock clock_game_end;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (menu_available) {
                    if (event.type == sf::Event::Resized) {
                        sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                        window.setView(sf::View(visibleArea));
                    }
                    if (event.type == sf::Event::KeyPressed) {
                        switch (event.key.code) {
                        case sf::Keyboard::Up:
                            menu.Move_up(game_available);
                            sound_menu.play();
                            break;
                        case sf::Keyboard::Down:
                            menu.Move_down(game_available);
                            sound_menu.play();
                            break;
                        case sf::Keyboard::Enter:
                            if (menu.Get_current_button_colour() == sf::Color::Green) {
                                if (game_available) {
                                    switch (menu.Get_current_button()) {
                                    case 0:
                                        menu_available = false;
                                        sound_menu.play();
                                        break;
                                    case 1:
                                        Restart();
                                        menu_available = false;
                                        sound_menu.play();
                                        break;
                                    case 2:
                                        menu_level_available = true;
                                        menu_available = false;
                                        sound_menu.play();
                                        break;
                                    case 3:
                                        sound_menu.play();
                                        window.close();
                                        break;
                                    }
                                }
                                else {
                                    switch (menu.Get_current_button()) {
                                    case 1:
                                        menu_available = false;
                                        sound_menu.play();
                                        break;
                                    case 2:
                                        sound_menu.play();
                                        menu_level_available = true;
                                        menu_available = false;
                                        break;
                                    case 3:
                                        sound_menu.play();
                                        window.close();
                                        break;
                                    }

                                }
                            }
                            break;
                        }
                    }
                    if (event.type == sf::Event::MouseMoved) {
                        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

                        for (int i = 0 + !game_available; i < menu.Get_button_count(); i++) {
                            if (menu.Is_mouse_over_button(mouse_position, i)) {
                                menu.Set_button_colour(i, sf::Color::Green);
                                if (menu.Get_current_button() != i) {
                                    menu.Set_current_button(i);
                                    sound_menu.play();
                                }
                            }
                            else {
                                if (menu.Get_current_button() != i) {
                                    menu.Set_button_colour(i, sf::Color::White);
                                }
                            }
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            if (menu.Get_current_button_colour() == sf::Color::Green) {
                                if (game_available) {
                                    switch (menu.Get_current_button()) {
                                    case 0:
                                        menu_available = false;
                                        sound_menu.play();
                                        break;
                                    case 1:
                                        Restart();
                                        menu_available = false;
                                        sound_menu.play();
                                        break;
                                    case 2:
                                        menu_level_available = true;
                                        menu_available = false;
                                        sound_menu.play();
                                        break;
                                    case 3:
                                        sound_menu.play();
                                        window.close();
                                        break;
                                    }
                                }
                                else {
                                    switch (menu.Get_current_button()) {
                                    case 1:
                                        menu_available = false;
                                        sound_menu.play();
                                        break;
                                    case 2:
                                        sound_menu.play();
                                        menu_level_available = true;
                                        menu_available = false;
                                        break;
                                    case 3:
                                        sound_menu.play();
                                        window.close();
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                else if (menu_level_available) {
                    if (event.type == sf::Event::KeyPressed) {
                        switch (event.key.code) {
                        case sf::Keyboard::Up:
                            menu.Move_up_level();
                            sound_menu.play();
                            break;
                        case sf::Keyboard::Down:
                            menu.Move_down_level();
                            sound_menu.play();
                            break;
                        case sf::Keyboard::Enter:
                            if (menu.Get_current_level_button_colour() == sf::Color::Green) {
                                switch (menu.Get_current_level_button()) {
                                case 0:
                                    level = 1;
                                    menu_level_available = false;
                                    sound_menu.play();
                                    break;
                                case 1:
                                    level = 2;
                                    menu_level_available = false;
                                    sound_menu.play();
                                    break;
                                case 2:
                                    level = 3;
                                    menu_level_available = false;
                                    sound_menu.play();
                                    break;
                                case 3:
                                    level = 4;
                                    menu_level_available = false;
                                    sound_menu.play();
                                    break;
                                case 4:
                                    level = 5;
                                    menu_level_available = false;
                                    sound_menu.play();
                                    break;
                                case 5:
                                    menu_level_available = false;
                                    menu_available = true;
                                    sound_menu.play();
                                    break;
                                }
                            }
                            break;
                        case sf::Keyboard::Escape:
                            sound_menu.play();
                            menu_level_available = false;
                            menu_available = true;
                            break;
                        }
                    }
                    if (event.type == sf::Event::MouseMoved) {
                        sf::Vector2i mouse_level_position = sf::Mouse::getPosition(window);

                        for (int i = 0; i < menu.Get_level_button_count(); i++) {
                            if (menu.Is_mouse_over_level_button(mouse_level_position, i)) {
                                menu.Set_level_button_colour(i, sf::Color::Green);
                                if (menu.Get_current_level_button() != i) {
                                    menu.Set_level_current_button(i);
                                    sound_menu.play();
                                }
                            }
                            else {
                                if (menu.Get_current_level_button() != i) {
                                    menu.Set_level_button_colour(i, sf::Color::White);
                                }
                            }
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            if (menu.Get_current_level_button_colour() == sf::Color::Green) {
                                switch (menu.Get_current_level_button()) {
                                case 0:
                                    level = 1;
                                    menu_level_available = false;
                                    sound_menu.play();
                                    break;
                                case 1:
                                    level = 2;
                                    menu_level_available = false;
                                    sound_menu.play();
                                    break;
                                case 2:
                                    level = 3;
                                    menu_level_available = false;
                                    sound_menu.play();
                                    break;
                                case 3:
                                    level = 4;
                                    menu_level_available = false;
                                    sound_menu.play();
                                    break;
                                case 4:
                                    level = 5;
                                    menu_level_available = false;
                                    sound_menu.play();
                                    break;
                                case 5:
                                    menu_level_available = false;
                                    menu_available = true;
                                    sound_menu.play();
                                    break;
                                }
                            }
                        }
                    }

                }
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        menu_available = true;
                        sound_menu.play();
                    }
                }
            }

            float dt = clock.restart().asSeconds();
            if (!(menu_available || menu_level_available)) {
                game_available = true;

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    ship.setVelocity(100, dt);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    ship.setVelocity(-100, dt);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    ship.Rotate(-250, dt);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    ship.Rotate(250, dt);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    if (is_bullet_available) {
                        if (count_bullets == size_bullets) {
                            Increase_size_bullets();
                        }
                        bullets[count_bullets].Setup(
                            ship.Get().getPosition().x,
                            ship.Get().getPosition().y,
                            5,
                            ship.V() + 30,
                            ship.Alpha()
                        );
                        count_bullets++;
                        is_bullet_available = false;
                    }
                }
                else {
                    is_bullet_available = true;
                }

                ship.Move(dt);
                for (int i = 0; i < count_bullets; i++) {
                    bullets[i].setVelocity(1000 / level, dt);
                    bullets[i].Move(dt);
                }

                for (auto& enemy : enemiesObjects) {
                    enemy->Move(dt);
                }

                if (clock_fps.getElapsedTime().asSeconds() > 1) {
                    fpsText.setString(std::to_string(1 / dt));
                    clock_fps.restart();
                }

                for (size_t i = 0; i < enemiesObjects.size(); i++) {
                    bool flag = false;
                    for (size_t j = 0; j < count_bullets; j++) {
                        if (Are_bullet_collision_with_enemy(bullets[j], *enemiesObjects[i])) {
                            flag = true;
                            Remove_bullet(j);
                            if (!collision_with_enemy[i]) {
                                enemiesObjects[i]->Health(level);
                                collision_with_enemy[i] = true;
                            }
                        }
                    }
                    if (!flag) {
                        collision_with_enemy[i] = false;
                    }
                }

                for (int i = 0; i < count_asteroid; i++) {
                    for (int j = 0; j < count_bullets; j++) {
                        if (Are_bullet_collision_with_asteroid(bullets[j], asteroids[i])) {
                            Remove_bullet(j);
                            j--;
                            if (!enemiesObjects.empty()) {
                                int rand = std::rand() % enemiesObjects.size();
                                enemiesObjects[rand]->SpecialAbility();
                            }
                        }
                    }
                }

                for (int i = 0; i < count_bullets; i++) {
                    if (bullets[i].Get().getPosition().x < -50 ||
                        bullets[i].Get().getPosition().x > window_width + 50 ||
                        bullets[i].Get().getPosition().y < -50 ||
                        bullets[i].Get().getPosition().y > window_height + 50) {
                        Remove_bullet(i);
                        i--;
                    }
                }

                for (size_t i = 0; i < enemiesObjects.size();) {
                    if (enemiesObjects[i]->Get_health() <= 0) {
                        Remove_enemies(i);
                    }
                    else {
                        i++;
                    }
                }

                for (size_t i = 0; i < enemiesObjects.size(); i++) {
                    if (Are_enemy_collision_with_statoin(*enemiesObjects[i])) {
                        is_lose = true;
                    }
                }

                if (enemiesObjects.empty()) {
                    is_win = true;
                }

                window.clear();
                window.draw(spriteBackground);
                if (!(is_win || is_lose) && !is_game_over_soon) {
                    window.draw(spriteStation);
                    for (int i = 0; i < count_asteroid; i++) {
                        window.draw(asteroids[i].Get());
                    }
                    window.draw(fpsText);
                    for (size_t i = 0; i < enemiesObjects.size(); i++) {
                        window.draw(enemiesObjects[i]->Get());
                        float healthText_x = enemiesObjects[i]->Get().getPosition().x;
                        float healthText_y = enemiesObjects[i]->Get().getPosition().y + enemiesObjects[i]->Get().getGlobalBounds().height / 2 + 10;
                        healthText[i].setPosition(healthText_x, healthText_y);
                        healthText[i].setString(std::to_string(enemiesObjects[i]->Get_health()));
                        window.draw(healthText[i]);
                    }
                    for (int i = 0; i < count_bullets; i++) {
                        window.draw(bullets[i].Get());
                    }
                    window.draw(ship.Get());
                }
                else {
                    if (is_win) {
                        window.draw(winText);
                        is_sound_win_play = true;
                    }
                    else if (is_lose) {
                        window.draw(loseText);
                        is_sound_lose_play = true;
                    }
                    should_game_restart = true;
                }

                if (is_sound_win_play && !once_is_sound_win_play) {
                    is_sound_win_play = false;
                    sound_win.play();
                    once_is_sound_win_play = true;
                    //once_should_game_restart = true;
                }

                else if (is_sound_lose_play && !once_is_sound_lose_play) {
                    std::cout << "asad" << std::endl;
                    is_sound_lose_play = false;
                    once_is_sound_lose_play = true;
                    sound_lose.play();
                    //once_should_game_restart = true;
                }

                if (should_game_restart && !once_should_game_restart) {
                    std::cout << "vdad" << std::endl;
                    clock_game_end.restart();
                    once_should_game_restart = true;
                }

                if (clock_game_end.getElapsedTime().asSeconds() > 0.7 && should_game_restart) {
                    menu_available = true;
                    is_win = false;
                    is_lose = false;
                    should_game_restart = false;
                    once_should_game_restart = false;
                    game_available = false;
                    Restart();
                }
            }

            if (menu_available) {
                menu.Draw_background_menu(window);
                menu.Draw_buttons(window, game_available);
            }
            if (menu_level_available) {
                menu.Draw_background_menu(window);
                menu.Draw_level_buttons(window);
            }
            window.display();
        }
    }
}

