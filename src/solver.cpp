#include "../include/solver.hpp"

Solver::Solver(cVRP* problem){
    this->problem = problem;
    srand(time(NULL)); // initialize random seed
}

Solver::~Solver(){
    problem = nullptr;
}

Solution* Solver::generateRandomSolution(){
    
    
    //std::cout << "Generating random solution...\n";

    int dimension = problem->getDimension();
    int max_capacity = problem-> getVehicleCapacity();
    Solution* solution_ptr = new Solution(dimension);
    std::vector<int> magazines;

    //std::cout << "Got dimension: " << dimension << "\n";
    //std::cout << "Got capacity: " << max_capacity << "\n";

    for(int i = 0; i < dimension-1; i++){
        magazines.push_back(i+1);
    }

    for(int i = 0; i < dimension-1; i++){
        int random = rand() % magazines.size();
        solution_ptr->setValueAt(i, magazines[random]);
        magazines.erase(magazines.begin() + random);
    }
    //std::cout << "Path created.\n";
    return solution_ptr;
}

Solution* Solver::generateGreedySolution(){
    
    
    std::cout << "Generating greedy solution...\n";

    int dimension = problem->getDimension();
    int max_capacity = problem-> getVehicleCapacity();
    Solution* solution_ptr = new Solution(dimension);
    std::vector<int> magazines;

    std::cout << "Got dimension: " << dimension << "\n";
    std::cout << "Got capacity: " << max_capacity << "\n";

    for(int i = 0; i < dimension-1; i++){
        magazines.push_back(i+1);
    }

    int random = rand() % magazines.size();
    int start_point = magazines[random];

    for(int i = 0; i < dimension -1; i++){
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

        solution_ptr->setValueAt(i, magazines[best_option]);
        start_point = magazines[best_option];
        magazines.erase(magazines.begin() + best_option);
    }

    //std::cout << "Paths created.\n";   
    return solution_ptr;
}

void Solver::printSolution(Solution* obj){
    int path_count = 1;
    int max_capacity = problem->getVehicleCapacity();
    int current_capacity = 0;
    std::cout << "Solution: \n";
    std::cout << "\tPath no. " << path_count << ": ";
    for(int i =0; i < problem->getDimension() - 1; i++){
        int mag = obj->getValueAt(i);
        int demand = problem->getDemands(mag);
        if(current_capacity + demand > max_capacity){
            std::cout << "\n";
            current_capacity = 0;
            path_count++;
            std::cout << "\tPath no. " << path_count << ": ";
        }
        else{
            if(i>0)
            std::cout << " - ";
        }
        std::cout << mag;
        current_capacity += demand;
        
    }
    std::cout << "\n";
}

//Random algorithm
Random::Random(cVRP* problem, int count) : Solver(problem){
    solution_count =  count;
    solutions = new Solution*[solution_count];
    scores = new float[solution_count];
}

Random::~Random(){
    for(int i = 0; i < solution_count; i++)
        if(solutions[i]!=nullptr){
            delete solutions[i];
        }

    delete[] solutions;
    delete[] scores;
}


void Random::genarateSolutions(){
    for(int i = 0; i < solution_count; i++){
        solutions[i] = generateRandomSolution();
        scores[i] = problem->evalutateSolution(solutions[i]);
    }
}
float Random::getBestScore(){
    float best_score = -1;
    for(int i = 0; i < solution_count; i++){
        if(best_score == -1 || best_score > scores[i]){
            best_score = scores[i];
        }
    }
    return best_score;
}
float Random::getAvgScore(){
    float sum;
    for(int i = 0; i < solution_count; i++){
        sum += scores[i];
        
    }
    sum = sum / solution_count;
    return sum;
}
float Random::getWorstScore(){
    float worst_score = -1;
    for(int i = 0; i < solution_count; i++){
        if(worst_score == -1 || worst_score  < scores[i]){
            worst_score = scores[i];
        }
    }
    return worst_score;
}

//Greedy algorithm
Greedy::Greedy(cVRP* problem): Solver(problem){
    solution_count = problem->getDimension() - 1;
    solutions = new Solution*[solution_count];

    
}

Greedy::~Greedy(){
    for( int i = 0; i < solution_count; i++){
        delete solutions[i];
    }
    delete[] solutions; 
}

Solution* Greedy::generateGreedySolution(int first){
    

    int dimension = problem->getDimension();
    int max_capacity = problem-> getVehicleCapacity();
    Solution* solution_ptr = new Solution(dimension);
    std::vector<int> magazines;

    for(int i = 0; i < dimension-1; i++){
        magazines.push_back(i+1);
    }

    
    int start_point = magazines[first];

    for(int i = 0; i < dimension -1; i++){
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

        solution_ptr->setValueAt(i, magazines[best_option]);
        start_point = magazines[best_option];
        magazines.erase(magazines.begin() + best_option);
    }

    //std::cout << "Paths created.\n";   
    return solution_ptr;
}

void Greedy::generateSolutions(){
    for (int i = 0; i < solution_count; i++){
        solutions[i] = generateGreedySolution(i);
    }
}

int Greedy::getbestIndex(){
    float best_score = -1;
    float index = -1;
    for(int i = 0; i < solution_count; i++){
        float score = problem->evalutateSolution(solutions[i]);
        if(best_score == -1 || best_score > score){
            best_score = score;
            index = i;
        }
    }
    return index;
}

Solution* Greedy::getSolution(int index){
    return solutions[index];
}

float Greedy::getBestScore(){
    float best_score = -1;
    for(int i = 0; i < solution_count; i++){
        float score = problem->evalutateSolution(solutions[i]);
        if(best_score == -1 || best_score > score){
            best_score = score;
        }
    }
    return best_score;
}
float Greedy::getAvgScore(){
    float sum;
    for(int i = 0; i < solution_count; i++){
        float score = problem->evalutateSolution(solutions[i]);
        sum += score;
        
    }
    sum = sum / solution_count;
    return sum;
}
float Greedy::getWorstScore(){
    float worst_score = -1;
    for(int i = 0; i < solution_count; i++){
        float score = problem->evalutateSolution(solutions[i]);
        if(worst_score == -1 || worst_score  < score){
            worst_score = score;
        }
    }
    return worst_score;
}

//////////////////////////
//Evolutionary algorithm//
//////////////////////////
Evolution::Evolution(cVRP* problem, int population_size, float cross, float mutate): Solver(problem){
    this->population_size = population_size;
    this->crossing_probablity = cross;
    this->mutation_probablity = mutate;
    initialize();
}

Evolution::~Evolution(){
    problem = nullptr;

    for(int i = 0; i < population_size; i++){
        delete population[i];
    }
    delete[] population;
    delete[] evaluation;
}

int Evolution::getPopulationSize(){
    return population_size;
}

void Evolution::setTournamentSize(int new_size){
    tournament_size = new_size;
}

void Evolution::initialize(){
    population = new Solution*[population_size];
    evaluation = new float[population_size];
    for(int i = 0; i < population_size; i++){
        population[i] = generateRandomSolution();
        evaluation[i] = -1;
    }
    evaluate();
}

void Evolution::evaluate(){
    for(int i = 0; i < population_size; i++){
        evaluation[i] = problem->evalutateSolution(population[i]);
    }
}

Solution* Evolution::clone(Solution* object){
    Solution* solution_ptr = new Solution(problem->getDimension());
    for(int i = 0 ; i < solution_ptr->getPathSize(); i++){
        solution_ptr->setValueAt(i, object->getValueAt(i));
    }
    return solution_ptr;
}


//Evolution
void Evolution::evolution(int generation_limit){
    int iteration = 0;
    while(iteration < generation_limit){
        //std::cout << "Generation no. " << iteration + 1 << "\n";
        Solution** new_pop = new Solution*[population_size];  
        for(int i = 0; i < population_size; i++){
            Solution* child;
            int index_one = select();
            //std::cout << "index one = " << index_one << "\n";
            int index_two = -1;
            Solution* parent_one = population[index_one];
            float cross = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float mutate = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            
            if (cross <= crossing_probablity){
                //std::cout << "CROSS!\n";
                index_two = select();
                Solution* parent_two = population[index_two];
                child = crossover(parent_one, parent_two);

            }
            else {
                child = clone(parent_one);

            }

            if( mutate <= mutation_probablity){
                mutation(child);
            }
            new_pop[i] = child;
            child = nullptr;
        }
        
        
        //clean memory and old population
        for( int i = 0; i < population_size; i++){
            delete population[i];
            
            population[i] = new_pop[i];
            new_pop[i] = nullptr;
        }
        
        delete[] new_pop;

        //Evaluate new population
        evaluate();
        iteration++;
    }
}

Solution* Evolution::getBest(){
    float best_score = -1;
    int index = -1;
    for(int i = 0; i < population_size; i++){
        float score = evaluation[i];
        if(index==-1 || best_score > score){
            index = i;
            best_score = score;
        }
    }
    std::cout << "EA eval: " << evaluation[index] << "\n";
    return population[index];
}

// Crossing
Solution* Evolution::crossover(Solution* parent_one, Solution* parent_two){
    return orderedCrossover(parent_one, parent_two);
    //return pmCrossover(parent_one, parent_two);
}

Solution* Evolution::orderedCrossover(Solution* parent_one, Solution* parent_two){
    
    Solution* child = new Solution(problem->getDimension());

    int size = child->getPathSize();
    int start_point = rand() % size;
    int end_point = rand() % size;

    while(start_point == end_point)
        end_point = rand() % size;
    
    if(start_point > end_point){
        int temp = end_point;
        end_point = start_point;
        start_point = temp;
    }

    
    for(int i = start_point; i <=end_point; i++){
        child->setValueAt(i, parent_one->getValueAt(i));
    }

    int parent_index = 0;
    for(int i = 0; i < size; i++){
        if(child->getValueAt(i) == -1){
            for(int j = 0; j < size; j++){
                if(parent_two->getValueAt(parent_index) == child->getValueAt(j)){
                    parent_index ++;
                    j = -1;
                }
            }
            child->setValueAt(i, parent_two->getValueAt(parent_index));
        }
    }
    return child;
}

Solution* Evolution::pmCrossover(Solution* parent_one, Solution* parent_two){
    Solution* child = new Solution(problem->getDimension());

    int size = child->getPathSize();
    int start_point = rand() % size;
    int end_point = rand() % size;

    while(start_point == end_point)
        end_point = rand() % size;
    
    if(start_point > end_point){
        int temp = end_point;
        end_point = start_point;
        start_point = temp;
    }

    //std::cout << "start: " << start_point <<", end : " << end_point << "\n";

    for(int i = 0; i < size; i++){
        child->setValueAt(i, parent_one->getValueAt(i));
    }

    for(int j = start_point; j < end_point; j++){
        for(int i = 0; i < size; i++){
            if(child->getValueAt(i) == parent_two->getValueAt(j)){
                child->setValueAt(i, parent_one->getValueAt(j));
            }
        }
    }

    for(int i = start_point; i < end_point; i++){
       child->setValueAt(i, parent_two->getValueAt(i)); 
    }
    return child;
}

// Mutation 
void Evolution::mutation(Solution* object){
    //swapMutation(object);
    invertMutation(object);
}

void Evolution::swapMutation(Solution* object){
    int dimension = object->getPathSize();
    int first_index = rand() % dimension;
    int second_index = rand() % dimension;
    
    //Make sure that indexes arent equal
    while(second_index == first_index)
        second_index = rand() % dimension;

    int fist_value = object->getValueAt(first_index);
    int second_value = object->getValueAt(second_index);

    object->setValueAt(first_index, second_value);
    object->setValueAt(second_index, fist_value);

}

void Evolution::invertMutation(Solution* object){
    int dimension = object->getPathSize();
    int start = rand() % dimension;
    int end = rand() % dimension;
    
    //Make sure that indexes arent equal
    while(start == end)
        end = rand() % dimension;

    if(start>end){
        int temp = start;
        start = end;
        end = temp;
    }

    for(int i = 0; i + start< end; i++){
        int temp = object->getValueAt(start+i);
        object->setValueAt(start+i, object->getValueAt(end-i));
        object->setValueAt(end-i, temp); 
       
    }

}

//Selection
int Evolution::select(){
    return tournament(tournament_size);
    //return roulette();
    
}

int Evolution::tournament(int size){
    
    std::set<int> numbers;
    while (numbers.size() < size)
    {
        numbers.insert(rand() % population_size);
    }

    int winner_index = -1;
    float best_score = -1;
    for (auto it = numbers.begin(); it != numbers.end(); ++it){
        int index = *it;
        float score = evaluation[index];
        if(winner_index == -1 || best_score > score){
            winner_index = index;
            best_score = score;
        }
    }
        

    return winner_index;
}

int Evolution::roulette(){
    int winner_index = 0;
    float sum = 0;
    for(int i = 0; i < population_size; i++){
        sum += evaluation[i];
    }
    
    float prob = 0;
    for(int i = 0; i < population_size; i++){
        prob += (1 - (evaluation[i] / sum))/population_size;  
    }

    float random  = rand() * prob;
    prob = 0;
    float old = 0;
    for(int i = 0; i < population_size; i++){
        prob += 1 - (evaluation[i] / sum);
        if(old <= random && prob > random ){
            winner_index = old;
            break;
        }
        old = prob;
    }

    return winner_index;
}

//help 
void Evolution::printSolution(int index){
    int path_count = 1;
    int max_capacity = problem->getVehicleCapacity();
    int current_capacity = 0;
    std::cout << "Solution: \n";
    std::cout << "\tPath no. " << path_count << ": ";
    for(int i =0; i < problem->getDimension() - 1; i++){
        int mag = population[index]->getValueAt(i);
        int demand = problem->getDemands(mag);
        if(current_capacity + demand > max_capacity){
            std::cout << "\n";
            current_capacity = 0;
            path_count++;
            std::cout << "\tPath no. " << path_count << ": ";
        }
        std::cout << mag << " - ";
        current_capacity += demand;
        
    }
    std::cout << "\n";
}

void Evolution::printSolution(Solution* obj){
    int path_count = 1;
    int max_capacity = problem->getVehicleCapacity();
    int current_capacity = 0;
    std::cout << "Solution: \n";
    std::cout << "\tPath no. " << path_count << ": ";
    for(int i =0; i < problem->getDimension() - 1; i++){
        int mag = obj->getValueAt(i);
        int demand = problem->getDemands(mag);
        if(current_capacity + demand > max_capacity){
            std::cout << "\n";
            current_capacity = 0;
            path_count++;
            std::cout << "\tPath no. " << path_count << ": ";
        }
        else{
            if(i>0)
            std::cout << " - ";
        }
        std::cout << mag;
        current_capacity += demand;
        
    }
    std::cout << "\n";
}

void Evolution::printPop(){
    for(int i = 0; i < population_size; i++){
        std::cout << "score:" << evaluation[i] << "\n";
    }
}

//Logger functions
float Evolution::getBestScore(){
    float best_score = -1;
    for(int i = 0; i < population_size; i++){
        if(best_score == -1 || best_score > evaluation[i]){
            best_score = evaluation[i];
        }
    }
    return best_score;
}
float Evolution::getAvgScore(){
    float sum = 0;
    for(int i = 0; i < population_size; i++){
        sum += evaluation[i];
        
    }
    sum = sum / population_size;
    return sum;
}
float Evolution::getWorstScore(){
    float worst_score = -1;
    for(int i = 0; i < population_size; i++){
        if(worst_score == -1 || worst_score  < evaluation[i]){
            worst_score = evaluation[i];
        }
    }
    return worst_score;
}

///////////////
//Tabu Search//
///////////////
TabuSearch::TabuSearch(cVRP* problem, int neighborhood_size, int tabu_size) : Solver(problem){
    this->neighborhood_size = neighborhood_size;
    this->tabu_size = tabu_size;
    initialize();
}

//Destructor
TabuSearch::~TabuSearch(){
    problem = nullptr;

    //Clean memory for neighbors
    for(int i = 0; i < neighborhood_size; i++){
        delete neighbors[i];
    }

    //Clean memory form tabu
    for(int i = 0; i < tabu.size(); i++){
        delete tabu.front();
        tabu.pop_front();
    }

    //clean rest of memory
    delete[] neighbors;
    delete[] evaluation;
    delete current_solution;
    delete best_solution;
}

//initialize Tabu Search
void TabuSearch::initialize(){    
    current_solution = generateRandomSolution();
    best_solution = clone(current_solution);
    current_evaluation = problem->evalutateSolution(current_solution);
    neighbors = new Solution*[neighborhood_size];
    evaluation = new float[neighborhood_size];
    best_evaluation = current_evaluation;

    for(int i = 0; i < neighborhood_size; i++){
        neighbors[i] = nullptr;
    }

    for(int i = 0; i < tabu_size; i++){
        tabu.push_back(nullptr);
    }
}

//main function
void TabuSearch::search(int iterations){
    for(int i = 0; i < iterations; i++){
        generateNeighbors(current_solution);
        int best_neighbor_index = getBestOfNeighbors();

        //Move forward to next best place //najlepszy, uwzgl??dniaj??c list?? Tabu
        delete current_solution;
        current_solution = clone(neighbors[best_neighbor_index]);
        current_evaluation = problem->evalutateSolution(current_solution);

        //Check if best path is found
        if(evaluation[best_neighbor_index] < best_evaluation){
                delete best_solution;
                best_solution = clone(neighbors[best_neighbor_index]);
                best_evaluation = evaluation[best_neighbor_index];
        }

        //update Tabu
        if(tabu.size()>=tabu_size)
            tabu.pop_front();
        tabu.push_back(clone(current_solution));

    }
}

int TabuSearch::getBestOfNeighbors(){
    float best = -1;
    int index = 0;
    for(int i = 0; i < neighborhood_size; i++){
        if(!isTabu(neighbors[i])){
            float score = evaluation[i];
            if(best==-1 || best > score){
                best = evaluation[i];
                index = i;
            }
        }
    }
    return index;
}

//Output functions
Solution* TabuSearch::getBest(){
    return best_solution;
}

float TabuSearch::getBestEvaluation(){
     return best_evaluation;
}

void TabuSearch::printTabu(){
    for(int i=0; i < tabu.size(); i++)
        tabu[i]->printPath();
}

//Neighbors functions
void TabuSearch::generateNeighbors(Solution* object){

    //delete old neighborhood
    for(int i = 0; i < neighborhood_size; i++){        
        if(neighbors[i] == nullptr)
            break;

        else{
            delete neighbors[i];
            neighbors[i] = nullptr;
        }
    }

    
    //Generate new neighbors
    for(int i = 0; i < neighborhood_size; i++){
        int is_unique_counter = 5;
        Solution* new_sol = generateNeighbor(object);
        bool is_unique = !isNeighbor(new_sol);
        
        while(is_unique == false){
            if(new_sol != nullptr){
                delete new_sol;
                new_sol = nullptr;
            }
            new_sol = generateNeighbor(object);
            is_unique = !isNeighbor(new_sol);
            is_unique_counter--;
            if(is_unique_counter==0)
                break;
        }
        
        //Dev msg
        /*
        if(is_unique_counter == 0){
            std::cout << "Unique counter is 0. Check if everything is all right.\n";
        }
        */

        neighbors[i] = new_sol;
    }

    /*
    //Print new neighbors
    for(int i = 0; i < neighborhood_size; i++)
        neighbors[i]->printPath();
    */

    //Evaluate new neighbors
    for(int i = 0; i < neighborhood_size; i++){
        float score = problem->evalutateSolution(neighbors[i]);
        //std::cout << score << "\n";
        evaluation[i] = score;
    }

    
}

//Generates new solution based on new one.
Solution* TabuSearch::generateNeighbor(Solution* object){
    //return swap(object);
   return invert(object);
}

//Generates new solution based on new one.
Solution* TabuSearch::swap(Solution* object){

    Solution* new_sol = clone(object);
    int dimension = object->getPathSize();
    int first_index = rand() % dimension;
    int second_index = rand() % dimension;
    
    //Make sure that indexes arent equal
    while(second_index == first_index)
        second_index = rand() % dimension;

    int fist_value = new_sol->getValueAt(first_index);
    int second_value = new_sol->getValueAt(second_index);

    new_sol->setValueAt(first_index, second_value);
    new_sol->setValueAt(second_index, fist_value);

    return new_sol;
}

Solution* TabuSearch::invert(Solution* object){
    
    Solution* new_sol = clone(object);
    int dimension = new_sol ->getPathSize();
    int start = rand() % dimension;
    int end = rand() % dimension;
    
    //Make sure that indexes arent equal
    while(start == end)
        end = rand() % dimension;

    if(start>end){
        int temp = start;
        start = end;
        end = temp;
    }

    for(int i = 0; i + start < end; i++){
        int temp = new_sol->getValueAt(start+i);
        new_sol->setValueAt(start+i, new_sol->getValueAt(end-i));
        new_sol->setValueAt(end-i, temp); 
             
    }
    return new_sol;
}

//help functions
//clone solution
Solution* TabuSearch::clone(Solution* object){
    Solution* solution_ptr = new Solution(problem->getDimension());
    for(int i = 0 ; i < solution_ptr->getPathSize(); i++){
        solution_ptr->setValueAt(i, object->getValueAt(i));
    }
    return solution_ptr;
}

bool TabuSearch::isEqual(Solution* obj1, Solution* obj2){
    if(obj1->getPathSize() != obj2->getPathSize())
        return false;

    for(int i = 0; i < obj1->getPathSize(); i++){
        if(obj1->getValueAt(i) != obj2->getValueAt(i))
            return false;
    }

    return true;
}

//Check if object is in tabu list
bool TabuSearch::isTabu(Solution* object){
    for(int i = 0; i < tabu_size; i++){
        if(tabu[i] == nullptr)
            break;
        if(isEqual(object, tabu[i]))
            return true;
    }
    return false;
}

//Check if object is in neighbor list
 bool TabuSearch::isNeighbor(Solution* object){
    for(int i = 0; i < neighborhood_size; i++){
        if(neighbors[i] == nullptr)
            return false;
        if(isEqual(object, neighbors[i]))
            return true;
        
    }
    return false;
}

float TabuSearch::getBestScore(){
    float best_score = -1;
    for(int i = 0; i < neighborhood_size; i++){
        float score = evaluation[i];
        if(best_score == -1 || best_score > score){
            best_score = score;
        }
    }
    return best_score;

}
float TabuSearch::getAvgScore(){
    float sum = 0;
    for(int i = 0; i < neighborhood_size; i++){
        sum += evaluation[i]; 
    }
    sum = sum / neighborhood_size;
    return sum;

}
float TabuSearch::getWorstScore(){
    float worst_score = -1;
    for(int i = 0; i < neighborhood_size; i++){
        float score = evaluation[i];
        if(worst_score == -1 || worst_score  < score){
            worst_score = score;
        }
    }
    return worst_score;
}

/////////////////////////
// Simulated Annealing //
/////////////////////////
SimulatedAnnealing::SimulatedAnnealing(cVRP* problem, int neighborhood_size, float start_temperature, int step, float multiplier) : Solver(problem){
    this->step = step;
    this->multiplier = multiplier;
    this->neighborhood_size = neighborhood_size;
    this->temperature = start_temperature;
    initialize();
}

//Destructor
SimulatedAnnealing::~SimulatedAnnealing(){
    problem = nullptr;

    //Clean memory from neighbors
    for(int i = 0; i < neighborhood_size; i++){
        delete neighbors[i];
    }

    //clean rest of memory
    delete[] neighbors;
    delete[] evaluation;
    delete current_solution;
    delete best_solution;
}

//initialize SimulatedAnnealing
void SimulatedAnnealing::initialize(){    
    current_solution = generateRandomSolution();
    best_solution = clone(current_solution);
    current_evaluation = problem->evalutateSolution(current_solution);
    neighbors = new Solution*[neighborhood_size];
    evaluation = new float[neighborhood_size];
    best_evaluation = current_evaluation;
    t = 0;

    for(int i = 0; i < neighborhood_size; i++){
        neighbors[i] = nullptr;
    }



}

//main function of searcher
void SimulatedAnnealing::annealing(int iterations){
    for(int i = 0; i < iterations; i++){ 
        generateNeighbors(current_solution);
        int best_neighbor_index = getBestOfNeighbors();

        // Calculate temp
        float diff = current_evaluation - evaluation[best_neighbor_index];
        float tolerance = exp((diff)/temperature);
        float choice = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        // if(current_evaluation < evaluation[best_neighbor_index])
        //std::cout << "diff = "<< diff << " \t tolerance = " << tolerance << " \t chance = " << choice << "\n";

        //Move forward to next best place or check temp
        if(current_evaluation > evaluation[best_neighbor_index] || choice < tolerance){
            delete current_solution;
            current_solution = clone(neighbors[best_neighbor_index]);
            current_evaluation = evaluation[best_neighbor_index];
        

            //Check if best path is found
            if(evaluation[best_neighbor_index] < best_evaluation){
                    delete best_solution;
                    best_solution = clone(neighbors[best_neighbor_index]);
                    best_evaluation = evaluation[best_neighbor_index];
            }
        }


        t++; // t+1
        if(t>=step){
            temperature = temperature * multiplier;
            t = 0;
        }
    }
}


int SimulatedAnnealing::getBestOfNeighbors(){
    float best = -1;
    int index = 0;
    for(int i = 0; i < neighborhood_size; i++){
        float score = evaluation[i];
        if(best==-1 || best > score){
                best = evaluation[i];
                index = i;
        }
        
    }
    return index;
}

//Output functions
Solution* SimulatedAnnealing::getBest(){
    return best_solution;
}

float SimulatedAnnealing::getBestEvaluation(){
     return best_evaluation;
}


void SimulatedAnnealing::generateNeighbors(Solution* object){

    //delete old neighborhood
    for(int i = 0; i < neighborhood_size; i++){        
        if(neighbors[i] == nullptr)
            break;

        else{
            delete neighbors[i];
            neighbors[i] = nullptr;
        }
    }

    
    //Generate new neighbors
    for(int i = 0; i < neighborhood_size; i++){
        int is_unique_counter = 5;
        Solution* new_sol = generateNeighbor(object);
        bool is_unique = !isNeighbor(new_sol);
        
        while(is_unique == false){
            if(new_sol != nullptr){
                delete new_sol;
                new_sol = nullptr;
            }
            new_sol = generateNeighbor(object);
            is_unique = !isNeighbor(new_sol);
            is_unique_counter--;
            if(is_unique_counter==0)
                break;
        }
        
        //Dev msg
        /*
        if(is_unique_counter == 0){
            std::cout << "Unique counter is 0. Check if everything is all right.\n";
        }
        */

        neighbors[i] = new_sol;
    }

    /*
    //Print new neighbors
    for(int i = 0; i < neighborhood_size; i++)
        neighbors[i]->printPath();
    */

    //Evaluate new neighbors
    for(int i = 0; i < neighborhood_size; i++){
        float score = problem->evalutateSolution(neighbors[i]);
        //std::cout << score << "\n";
        evaluation[i] = score;
    }

    
}

//Generates new solution based on new one.
Solution* SimulatedAnnealing::generateNeighbor(Solution* object){
    //return swap(object);
   return invert(object);
}

//Generates new solution based on new one.
Solution* SimulatedAnnealing::swap(Solution* object){

    Solution* new_sol = clone(object);
    int dimension = object->getPathSize();
    int first_index = rand() % dimension;
    int second_index = rand() % dimension;
    
    //Make sure that indexes arent equal
    while(second_index == first_index)
        second_index = rand() % dimension;

    int fist_value = new_sol->getValueAt(first_index);
    int second_value = new_sol->getValueAt(second_index);

    new_sol->setValueAt(first_index, second_value);
    new_sol->setValueAt(second_index, fist_value);

    return new_sol;
}

Solution* SimulatedAnnealing::invert(Solution* object){
    
    Solution* new_sol = clone(object);
    int dimension = new_sol ->getPathSize();
    int start = rand() % dimension;
    int end = rand() % dimension;
    
    //Make sure that indexes arent equal
    while(start == end)
        end = rand() % dimension;

    if(start>end){
        int temp = start;
        start = end;
        end = temp;
    }

    for(int i = 0; i + start < end; i++){
        int temp = new_sol->getValueAt(start+i);
        new_sol->setValueAt(start+i, new_sol->getValueAt(end-i));
        new_sol->setValueAt(end-i, temp); 
             
    }
    return new_sol;
}


//Help functions
Solution* SimulatedAnnealing::clone(Solution* object){
    Solution* solution_ptr = new Solution(problem->getDimension());
    for(int i = 0 ; i < solution_ptr->getPathSize(); i++){
        solution_ptr->setValueAt(i, object->getValueAt(i));
    }
    return solution_ptr;
}

bool SimulatedAnnealing::isEqual(Solution* obj1, Solution* obj2){
    if(obj1->getPathSize() != obj2->getPathSize())
        return false;

    for(int i = 0; i < obj1->getPathSize(); i++){
        if(obj1->getValueAt(i) != obj2->getValueAt(i))
            return false;
    }

    return true;
}
//Check if object is in neighbor list
 bool SimulatedAnnealing::isNeighbor(Solution* object){
    for(int i = 0; i < neighborhood_size; i++){
        if(neighbors[i] == nullptr)
            return false;
        if(isEqual(object, neighbors[i]))
            return true;
        
    }
    return false;
}
float SimulatedAnnealing::getBestScore(){
    float best_score = -1;
    for(int i = 0; i < neighborhood_size; i++){
        float score = evaluation[i];
        if(best_score == -1 || best_score > score){
            best_score = score;
        }
    }
    return best_score;


}
float SimulatedAnnealing::getCurrentScore(){
    return current_evaluation;
}
float SimulatedAnnealing::getAvgScore(){
    float sum = 0;
    for(int i = 0; i < neighborhood_size; i++){
        sum += evaluation[i]; 
    }
    sum = sum / neighborhood_size;
    return sum;

}
float SimulatedAnnealing::getWorstScore(){
    float worst_score = -1;
    for(int i = 0; i < neighborhood_size; i++){
        float score = evaluation[i];
        if(worst_score == -1 || worst_score  < score){
            worst_score = score;
        }
    }
    return worst_score;
}
float SimulatedAnnealing::getTemperature(){
    return temperature;
}

/////////////////////////
///EA with temp hybrid///
/////////////////////////
EA_TS_Hybrid::EA_TS_Hybrid(cVRP* problem, int pop_size, float cross, float mutate, int neighborhood_size, float start_temperature, int step_temp, float multiplier,int boost_iterations, float n_boost, int boost_step):
Evolution(problem, pop_size, cross, mutate), neighborhood_size(neighborhood_size), temperature(start_temperature), temp_step(step_temp), temp_multiplier(multiplier), boost_iterations(boost_iterations), n_boost(n_boost), boost_step(boost_step){
    step = 0;
}

Solution** EA_TS_Hybrid::generateNeighbors(Solution* object){
    Solution** neighbors = new Solution*[neighborhood_size];
    for(int i = 0; i < neighborhood_size; i++){
        neighbors[i] = generateNeighbor(object);
    }
    return neighbors;
}
Solution* EA_TS_Hybrid::generateNeighbor(Solution* object){
    Solution* new_sol = clone(object);
    int dimension = new_sol ->getPathSize();
    int start = rand() % dimension;
    int end = rand() % dimension;
    
    //Make sure that indexes arent equal
    while(start == end)
        end = rand() % dimension;

    if(start>end){
        int temp = start;
        start = end;
        end = temp;
    }

    for(int i = 0; i + start < end; i++){
        int temp = new_sol->getValueAt(start+i);
        new_sol->setValueAt(start+i, new_sol->getValueAt(end-i));
        new_sol->setValueAt(end-i, temp); 
             
    }
    return new_sol;
}


void EA_TS_Hybrid::boost(){
    
    // std::cout << "BOOST!\n";
    int boost_size = n_boost * population_size;
    int indexes_array[boost_size];

    for(int i = 0; i < boost_size; i++){
        indexes_array[i] = rand() % population_size;
        // std::cout<< indexes_array[i] << " ";
    }
    //  std::cout << "CHOSEN!\n";
    
    for(int i = 0; i < boost_size; i++){
        Solution* current_solution = clone(population[indexes_array[i]]);
        float old_evaluation = evaluation[indexes_array[i]];
        float current_evaluation = old_evaluation;
        Solution* best_solution = clone(current_solution);
        float best_evaluation = current_evaluation;

        Solution** neighbors;
        // std::cout << "GENERATED NEEDED SOLUTIONS!\n";
        int t = 0;
        float local_temp = temperature;
        
        for(int j = 0; j < boost_iterations; j++){ 
            neighbors = generateNeighbors(current_solution);
            // std::cout << "UPDATE NEIGBORS!\n";
            int best_neighbor_index = -1; 
            float neighborhood_eval = -1;

            //Get best neighbor
            for(int z = 0; z < neighborhood_size; z++){
                    float l_score = problem->evalutateSolution(neighbors[z]);
                    if(best_neighbor_index == -1 || neighborhood_eval > l_score){
                            best_neighbor_index = z;
                            neighborhood_eval = l_score;
                    }
                      
            }
            // std::cout << "GET BEST!\n";
            // std::cout << "index; " << best_neighbor_index << " score : " << neighborhood_eval;
            // Calculate temp
            float diff = current_evaluation - neighborhood_eval;
            float tolerance = exp((diff)/temperature);
            float choice = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            // std::cout << "CALCULATE P \n";
            //Move forward to next best place or check temp
            if(current_evaluation > neighborhood_eval || choice < tolerance){
                delete current_solution;
                current_solution = clone(neighbors[best_neighbor_index]);
                current_evaluation = neighborhood_eval;
            
                // std::cout << "UPDATE CURRENT P \n";
                //Check if best path is found
                if(neighborhood_eval < best_evaluation){
                        delete best_solution;
                        best_solution = clone(neighbors[best_neighbor_index]);
                        best_evaluation = neighborhood_eval;
                        // std::cout << "UPDATE BEST P \n";
                }
                for(int s = 0; s < neighborhood_size; s++)
                    delete neighbors[s];
                delete[] neighbors;
                

            }

            t++; // t+1
            if(t>=temp_step){
                // std::cout<< "T = " << local_temp << "\n";
                local_temp = local_temp * temp_multiplier;
                t = 0;
            }
        }

        if(best_evaluation < old_evaluation){
            delete population[indexes_array[i]];
            population[indexes_array[i]] = best_solution;
            evaluation[indexes_array[i]] = best_evaluation;
            best_solution = nullptr;
        }
        delete current_solution;
        delete best_solution;
        for(int s = 0; s < neighborhood_size; s++)
            delete neighbors[s];
        delete[] neighbors;
    }

}
void EA_TS_Hybrid::boosted_evolution(int generation_limit){
    int iteration = 0;
    while(iteration < generation_limit){
        //std::cout << "Generation no. " << iteration + 1 << "\n";
        Solution** new_pop = new Solution*[population_size];  
        for(int i = 0; i < population_size; i++){
            Solution* child;
            int index_one = select();
            //std::cout << "index one = " << index_one << "\n";
            int index_two = -1;
            Solution* parent_one = population[index_one];
            float cross = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float mutate = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            
            if (cross <= crossing_probablity){
                //std::cout << "CROSS!\n";
                index_two = select();
                Solution* parent_two = population[index_two];
                child = crossover(parent_one, parent_two);
                parent_two = nullptr;

            }
            else {
                child = clone(parent_one);
            }

            if( mutate <= mutation_probablity){
                mutation(child);
            }
            new_pop[i] = child;
            child = nullptr;
            parent_one = nullptr;
            
            
        }
        
        
        //clean memory and old population
        for( int i = 0; i < population_size; i++){
            delete population[i];
            population[i] = new_pop[i];
            new_pop[i] = nullptr;
        }
        
        delete[] new_pop;

        //Evaluate new population
        evaluate();
        
        //boost
        step++;
        if(step >= boost_step){
            step = 0;
            boost();
        }

        iteration++;
    }

}

/////////////////////////
///EA with temp hybrid///
/////////////////////////
EA_Temp_Hybrid::EA_Temp_Hybrid(cVRP* problem, int pop_size, float cross, float mutate, float start_temperature, int step_temp, float multiplier) : 
Evolution(problem, pop_size, cross, mutate), temperature(start_temperature),temp_step(step_temp), temp_multiplier(multiplier){step = 0;}


// Overwritten main function
void EA_Temp_Hybrid::hybrid_evolution(int generation_limit){
    
    int iteration = 0;
    

    while(iteration < generation_limit){
        //std::cout << "Generation no. " << iteration + 1 << "\n";
        Solution** new_pop = new Solution*[population_size];  
        float* new_evaluation = new float[population_size];

        for(int i = 0; i < population_size; i++){
            Solution* child;
            int index_one = select();
            //std::cout << "index one = " << index_one << "\n";
            int index_two = -1;
            Solution* parent_one = population[index_one];
            float cross = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

            if (cross <= crossing_probablity){
                //std::cout << "CROSS!\n";
                index_two = select();
                Solution* parent_two = population[index_two];
                child = crossover(parent_one, parent_two);

            }
            else {
                child = clone(parent_one);

            }

            Solution* neighbor = clone(child);
            mutation(neighbor);
            float c_evaluation = problem->evalutateSolution(child);
            float n_evaluation = problem->evalutateSolution(neighbor);
            // Calculate temp
            // std::cout << "T = " << temperature << " ";
            float diff = c_evaluation - n_evaluation;
            float tolerance = exp((diff)/temperature) * cross;
            // std::cout <<" dif = " << diff << " P = " << tolerance << " \n";
            float choice = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if(c_evaluation > n_evaluation || choice < tolerance ){
                // std::cout << "Mutate!";
                delete child;
                child = neighbor;
                neighbor = nullptr;
                c_evaluation = n_evaluation;
            }
            else{
                delete neighbor;
                neighbor = nullptr;
            }
            
            new_pop[i] = child;
            new_evaluation[i] = c_evaluation;
            child = nullptr;
        }
        
        
        //clean memory and old population
        for( int i = 0; i < population_size; i++){
            delete population[i];
            population[i] = new_pop[i];
            new_pop[i] = nullptr;
        }
        
        delete[] new_pop;

        //Evaluate new population
        delete[] evaluation;
        evaluation = new_evaluation;
        new_evaluation = nullptr;

        iteration++;
        step++;
        // std::cout << "T = " << temperature << "\n";
        if(step>=temp_step){
            temperature = temperature * temp_multiplier;
            step = 0;
        }
    }
}