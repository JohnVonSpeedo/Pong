#include<bits/stdc++.h>
#include "game.h"

int main(){
    Screen screen(15, 30);
    Arena *arena = new Arena(screen);
    Game game(arena);
    game.updateFrame();
    game.drawFrame();
    for(size_t i = 0; i < 40; i++){
        std::cout << std::endl;
        game.moveBall();
        game.updateFrame();
        game.drawFrame();
    }

    delete arena;
    return 0;
}