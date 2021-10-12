#ifndef Loader_H
#define Loader_H

#include <fstream>
#include <iostream>

class Loader{
    private:
        std::string file_name;
    
    public:
        Loader(std::string name) : file_name (name) {};
        void printInfo();
        void readFile();
};

#endif