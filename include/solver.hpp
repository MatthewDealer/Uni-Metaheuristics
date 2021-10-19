#pragma once
#include "problem.hpp"
#include "solution.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>  

class Solver{   
    protected:
        cVRP* problem;    
    public:
        Solver(cVRP* problem);
        ~Solver();
        Solution* generateRandomSolution(cVRP* problem);
        Solution* generateGreedySolution(cVRP* problem);

};

class Evolution : Solver{
    private:
        int population_size;
        int max_generation;
        Solution* population;
    public:
        void initialize();
        
        //Crossing functions
        Solution* crossover(Solution* parent_one, Solution* parent_two);
        Solution* orderedCrossover(Solution* parent_one, Solution* parent_two);
        Solution* pmCrossover(Solution* parent_one, Solution* parent_two);
        
        //Mutation functions
        void mutation(Solution* object);
        void swapMutation(Solution* object);
        void invertMutation(Solution* object);
};


