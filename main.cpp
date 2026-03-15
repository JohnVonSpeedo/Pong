#include <bits/stdc++.h>
#include "game.h"

int main(){
    long long gameCounter = 0;
    Screen screen(15, 50);
    Arena arena(screen);
    Game game(&arena);

    const int FPS = 30;
    const std::chrono::milliseconds frameDuration(1000 / FPS);

    while(true){
        auto frameStart = std::chrono::high_resolution_clock::now();

        game.updateFrame();
        game.moveBall();

        std::cout << "\033[2J\033[H";

        game.drawFrame();

        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto elapsed = frameEnd - frameStart;
        if (elapsed < frameDuration) 
            std::this_thread::sleep_for(frameDuration - elapsed);
    }

    return 0;
}