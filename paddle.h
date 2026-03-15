#pragma once
#include <bits/stdc++.h>
#include "screen.h"

class Paddle{
    private:
        size_t height;
        size_t posX, posY;

    public:
        Paddle(){
            height = 0;
            posX = 0;
            posY = 0;
        }
        Paddle(size_t arenaHeight, size_t posX = 0){
            height = arenaHeight / 2;
            posY = arenaHeight / 3.5;
            this->posX = posX; 
        }
        bool isPaddle(size_t posY, size_t posX){
            return this->posX == posX && posY >= this->posY && posY < this->posY + height; 
        }
};