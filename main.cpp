#include <iostream>
#include <vector>
#include "include/loader.hpp"
#include "include/problem.hpp"
#include "include/solution.hpp"
#include "include/solver.hpp"

int main(int, char**) {

    //Path to file
    //std::string file_name = "D:/Dev/Uni-Metaheuristics/problem instances/test-file.vrp";
    std::string file_name = "D:/Dev/Metaheuristic/problem instances/test-file.vrp";
    //std::string file_name = "D:/Dev/Metaheuristic/problem instances/A-n32-k5.vrp";
    
    
    cVRP* prob;
    Loader load_one(file_name);
    prob = load_one.loadProblem();

    
    std::cout << "Vehicle capacity: " << prob->getVehicleCapacity() << "\n";
    std::cout << "Dimension: " << prob->getDimension() << "\n";
    std::cout << "______________________________________________________\n";
    //std::cout << "Distance check: \n";
    //prob->printDistanceMatrix();

    
    Evolution solver(prob, 100, 0.2, 0.2);
    solver.setTournamentSize(5);
    std::cout << "Size: " << solver.getPopulationSize() << "\n";

    /*
    Solution* sol_one = solver.generateRandomSolution();
    Solution* sol_two = solver.generateRandomSolution();
    Solution* child = solver.pmCrossover(sol_one, sol_two);

    sol_one->printPath();
    sol_two->printPath();
    child->printPath();
    */

    
    //Evolution Test
    solver.evolution(20);
    
    std::cout << "Done\n";
    std::cout << "Best path:\n";
    Solution* best = solver.getBest();
    solver.printSolution(best);
    std::cout << "Score: " << prob->evalutateSolution(best) << "\n";
    
    /*
    //Solution Test
    Solution* sol_one = solver.generateRandomSolution();

    sol_one->printPath();
    float result = prob->evalutateSolution(sol_one);
    std::cout << "Score: " << result << "\n";
    // ValueAt Test
    std::cout << sol_one->getValueAt(4) << "\n";
    sol_one->setValueAt(4, 9); 
    std::cout << sol_one->getValueAt(4) << "\n";
    sol_one->printPath();
    */
    /*
    //Crosover Test
    Solution* sol_two = solver.generateRandomSolution(prob);
    sol_one->printPath();
    sol_two->printPath();
    std::cout << "__Crossover__\n";
    Solution* child = solver.crossover(sol_one, sol_two);
    child->printPath();
    */
    //Selection test
    //solver.tournament(10);

    //_________________________________________________________________________________________________
    //Clean up memory and close program
    delete prob;

    //delete sol_one;
    //delete sol_two;
    return 0;
}
