#include <bits/stdc++.h>
#include "game.h"

int main(){
    Screen screen(15, 50);
    Arena arena(screen);
    Game game(&arena);

    const int FPS = 15;
    const std::chrono::milliseconds frameDuration(1000 / FPS);

    while(true){
        auto frameStart = std::chrono::high_resolution_clock::now();

        char key = game.getKeyPress();
        if (key == 'q'){ 
            std::system("clear");
            break;
        }

        game.updateFrame();
        game.moveBall();

        game.clearFrame();

        game.build_border();
        game.drawFrame();
        game.build_border();
        game.print_info();


        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto elapsed = frameEnd - frameStart;
        if (elapsed < frameDuration) {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
    }

    return 0;
}