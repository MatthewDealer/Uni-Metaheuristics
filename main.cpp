#include <iostream>
#include <vector>
#include "include/loader.hpp"
#include "include/problem.hpp"
#include "include/solution.hpp"
#include "include/solver.hpp"

int main(int, char**) {

    //Path to file
    std::string file_name = "D:/Dev/Uni-Metaheuristics/problem instances/test-file.vrp";
    //std::string file_name = "D:/Dev/Metaheuristic/problem instances/A-n32-k5.vrp";
    
    
    cVRP* prob;

    Loader load_one(file_name);

    prob = load_one.loadProblem();

    
    std::cout << "Vehicle capacity: " << prob->getVehicleCapacity() << "\n";
    std::cout << "Dimension: " << prob->getDimension() << "\n";

    //std::cout << "Distance check: \n";
    //prob->printDistanceMatrix();
    
    std::cout << "Solution Test\n";
    Solver solver;
    Solution* sol_one = solver.generateRandomSolution(prob);
    sol_one->printPaths();
        
    float result = prob->evalutateSolution(sol_one);
    std::cout << "Score: " << result << "\n";
    
    //Clean up memory and close program
    delete prob;
    delete sol_one;
    return 0;
}
