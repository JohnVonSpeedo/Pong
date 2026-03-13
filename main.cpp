#include<bits/stdc++.h>
#include "game.h"

int main(){
    Screen screen(15, 80);
    Arena *arena = new Arena(screen);
    Game game(arena);
    game.updateFrame();
    game.drawFrame();
    delete arena;
    return 0;
}