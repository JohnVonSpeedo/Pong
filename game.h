#pragma once
#include<bits/stdc++.h>
#include "arena.h"
#include "paddle.h"
#include "ball.h"

class Game{
    private:
        bool left, down;
        Arena *arena;
        Paddle paddle1;
        Paddle paddle2;
        Ball ball;

    public:
        Game(){
            left = true;
            down = true;
            arena = new Arena();
            paddle1 = Paddle();
            paddle2 = Paddle();
            ball = Ball();
        }

        Game(Arena *arena){
            left = true;
            down = true;
            this->arena = arena;
            this->paddle1 = Paddle(arena->getHeight(), 0);
            this->paddle2 = Paddle(arena->getHeight(), arena->getWidth() - 1);
            this->ball = Ball(arena->getHeight(), arena->getWidth() - 1);
        }

        void updateFrame(){
            for(size_t i = 0; i < arena->getFrame().size(); i++){
                for(size_t j = 0; j < arena->getFrame()[i].size(); j++){
                    if(paddle1.isPaddle(i, j) || paddle2.isPaddle(i, j))
                        arena->getFrame()[i][j] = '0';
                    else if(ball.isBall(i, j))
                        arena->getFrame()[i][j] = '0';
                    else
                        arena->getFrame()[i][j] = '-';
                }
            }
        }
        void drawFrame(){
            for(size_t i = 0; i < arena->getFrame().size(); i++){
                for(size_t j = 0; j < arena->getFrame()[i].size(); j++)
                    std::cout << arena->getFrame()[i][j];
                std::cout << std::endl;
            }
        }
        void moveBall(){
            if(ball.getPosX() == 1 && arena->getFrame()[ball.getPosY()][ball.getPosX() - 1] == '0') left = false;
            if(ball.getPosX() == arena->getWidth() - 2 && arena->getFrame()[ball.getPosY()][ball.getPosX() + 1] == '0') left = true;
            if(ball.getPosY() == 0) down = true;
            if(ball.getPosY() == arena->getHeight() - 1) down = false;
            if(left && down){
                ball.moveDown();
                ball.moveLeft();
            }
            else if(!left && down){
                ball.moveDown();
                ball.moveRigth();
            }
            else if(left && !down){
                ball.moveUp();
                ball.moveLeft();
            }
            else{
                ball.moveUp();
                ball.moveRigth();
            }
        }
};