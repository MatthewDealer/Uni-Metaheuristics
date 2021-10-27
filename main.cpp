#include <iostream>
#include <vector>
#include "include/loader.hpp"
#include "include/problem.hpp"
#include "include/solution.hpp"
#include "include/solver.hpp"
#include "include/csvlogger.hpp"


void exerciseOne(cVRP* prob){
    //Logger test
    std::string output_file = "../datasheets/Evolution_T1.csv";
    int repeat_count = 10;
    Logger log(output_file, prob);
    int population_size = 5000;
    int generation_limit = 500;
    float cross_prob = 0.4;
    float mutate_prob = 0.6;
    int tournament_size = 10;
    int step_evolution = 10;
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

    //log.runCompareLog(population_size, generation_limit, cross_prob, mutate_prob, tournament_size, repeat_count);
}

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

int main(int, char**) {

    //Path to file
    //std::string file_name = "D:/Dev/Uni-Metaheuristics/problem instances/test-file.vrp";
    //std::string file_name = "D:/Dev/Uni-Metaheuristics/problem instances/A-n32-k5.vrp";
    //std::string file_name = "D:/Dev/Metaheuristic/problem instances/test-file.vrp";
    std::string pc_problem_paths[8] = {
        "D:/Dev/Metaheuristic/problem instances/test-file.vrp",
        "D:/Dev/Metaheuristic/problem instances/A-n32-k5.vrp",
        "D:/Dev/Metaheuristic/problem instances/A-n37-k6.vrp",
        "D:/Dev/Metaheuristic/problem instances/A-n39-k5.vrp",
        "D:/Dev/Metaheuristic/problem instances/A-n45-k6.vrp",
        "D:/Dev/Metaheuristic/problem instances/A-n48-k7.vrp",
        "D:/Dev/Metaheuristic/problem instances/A-n50-k7.vrp",
        "D:/Dev/Metaheuristic/problem instances/A-n60-k9.vrp"

    };
    std::string file_name = (std::string) pc_problem_paths[1];
    
    std::cout << file_name << "\n";
    
    cVRP* prob;
    Loader load_one(file_name);
    prob = load_one.loadProblem();
    
    std::cout << "Vehicle capacity: " << prob->getVehicleCapacity() << "\n";
    std::cout << "Dimension: " << prob->getDimension() << "\n";
    std::cout << "______________________________________________________\n";
    //std::cout << "Distance check: \n";
    //prob->printDistanceMatrix();

    exerciseOne(prob);
    
    //_________________________________________________________________________________________________
    //Clean up memory and close program
    //delete prob;
    return 0;
}
