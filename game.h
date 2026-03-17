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
        size_t player1_points, player2_points;
        Arena *arena;
        Paddle paddle1;
        Paddle paddle2;
        Ball ball;

    public:
        Game(){
            left = true;
            down = true;
            player1_points = 0;
            player2_points = 0;
            arena = new Arena();
            paddle1 = Paddle();
            paddle2 = Paddle();
            ball = Ball();
        }
        Game(Arena *arena){
            left = true;
            down = true;
            player1_points = 0;
            player2_points = 0;
            this->arena = arena;
            this->paddle1 = Paddle(arena->getHeight(), 0);
            this->paddle2 = Paddle(arena->getHeight(), arena->getWidth() - 1);
            this->ball = Ball(arena->getHeight(), arena->getWidth() - 1);
        }

        void update(){
            updateFrame();
            clearFrame();
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
        void renderFrame() const{
            for(size_t i = 0; i < arena->getFrame().size(); i++){
                for(size_t j = 0; j < arena->getFrame()[i].size(); j++)
                    std::cout << arena->getFrame()[i][j];
                std::cout << std::endl;
            }
        }
        void clearFrame(){
            std::cout << "\033[2J\033[H";
        }
        
        void build_border(){
            std::cout << std::string(arena->getWidth(), '=') << std::endl;
        }
        void print_info(){
            std::cout << " Controls: W/S (Up/Down) | Press 'q' to Exit | player1 " << player1_points << " - " << player2_points << " player2" << std::endl;
        }
        void printFrame(){
            build_border();
            renderFrame();
            build_border();
            print_info();
        }
        
        void moveBall(){
            if(ball.getPosX() < 1){ 
                player1_points++;
                ball.setPosX(arena->getWidth()/2);
                ball.setPosY(arena->getHeight()/2);
                paddle1.setPosY(arena->getHeight()/3.5);
                paddle2.setPosY(arena->getHeight()/3.5);

            }
            if(ball.getPosX() > arena->getWidth()) {
                player2_points++;
                ball.setPosX(arena->getWidth()/2);
                ball.setPosY(arena->getHeight()/2);
                paddle1.setPosY(arena->getHeight()/3.5);
                paddle2.setPosY(arena->getHeight()/3.5);
            }
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
        void movePlayerPaddleUp(){
            paddle1.movePaddleUp();
        }
        void movePlayerPaddleDown(){
            paddle1.movePaddleDown();
        }
        void movePaddleBot(){
            srand(time(0));

            double chance = rand() % 100;
            
            if(chance < 30){
                if(ball.getPosY() < paddle2.getPosY()){
                    paddle2.movePaddleUp();
                }
                else if(ball.getPosY() > paddle2.getPosY() + paddle2.getHeight() - 1){
                    paddle2.movePaddleDown();
                }
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