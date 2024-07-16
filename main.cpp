#include <SFML/Graphics.hpp>
#include <Game.hpp>

int main()
{
    msp::Game game("SFML_enemies");

    if (!game.Setup())
        return -1;

    game.LifeCycle();

    return 0;
}