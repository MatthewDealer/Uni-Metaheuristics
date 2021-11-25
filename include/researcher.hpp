#pragma once

#include <chrono>
#include <iostream>
#include "loader.hpp"
#include "problem.hpp"
#include "solution.hpp"
#include "solver.hpp"
#include "csvlogger.hpp"

enum mutation_type {swap, invert};
enum crossing_type {oc, xc};
enum selection_type {rullette, tournament};

class Researcher{
    protected:
        int sample_count;
        int tests_count;

        //Initial parameters
        int exercise_number;
        int iteration_limit;
        mutation_type mutate_mode;

        //Shift values
        int iteration_shift = 0;

        //time
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;
        std::chrono::nanoseconds duration;

        std::string output_file = "../datasheets/Evolution_research_popxiter_2.csv";
        Logger* log;


        //Problem instances     
        std::string problem_paths[7] = {
        "../problem instances/A-n32-k5.vrp",  //0
        "../problem instances/A-n37-k6.vrp",  //1
        "../problem instances/A-n39-k5.vrp",  //2
        "../problem instances/A-n45-k6.vrp",  //3
        "../problem instances/A-n48-k7.vrp",  //4
        "../problem instances/A-n54-k7.vrp",  //5
        "../problem instances/A-n60-k9.vrp"   //6

    };

    public:
        //Constructor of researcher.
        Researcher(int iterations, mutation_type m_mode) : iteration_limit(iterations), mutate_mode(m_mode){

        };
        ~Researcher();

        //Set tests count
        void setExNumber(int number);
        void setTestsCount(int count);
        void setSampleCount(int count);

        //Set shift values
        void setIterShift(int shift);

        void setIterations(int size);

        void research();


};

class EA_Researcher : public Researcher{
    private:
        crossing_type cross_mode;
        selection_type select_mode;

        int pop_size;
        float cross_probability;
        float mutate_probability;
        int tournament_size;

        //Shift Values
        float cross_shift = 0;
        float mutate_shift = 0;
        int pop_shift = 0;
        int tournament_shift = 0;


    public:
        /*Constructor of EA researcher.
        //@param number population size
        //@param m_mode mutation mode
        //@param c_mode crossing mode
        */
        EA_Researcher(int iterations, mutation_type m_mode, crossing_type c_mode, 
            selection_type s_mode, int population_size, float cross_p, float mutate_p) : Researcher(iterations, m_mode), 
            cross_mode(c_mode), select_mode(s_mode), pop_size(population_size), cross_probability(cross_p), mutate_probability(mutate_p){
                log = new Logger(output_file, nullptr);
                //Log to file first line
                std::vector<std::string> first_line;
                first_line.push_back("EA Research");
                first_line.push_back("Population size");
                first_line.push_back("Generations");
                first_line.push_back("Cross p");
                first_line.push_back("Mutate p");
                first_line.push_back("Tournament size");
                first_line.push_back("best");
                first_line.push_back("avg");
                first_line.push_back("worst");
                log->LogToFile(first_line);
            };


        //Set other values
        void setTournamentSize(int size);
        // Set shift values
        void setCrossShift(float shift);
        void setMutateShift(float shift);
        void setPopShift(int shift);
        void setPTournamentShift(int shift);

        //Set parameters
        void setCross(float p);
        void setMutate(float p);
        void setPopSize(int size);
        void setTSize(int size);
        void setIterations(int size);

        void research();
};

class TS_Researcher : public Researcher{
    private:
        int n_size; //Neighborhood size
        int t_size; //Tabu size 

        //Shift values
        int n_shift = 0;
        int t_shift = 0;

    public:
        //Constructor of TS researcher.
        TS_Researcher(int iterations, mutation_type m_mode, int neighborhood_size, int tabu_size) : Researcher(iterations, m_mode), 
            n_size(neighborhood_size), t_size(tabu_size){
                log = new Logger(output_file, nullptr);
                //Log to file first line
                std::vector<std::string> first_line;
                first_line.push_back("TS Research");
                first_line.push_back("Iterations");
                first_line.push_back("Neighborhood size");
                first_line.push_back("Tabu size");
                first_line.push_back("best");
                first_line.push_back("avg");
                first_line.push_back("worst");
                log->LogToFile(first_line);
            };


        //Set shift values
        void setNShift(int shift);
        void setTShift(int shift);

        //Set parameters
        void setNSize(int size);
        void setTabuSize(int size);


        void research();

};

class SA_Researcher : public Researcher{
    private:
        int n_size; //Neighborhood size
        float temperature;
        float temp_multiplier;
        int temp_step;

        //Shift values
        int n_shift = 0;
        float temp_shift = 0;
        float multiplier_shift = 0;
        int step_shift = 0;

    public:
        //Constructor of SA researcher.
        SA_Researcher(int iterations, mutation_type m_mode, int neighborhood_size, int temperature, float temp_multiplier, int temp_step) : Researcher(iterations, m_mode),
            n_size(neighborhood_size), temperature(temperature), temp_multiplier(temp_multiplier), temp_step(temp_step){
                log = new Logger(output_file, nullptr);
                //Log to file first line
                std::vector<std::string> first_line;
                first_line.push_back("SA Research");
                first_line.push_back("Iterations");
                first_line.push_back("Neighborhood size");
                first_line.push_back("Temp");
                first_line.push_back("Multiplier");
                first_line.push_back("Step");
                first_line.push_back("best");
                first_line.push_back("avg");
                first_line.push_back("worst");
                log->LogToFile(first_line);
            };

        //Set shift values
        void setNShift(int shift);
        void setTempShift(float shift);
        void setMultiplierShift(float shift);
        void setStepShift(int shift);

        //Set parameters
        void setTemp(int value);
        void setNsize(int size);
        void setMultiplier(float value);
        void setStep(int step);
        

        void research();
};
