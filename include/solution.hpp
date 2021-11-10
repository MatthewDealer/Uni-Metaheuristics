#pragma once
#include <iostream>


class Solution{
    //reprezentacja problemu jako: TSP
    private:
        int size;
        int* path;

    public:
        Solution(int dimension);
        ~Solution();
        int getPathSize();
        void printPath();
        int getValueAt(int index);
        void setValueAt(int index, int value);
        
};

