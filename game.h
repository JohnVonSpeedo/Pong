#pragma once
#include <bits/stdc++.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
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
                        arena->getFrame()[i][j] = ball.getSkin();
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
        void clearFrame(){
            std::cout << "\033[2J\033[H";
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
        void build_border(){
            std::cout << std::string(arena->getWidth(), '=') << std::endl;
        }
        void print_info(){
            std::cout << " Controls: W/S (Up/Down) | Press 'q' to Exit" << std::endl;
        }
        void movePlayerPaddleUp(){
            paddle1.movePaddleUp();
        }
        void movePlayerPaddleDown(){
            paddle1.movePaddleDown();
        }

        void movePaddleBot(){
            if(ball.getPosY() < paddle2.getPosY()){
                paddle2.movePaddleUp();
            }
            else if(ball.getPosY() > paddle2.getPosY() + paddle2.getHeight() - 1){
                paddle2.movePaddleDown();
            }
        }
        void setBallSkin(char c){
            this->ball.setSkin(c);
        }
        char getKeyPress() {
            struct termios oldt, newt;
            char ch;
            int oldf;

            // Get current terminal settings
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;

            // Disable line buffering and echo
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);

            // Make read() non-blocking
            oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
            fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

            // Try to read a character
            ch = getchar();

            // Restore terminal settings
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            fcntl(STDIN_FILENO, F_SETFL, oldf);

            return ch;
        }
};