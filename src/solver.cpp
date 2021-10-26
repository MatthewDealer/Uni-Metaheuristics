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


//Evolutionary algorithm
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

    for(int j = start_point; j <= end_point; j++){
        for(int i = 0; i < size; i++){
            if(child->getValueAt(i) == parent_two->getValueAt(j)){
                child->setValueAt(i, parent_one->getValueAt(j));
            }
        }
    }

    for(int i = start_point; i <= end_point; i++){
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
        if(start+i != end-i){
            int temp = object->getValueAt(start+i);
            object->setValueAt(start+i, object->getValueAt(end-i));
            object->setValueAt(end-i, temp); 
        }
             
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