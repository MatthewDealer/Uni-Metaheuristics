#include "../include/solver.hpp"


Solution* Solver::generateRandomSolution(cVRP* problem){
    srand(time(NULL)); // initialize random seed
    
    int dimension = problem->getDimension();
    int max_capacity = problem-> getVehicleCapacity();
    Solution* sol_ptr = new Solution();
    std::vector<int> path;
    std::vector<int> magazines;

    std::cout << "Got dimension: " << dimension << "\n";
    std::cout << "Got capacity: " << max_capacity << "\n";

    for(int i = 0; i < dimension; i++){
        magazines.push_back(i);
    }

    int current_load = 0;
    int path_count = 1;

    while(magazines.size() > 0){
        std::cout << "Creating path no. " << path_count << "...\n";
        while(current_load < max_capacity && magazines.size() > 0){
            int random = rand() % magazines.size();
            path.push_back(magazines[random]);
            current_load += problem->getDemands(magazines[random]);
            //delete magazine from vector
            magazines.erase(magazines.begin() + random);

        }
        sol_ptr->addPath(path);
        path.clear();
        current_load = 0;
        path_count ++;
    }
    std::cout << "Paths created.\n";   
    return sol_ptr;
}


Solution* Solver::genetareGreedySolution(cVRP* problem){
    return nullptr;
}