#include <iostream>
#include <vector>
#include "include/loader.hpp"
#include "include/problem.hpp"
#include "include/solution.hpp"
#include "include/solver.hpp"
#include "include/csvlogger.hpp"
#include "include/researcher.hpp"
#include <cstdio>



#define EXERCISE 1

void mutationTest(cVRP* prob){
    Evolution solver(prob, 100, 0.2, 0.2);
    solver.setTournamentSize(5);
    std::cout << "Size: " << solver.getPopulationSize() << "\n";
    Solution* sol_one = solver.generateRandomSolution();
    Solution* sol_two = solver.generateRandomSolution();
    Solution* child = solver.pmCrossover(sol_one, sol_two);

    sol_one->printPath();
    sol_two->printPath();
    child->printPath();
    delete sol_one;
    delete sol_two;
}

void crossoverTest(cVRP* prob){
    //Crosover Test
    Evolution solver(prob, 100, 0.2, 0.2);
    Solution* sol_one = solver.generateRandomSolution();
    Solution* sol_two = solver.generateRandomSolution();
    sol_one->printPath();
    sol_two->printPath();
    std::cout << "__Crossover__\n";
    Solution* child = solver.crossover(sol_one, sol_two);
    child->printPath();
    delete sol_one;
    delete sol_two;
}

void exerciseOne(cVRP* prob){
    //Logger test
    std::string output_file = "../datasheets/Evolution_1.csv";
    
    Logger log(output_file, prob);

    //EA parameters
    int population_size = 5000;
    int generation_limit = 500;
    float cross_prob = 0.73;
    float mutate_prob = 0.46;
    int tournament_size = 16;
    
    //Log parameters
    int step_evolution = 100;
    int repeat_count = 1;

    Evolution evolution_solver(prob, population_size, cross_prob, mutate_prob); 
    evolution_solver.setTournamentSize(tournament_size);

    
    //Evolution algorithm test
    log.runTest(&evolution_solver, generation_limit, step_evolution);
    std::cout << "Best path:\n";
    Solution* best = evolution_solver.getBest();
    evolution_solver.printSolution(best);
    std::cout << "Score: " << prob->evalutateSolution(best) << "\n";
    std::cout << "________________________________________________\n";
    prob->evalutateSolution(best);
    
    // log.runCompareLog(population_size, generation_limit, cross_prob, mutate_prob, tournament_size, repeat_count);
}

void exerciseTwo(cVRP* prob){
    //Tabu search test
    std::string output_file = "../datasheets/TabuSearch_p1_swap.csv";
    Logger log(output_file, prob);

    // Sa parameters
    int neighborhood_size = 50;
    float tabu_size = 100;
    int iteration_limit = 1000;

    //Log parameters
    int step = 1;

    log.runTsTest(iteration_limit, step, neighborhood_size, tabu_size);

}

void exerciseThree(cVRP* prob){
    //Simulated annealing test
    std::string number = std::to_string(EXERCISE);
    std::string output_file = "../datasheets/Anneling_p_comp" + number + ".csv";
    Logger log(output_file, prob);

    //SA parameters
    int neighborhood_size = 16; 
    float start_temperature = 150; 
    int anneling_step = 64; 
    float multiplier = 0.978;
    int generations_limit = 300;

    //loger parameters
    int step = 1; 
    int repeat_count = 10;
    // log.runAnnelingTest(generations_limit, step, neighborhood_size, start_temperature, anneling_step, multiplier);
    log.runAnnelingLog(generations_limit, neighborhood_size, start_temperature, anneling_step, multiplier, repeat_count);
    

}

void exerciseFour(){

    /// MAX CHILDS = 1 000 000
    int iterations = 200; //200
    mutation_type m = mutation_type::invert;
    crossing_type c = crossing_type::oc;
    selection_type s = selection_type::tournament;
    int population_size = 3500; //3500
    float cross_p = 0.7; //0.9
    float mutate_p = 0.1; // 0.83
    int tournament_size = 12; //20


    EA_Researcher ea(iterations, m, c, s, population_size, cross_p, mutate_p);
    ea.setExNumber(0);
    ea.setTournamentSize(tournament_size);


    //Research Mutate
    ea.setIterShift(0);
    ea.setPopShift(0);
    ea.setMutateShift(0.1);
    ea.setCrossShift(0);
    
    ea.setSampleCount(10);
    ea.setTestsCount(9);
    ea.research();
    
    //Research Cross
    ea.setCross(0.1);
    ea.setIterShift(0);
    ea.setPopShift(0);
    ea.setMutateShift(0);
    ea.setCrossShift(0.1);
    
    ea.research();
    
    //Research PopSize
    ea.setIterShift(0);
    ea.setPopShift(500);
    ea.setMutateShift(0);
    ea.setCrossShift(0);
    ea.setSampleCount(10);
    ea.setTestsCount(3);
    ea.research();

    //Research Iterations Size
    ea.setIterShift(100);
    ea.setPopShift(0);
    ea.setMutateShift(0);
    ea.setCrossShift(0);
    ea.setPTournamentShift(0);

    ea.setSampleCount(10);
    ea.setTestsCount(4);
    ea.research();

    //Research Tournament Size
    ea.setIterShift(0);
    ea.setPopShift(0);
    ea.setMutateShift(0);
    ea.setCrossShift(0);
    ea.setPTournamentShift(10);

    ea.setSampleCount(10);
    ea.setTestsCount(5);
    ea.research();




}

int main(int, char**) {
    //std::getchar();
    //Path to file
    std::string laptop_problem_paths[8] = {
        "D:/Dev/Uni-Metaheuristics/problem instances/test-file.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n32-k5.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n37-k6.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n39-k5.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n45-k6.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n48-k7.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n54-k7.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n60-k9.vrp"

    };


    std::string pc_problem_paths[8] = {
        "D:/Dev/Metaheuristic/problem instances/test-file.vrp", //0
        "D:/Dev/Metaheuristic/problem instances/A-n32-k5.vrp",  //1
        "D:/Dev/Metaheuristic/problem instances/A-n37-k6.vrp",  //2
        "D:/Dev/Metaheuristic/problem instances/A-n39-k5.vrp",  //3
        "D:/Dev/Metaheuristic/problem instances/A-n45-k6.vrp",  //4
        "D:/Dev/Metaheuristic/problem instances/A-n48-k7.vrp",  //5
        "D:/Dev/Metaheuristic/problem instances/A-n54-k7.vrp",  //6
        "D:/Dev/Metaheuristic/problem instances/A-n60-k9.vrp"   //7

    };

        std::string problem_paths[8] = {
        "../problem instances/test-file.vrp", //0
        "../problem instances/A-n32-k5.vrp",  //1
        "../problem instances/A-n37-k6.vrp",  //2
        "../problem instances/A-n39-k5.vrp",  //3
        "../problem instances/A-n45-k6.vrp",  //4
        "../problem instances/A-n48-k7.vrp",  //5
        "../problem instances/A-n54-k7.vrp",  //6
        "../problem instances/A-n60-k9.vrp"   //7

    };
    
    std::string file_name = (std::string) problem_paths[EXERCISE];
    //std::string file_name = (std::string) laptop_problem_paths[1];
    
    std::cout << file_name << "\n";
    
    cVRP* prob;
    Loader load_one(file_name);
    prob = load_one.loadProblem();
    
    std::cout << "Vehicle capacity: " << prob->getVehicleCapacity() << "\n";
    std::cout << "Dimension: " << prob->getDimension() << "\n";
    std::cout << "______________________________________________________\n";
    
    //std::cout << "Distance check: \n";
    //prob->printDistanceMatrix();

    //Exercise One
    //Wynik średni powinien być lepszy od greedy.
    //exerciseOne(prob);

    //Exercise Two
    // exerciseTwo(prob);

    //Exercise Three
    // exerciseThree(prob);
    
    //Exercise Four
    exerciseFour();

    //_________________________________________________________________________________________________
    //Clean up memory and close program
    //delete prob;
    //std::getchar();
    return 0;
}
