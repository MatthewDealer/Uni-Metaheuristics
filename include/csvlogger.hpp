#pragma once
#include <iostream>
#include <fstream>
#include <limits>

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
        void LogToFile(std::vector<std::string> vector_of_words);

        void runEATest(Evolution* evolution_solver, int generations_limit,int evolution_step);
        void runTsTest(int generations_limit, int step, int neighborhood_size, int tabu_size);
        void runAnnelingTest(int generations_limit, int step, int n_size, float start_temperature, int a_step, float multiplier);
        void runEATSTest(EA_TS_Hybrid* evolution_solver, int generations_limit,int evolution_step);
        void runEATempTest(EA_Temp_Hybrid* evolution_solver, int generations_limit,int evolution_step);

        //Compare functions
        void runCompareLog(int pop_size, int generations_limit, float cross_prob, float mutate_prob,  int tournament_sizem, int repeat_count);
        void runEALog(int pop_size, int generations_limit, float cross_prob, float mutate_prob,  int tournament_sizem, int repeat_count);
        void runTsLog(int generations_limit, int step, int neighborhood_size, int tabu_size, int repeat_count);
        void runAnnelingLog(int generations_limit,int neighborhood_size,int start_temperature, int anneling_step, float multiplier, int repeat_count);
        void runEATempLog(int pop_size, int generations_limit, float cross_prob, float mutate_prob,  int tournament_sizem, float temp, int step, float multiplier, int repeat_count);
        void runEATsLog(int pop_size, int generations_limit, float cross_prob, float mutate_prob,  int tournament_sizem, int n_size, float temp, int step, float multiplier, int repeat_count, int boost_iters, float n_boost, int boost_step);
        
};
