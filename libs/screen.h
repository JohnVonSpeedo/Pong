#pragma once
#include <bits/stdc++.h>

class Screen{
    private:
        size_t height;
        size_t width;

    public:
        Screen(size_t height = 0, size_t width = 0){
            this->height = height;
            this->width = width;
        }

        int getHeight(){
            return height;
        }
        int getWidth(){
            return width;
        }
};