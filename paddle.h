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
        
        size_t getPosX(){
            return posX;
        }
        size_t getPosY(){
            return posY;
        }
        size_t getHeight(){
            return height;
        }
        
        void setPosY(size_t posY){
            this->posY = posY;
        }
        
        void movePaddleUp(){
            if(this->getPosY() > 0)
                posY--;
        }
        void movePaddleDown(){
            if(this->getPosY() < height + 1)
                posY++;
        }
};