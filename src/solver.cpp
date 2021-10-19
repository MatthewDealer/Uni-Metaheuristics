#include "../include/solver.hpp"

Solver::Solver(cVRP* problem){
    this->problem = problem;
}

Solver::~Solver(){
    problem = nullptr;
}

Solution* Solver::generateRandomSolution(cVRP* problem){
    srand(time(NULL)); // initialize random seed
    
    std::cout << "Generating random solution...\n";

    int dimension = problem->getDimension();
    int max_capacity = problem-> getVehicleCapacity();
    Solution* solution_ptr = new Solution(dimension);
    std::vector<int> path;
    std::vector<int> magazines;

    std::cout << "Got dimension: " << dimension << "\n";
    std::cout << "Got capacity: " << max_capacity << "\n";

    for(int i = 0; i < dimension-1; i++){
        magazines.push_back(i+1);
    }

    while(magazines.size() > 0){
        int random = rand() % magazines.size();
        int load = problem->getDemands(magazines[random]);
        //delete magazine from vector
        magazines.erase(magazines.begin() + random);

    }
    std::cout << "Path created.\n";
    return solution_ptr;
}

Solution* Solver::generateGreedySolution(cVRP* problem){
    srand(time(NULL)); // initialize random seed
    
    std::cout << "Generating greedy solution...\n";

    int dimension = problem->getDimension();
    int max_capacity = problem-> getVehicleCapacity();
    Solution* solution_ptr = new Solution();
    std::vector<int> path;
    std::vector<int> magazines;

    std::cout << "Got dimension: " << dimension << "\n";
    std::cout << "Got capacity: " << max_capacity << "\n";

    for(int i = 0; i < dimension-1; i++){
        magazines.push_back(i+1);
    }

    int random = rand() % magazines.size();
    int start_point = magazines[random];
    int current_load = problem->getDemands(start_point);
    int path_count = 1;
    path.push_back(start_point);
    magazines.erase(magazines.begin() + random);

    while(magazines.size() > 0){
        int best_option = -1;
        int best_distance = -1;

        // Get the shortes route
        for (int i = 0; i < magazines.size(); i++){
            int distance = problem->getDistance(start_point, magazines[i]);
            if(best_option == -1 || best_distance > distance){
                best_option = i;
                best_distance = distance; 
            }
        }
        
        int load = problem->getDemands(magazines[best_option]);
        if(current_load + load > max_capacity){
            std::cout << "Created path no. " << path_count << "...\n";
            solution_ptr->addPath(path);
            path.clear();
            current_load = 0;
            path_count ++; 
        }

        path.push_back(magazines[best_option]);
        current_load += load;
        start_point = magazines[best_option];
        magazines.erase(magazines.begin() + best_option);
    }
    solution_ptr->addPath(path);
    std::cout << "Paths created.\n";   
    return solution_ptr;
}


//Evolutionary algorithm
void Evolution::initialize(){
    std::cout << "heh";
}

// Crossing
Solution* Evolution::crossover(Solution* parent_one, Solution* parent_two){

}

Solution* Evolution::orderedCrossover(Solution* parent_one, Solution* parent_two){
    srand(time(NULL)); // initialize random seed
    int start_point = rand() % problem->getDimension();
    int end_point = rand() % problem->getDimension();
    for(int i = 0; i < problem->getDimension(); i++){

    }
}

Solution* Evolution::pmCrossover(Solution* parent_one, Solution* parent_two){

}

// Mutation 
void Evolution::mutation(Solution* object){
    swapMutation(object);
}

void Evolution::swapMutation(Solution* object){
    srand(time(NULL)); // initialize random seed
    int dimension = problem->getDimension();
    int first_index = rand() % dimension;
    int second_index = rand() % dimension;
    
    //Make sure that indexes arent equal
    while(second_index == first_index)
        second_index = rand() % dimension;

    int fist_value = object->getValueAt(first_index);
    int second_value = object-> getValueAt(second_index);

    object->setValueAt(first_index, second_value);
    object->setValueAt(second_index, fist_value);

    fixSolution(object);
}

