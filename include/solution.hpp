#pragma once
#include <iostream>
#include <vector>

class Solution{
    //reprezentacja problemu jako:
    //Sciezka 1: numer magazynu, numer magazynu
    //Sciezka 2: nr mag, nr mag, nr mag
    private:
        std::vector<std::vector<int>> paths;

    public:
        int getPathsCount();
        std::vector<int> getPath(int index);
        void printPaths();
        void addPath(std::vector<int>);

};

