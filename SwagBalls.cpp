#include "Game.h"

int main() {
    // Initialize random
    srand(static_cast<unsigned>(time(0)));

    // Init game obj
    Game game;

    // Game loop
    while(game.running()) {
        game.update();
        game.render();
    }

    return 0;
}