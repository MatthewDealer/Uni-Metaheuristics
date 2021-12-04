#pragma once
#include "problem.hpp"
#include "solution.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <deque>
#include <math.h>

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

        void printSolution(Solution* obj);

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
        int getbestIndex();
        float getBestScore();
        float getAvgScore();
        float getWorstScore();
};

class Evolution : public Solver{
    protected:
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
        float getBestEvaluation();
        void printTabu();

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

        float getBestScore();
        float getAvgScore();
        float getWorstScore();
};


class SimulatedAnnealing : public Solver{
    private:
        int neighborhood_size;
        float temperature;
        int t;
        int step;
        float multiplier;

        Solution* current_solution;
        float current_evaluation;
        Solution* best_solution;
        float best_evaluation;
        Solution** neighbors;
        float* evaluation;
    
    public:
        SimulatedAnnealing(cVRP* problem, int n_size, float start_temperature, int step, float multiplier);
        ~SimulatedAnnealing();
        void initialize();

        //main function
        void annealing(int iterations);
        int getBestOfNeighbors();

        //Output functions
        Solution* getBest();
        float getBestEvaluation();

        //Neighbors functions
        void generateNeighbors(Solution* object);
        Solution* generateNeighbor(Solution* object);
        Solution* swap(Solution* object);
        Solution* invert(Solution* object);

        //help functions
        Solution* clone(Solution* object);
        bool isEqual(Solution* obj1, Solution* obj2);
        bool isNeighbor(Solution* object);

        float getBestScore();
        float getAvgScore();
        float getWorstScore();
        float getCurrentScore();
        float getTemperature();
};


//Hybrid for ex 5
class EA_TS_Hybrid : public Evolution{
    private:
        float n_boost;
        int boost_step;
        int boost_iterations;

        int neighborhood_size;
        float temperature;
        int temp_step;
        float temp_multiplier;
        
        int step;
    public:
    EA_TS_Hybrid(cVRP* problem, int pop_size, float cross, float mutate, int neighborhood_size, float start_temperature, int step_temp, float multiplier, int boost_iterations, float n_boost, int boost_step);

    Solution** generateNeighbors(Solution* object);
    Solution* generateNeighbor(Solution* object);

    void boost();
    void boosted_evolution(int generation_limit);
};

//Second Hybrid for ex 5
class EA_Temp_Hybrid : public Evolution{
    private:
        //Anneling part
        float temperature;
        int temp_step;
        float temp_multiplier;
        int step;

    public:
        EA_Temp_Hybrid(cVRP* problem, int pop_size, float cross, float mutate, float start_temperature, int step_temp, float multiplier);     

        // main function
        void hybrid_evolution(int generation_limit);

};