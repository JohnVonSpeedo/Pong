#pragma once
#include <bits/stdc++.h>
#include "screen.h"

class Arena{
    private:
        size_t height, width;
        std::vector<std::vector<char>> frame;

    public:
        Arena():
        height(0),
        width(0),
        frame(){}
        
        Arena(Screen screen) : 
        height(screen.getHeight()), 
        width(screen.getWidth()), 
        frame(height, std::vector<char>(width, '-')){}

        size_t getHeight(){
            return height;
        }

        size_t getWidth(){
            return width;
        }

        std::vector<std::vector<char>>& getFrame(){
            return frame;
        }
};