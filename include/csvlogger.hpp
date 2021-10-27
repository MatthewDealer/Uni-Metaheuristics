#pragma once
#include <iostream>
#include <fstream>

#include "solver.hpp"
//#include "problem.hpp"

class Logger{
    private:
        std::string file_name;
        std::ofstream file;
        cVRP* problem;

    public:
        Logger(std::string path, cVRP* problem);
        ~Logger();
        void runTest(Evolution* evolution_solver, int generations_limit,int evolution_step);
        void runTsTest(int generations_limit, int step, int neighborhood_size, int tabu_size);
        //Compare functions
        void runCompareLog(int pop_size, int generations_limit, float cross_prob, float mutate_prob,  int tournament_sizem, int repeat_count);
        
};
