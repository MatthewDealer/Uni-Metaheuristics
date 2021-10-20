#pragma once
#include "problem.hpp"
#include "solution.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <stdlib.h>
#include <time.h>  

class Solver{   
    protected:
        cVRP* problem;    
    public:
        Solver(cVRP* problem);
        ~Solver();
        Solution* generateRandomSolution();
        Solution* generateGreedySolution();

};

class Evolution : public Solver{
    private:

        float crossing_probablity;
        float mutation_probablity;  

        int tournament_size;
        
        int population_size;
        int max_generation;
        Solution** population;
        float* evaluation;
    public:
        
        Evolution(cVRP* problem, int pop_size, float cross, float mutate);
        ~Evolution();
        
        int getPopulationSize();
        void setTournamentSize(int size);

        //Main function
        void evolution(int generation_limit);
        Solution* getBest();

        //population control functions
        void initialize();
        void evaluate();
        Solution* clone(Solution* object);

        //Crossing functions
        Solution* crossover(Solution* parent_one, Solution* parent_two);
        Solution* orderedCrossover(Solution* parent_one, Solution* parent_two);
        Solution* pmCrossover(Solution* parent_one, Solution* parent_two);
        
        //Mutation functions
        void mutation(Solution* object);
        void swapMutation(Solution* object);
        void invertMutation(Solution* object);

        //Selection functions
        int select();
        int tournament(int size);
        int roulette();

        //help functions
        void printSolution(int index);
        void printSolution(Solution* obj);
};


