#include <iostream>
#include "include/loader.hpp"
#include "include/problem.hpp"


int main(int, char**) {
    //Loader loader("D:/Dev/Metaheuristic/test.txt");
    //Loader loader("D:/Dev/Metaheuristic/problem instances/test-file.vrp");
    //loader.printInfo();
    //loader.readFile();

    cVRP object(3,5);
    
    cVRP* prob = &object;

    std::cout << prob->getVehicleCapacity() << "\n";
    std::cout << prob->getDimension() << "\n";

    delete prob;
}
