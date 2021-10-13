#include <iostream>
#include "include/loader.hpp"
#include "include/problem.hpp"


int main(int, char**) {
    std::string file_name = "D:/Dev/Metaheuristic/problem instances/test-file.vrp";
    //std::string file_name = "D:/Dev/Metaheuristic/problem instances/A-n32-k5.vrp";
    //Loader loader("D:/Dev/Metaheuristic/test.txt");
    //Loader loader("D:/Dev/Metaheuristic/problem instances/test-file.vrp");
    //loader.printInfo();
    
    cVRP* prob;

    Loader load_one(file_name);

    prob = load_one.loadProblem();

    
    std::cout << "Vehicle capacity: " << prob->getVehicleCapacity() << "\n";
    std::cout << "Dimension: " << prob->getDimension() << "\n";

    std::cout << "Distance check: \n";
    prob->printDistanceMatrix();
    
    delete prob; 
    return 0;
}
