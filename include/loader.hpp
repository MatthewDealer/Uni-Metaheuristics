#pragma once
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include "problem.hpp"

class Loader{
    private:
        std::string file_name;
    
    public:
        Loader(std::string name) : file_name (name) {};
        void printInfo();
        void readFile();
        cVRP* loadProblem();
        
};

