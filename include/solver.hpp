#pragma once
#include "problem.hpp"
#include "solution.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <deque>

class Solver{   
    protected:
        cVRP* problem;    
    public:
        Solver(cVRP* problem);
        ~Solver();
        Solution* generateRandomSolution();
        Solution* generateGreedySolution();
        float getBestScore();
        float getAvgScore();
        float getWorstScore();

};

class Random : public Solver{
    private:
        int solution_count;
        Solution** solutions;
        float* scores;
    public:
        Random(cVRP* problem, int count);
        ~Random();
        void genarateSolutions();
        float getBestScore();
        float getAvgScore();
        float getWorstScore();
        
};

class Greedy : public Solver{
    private:
        int solution_count;
        Solution** solutions;
    public:
        Greedy(cVRP* problem);
        ~Greedy();
        Solution* generateGreedySolution(int first);
        void generateSolutions();
        Solution* getSolution(int index);
        float getBestScore();
        float getAvgScore();
        float getWorstScore();
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
        void printPop();


        float getBestScore();
        float getAvgScore();
        float getWorstScore();
};


class TabuSearch : public Solver{
    private:
        int neighborhood_size;
        int tabu_size;

        Solution* current_solution;
        Solution* best_solution;
        Solution** neighbors;
        std::deque<Solution*> tabu;
        float current_evaluation;
        float best_evaluation;
        float* evaluation;
    
    public:
        TabuSearch(cVRP* problem, int n_size, int t_size);
        ~TabuSearch();
        void initialize();

        //main function
        void search(int iterations);
        int getBestOfNeighbors();

        //Output functions
        Solution* getBest();

        //Neighbors functions
        void generateNeighbors(Solution* object);
        Solution* generateNeighbor(Solution* object);
        Solution* swap(Solution* object);
        Solution* invert(Solution* object);

        //help functions
        Solution* clone(Solution* object);
        bool isEqual(Solution* obj1, Solution* obj2);
        bool isTabu(Solution* object);
        bool isNeighbor(Solution* object);
};