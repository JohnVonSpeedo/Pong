#include<bits/stdc++.h>

class Ball{
    private:
        size_t posX;
        size_t posY;
    public:
        Ball() :
        posX(0),
        posY(0) {}

        Ball(size_t arenaHeight, size_t arenaWidth) :
        posX(arenaWidth/2),
        posY(arenaHeight/2){}

        bool isBall(size_t posY, size_t posX){
            return this->posX == posX && this->posY == posY;
        }
};