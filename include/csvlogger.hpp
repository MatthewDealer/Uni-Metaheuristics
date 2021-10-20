#pragma once
#include <iostream>
#include <fstream>

class Logger{
    private:
        std::string file_name;
        std::ofstream file;
    public:
        Logger(std::string path);
        ~Logger();
};

/*
    std::ofstream myfile;
      myfile.open ("example.csv");
      myfile << "This is the first cell in the first column.\n";
      myfile << "a,b,c,\n";
      myfile << "c,s,v,\n";
      myfile << "1,2,3.456\n";
      myfile << "semi;colon";
      myfile.close();
      return 0;
*/