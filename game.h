#pragma once
#include<bits/stdc++.h>
#include "arena.h"
#include "paddle.h"
#include "ball.h"

class Game{
    private:
        Arena *arena;
        Paddle paddle1;
        Paddle paddle2;
        Ball ball;

    public:
        Game(){
            arena = new Arena();
            paddle1 = Paddle();
            paddle2 = Paddle();
            ball = Ball();
        }

        Game(Arena *arena){
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
};