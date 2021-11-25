#include "../include/researcher.hpp"

//////////////Researcher//////////////
Researcher::~Researcher(){
    delete log;
}
void Researcher::setTestsCount(int count){
    this->tests_count = count;
}
void Researcher::setExNumber(int number){
    this->exercise_number = number;
}
void Researcher::setSampleCount(int count){
    this->sample_count = count;
}

void Researcher::setIterShift(int shift){
    this->iteration_shift = shift;
}
void Researcher::setIterations(int size){
    this->iteration_limit = size;
}

////////////EA_Researcher////////////
void EA_Researcher::setCrossShift(float shift){
    this->cross_shift = shift;
}

void EA_Researcher::setMutateShift(float shift){
    this->mutate_shift = shift;
    // std::cout << mutate_shift << "\n";
}

void EA_Researcher::setPopShift(int shift){
    this->pop_shift = shift;
}
void EA_Researcher::setTournamentSize(int size){
    this->tournament_size = size;
}

void EA_Researcher::setPTournamentShift(int shift){
    this->tournament_shift = shift;
}

void EA_Researcher::setCross(float p){
    this->cross_probability = p;
}
void EA_Researcher::setMutate(float p){
    this->mutate_probability = p;
}
void EA_Researcher::setPopSize(int size){
    this->pop_size = size;
}
void EA_Researcher::setTSize(int size){
    this->tournament_size = size;
}
void EA_Researcher::setIterations(int size){
    this->iteration_limit = size;
}

void EA_Researcher::research(){
    std::string file_name = (std::string) problem_paths[exercise_number];

    std::cout << "\n=================\n";
    std::cout << "===EA Research===\n";
    std::cout << "=================\n";

    cVRP* prob;
    Loader load_one(file_name);
    prob = load_one.loadProblem();
    
    std::cout << "Exercise number: " << this->exercise_number << "\n";
    std::cout << "Vehicle capacity: " << prob->getVehicleCapacity() << "\n";
    std::cout << "Dimension: " << prob->getDimension() << "\n";
    std::cout << "______________________________________________________\n";
    std::cout << "\nStart params:\n";
    std::cout << "Generations = " << iteration_limit << "\n";
    std::cout << "Population size = " << pop_size << "\n";
    std::cout << "Cross probability = " << cross_probability << "\n";
    std::cout << "Mutate probability = " << mutate_probability << "\n";
    std::cout << "Tournament Size = " << tournament_size  << "\n";
    std::cout << "______________________________________________________\n";


    float best_avg = 10000000;
    int best_test_index = 0;
    int output_iters = iteration_limit;
    int output_pop_size = pop_size;
    float output_cross_probability = cross_probability;
    float output_mutate_probability = mutate_probability;
    int output_t_size = tournament_size;

    for(int i = 0; i < tests_count; i++){
        std:: cout << "Test " << i+1 << " out of " << tests_count << " . . . \n";
        float best = 100000;
        float avg = 0;
        float worst = 0;

        for(int sample = 0; sample < sample_count; sample++){
            std::cout << "[";
            for(int j = 0; j < sample_count; j++){
                if( j <= sample)    
                    std::cout << "=";
                else
                    std::cout << " ";
            }
            float progress = (sample+1)/(double)sample_count * 100;
            std::cout << "] " << progress << "%\r";
                
            Evolution ea_solver(prob, pop_size, cross_probability, mutate_probability);
            if(select_mode = selection_type::tournament){
                ea_solver.setTournamentSize(tournament_size); 
            }
            ea_solver.evolution(iteration_limit);
            float score = ea_solver.getBestScore();
            avg += score;
            if(score < best)
                best = score;
            if(score > worst)
                worst = score;
            std::cout.flush();
        }
        std::cout << std::endl;
        avg = avg / (double)sample_count;
        std::cout << "Avg = " << avg << "\n";
        if( avg < best_avg ){
            best_avg = avg;
            best_test_index = i;
            
            // Save parameters
            output_iters = iteration_limit;
            output_pop_size = pop_size;
            output_cross_probability = cross_probability;
            output_mutate_probability = mutate_probability;
            output_t_size = tournament_size;

        }
        std::vector <std::string> output_string;
        output_string.push_back(std::to_string(i));
        output_string.push_back(std::to_string(pop_size));
        output_string.push_back(std::to_string(iteration_limit));
        output_string.push_back(std::to_string(cross_probability));
        output_string.push_back(std::to_string(mutate_probability));
        output_string.push_back(std::to_string(tournament_size));
        output_string.push_back(std::to_string(best));
        output_string.push_back(std::to_string(avg));
        output_string.push_back(std::to_string(worst));
        log->LogToFile(output_string);

        iteration_limit += iteration_shift;
        pop_size += pop_shift;
        cross_probability += cross_shift;
        mutate_probability += mutate_shift;
        tournament_size += tournament_shift;

    }

    std::cout <<"\n--------------------------------------------\n";
     std::cout << "Best test = " << best_test_index+1 << "\n";
    std::cout << "Iter = " << output_iters << ", Pop size = " << output_pop_size << ", Cross p = " << output_cross_probability << ", Mutate p = " << output_mutate_probability << ", T size = " << output_t_size << "\n";
    std::cout <<"--------------------------------------------\n";
    
    iteration_limit = output_iters;
    pop_size = output_pop_size;
    cross_probability = output_cross_probability;
    mutate_probability = output_mutate_probability;
    tournament_size = output_t_size;
    delete prob;
}

////////////TS_Researcher////////////
void TS_Researcher::setNShift(int shift){
    this->n_shift = shift;
}

void TS_Researcher::setTShift(int shift){
    this->t_shift = shift;
}

void TS_Researcher::setNSize(int size){
    this->n_size = size;
}
void TS_Researcher::setTabuSize(int size){
    this->t_size = size;
}

void TS_Researcher::research(){
    
    std::string file_name = (std::string) problem_paths[exercise_number];
    std::cout << "\n=================\n";
    std::cout << "===TS Research===\n";
    std::cout << "=================\n";
    
    cVRP* prob;
    Loader load_one(file_name);
    prob = load_one.loadProblem();
    
    std::cout << "Exercise number: " << this->exercise_number << "\n";
    std::cout << "Vehicle capacity: " << prob->getVehicleCapacity() << "\n";
    std::cout << "Dimension: " << prob->getDimension() << "\n";
    std::cout << "______________________________________________________\n";
    std::cout << "\nStart params:\n";
    std::cout << "Iterations = " << iteration_limit << "\n";
    std::cout << "N size = " << n_size << "\n";
    std::cout << "Tabu size = " << t_size << "\n";
    std::cout << "______________________________________________________\n";


    float best_avg = 10000000;
        
    int best_test_index = 0;
    int output_iters = iteration_limit;
    int output_n_size = n_size;
    int output_t_size = t_size;


    for(int i = 0; i < tests_count; i++){
        std:: cout << "Test " << i+1 << " out of " << tests_count << " . . . \n";
        float best = 100000;
        float avg = 0;
        float worst = 0;
        for(int sample = 0; sample < sample_count; sample++){
            std::cout << "[";
            for(int j = 0; j < sample_count; j++){
                if( j <= sample)    
                    std::cout << "=";
                else
                    std::cout << " ";
            }
            float progress = (sample+1)/(double)sample_count * 100;
            std::cout << "] " << progress << "%\r";
            TabuSearch solver(prob, n_size, t_size);
            solver.search(iteration_limit);
            float score = solver.getBestScore();
            avg += score;
            if(score < best)
                best = score;
            if(score > worst)
                worst = score;
            std::cout.flush();
        }
        std::cout << std::endl;
        avg = avg / (double)sample_count;
        std::cout << "Avg = " << avg << "\n";
        if( avg < best_avg ){
            best_avg = avg;
            best_test_index = i;
            // Save parameters
            output_iters = iteration_limit;
            output_n_size = n_size;
            output_t_size = t_size;
        }

        std::vector <std::string> output_string;
        output_string.push_back(std::to_string(i));
        output_string.push_back(std::to_string(iteration_limit));
        output_string.push_back(std::to_string(n_size));
        output_string.push_back(std::to_string(t_size));
        output_string.push_back(std::to_string(best));
        output_string.push_back(std::to_string(avg));
        output_string.push_back(std::to_string(worst));
        log->LogToFile(output_string);

        n_size += n_shift;
        iteration_limit += iteration_shift;
        t_size += t_shift;


    }


    std::cout <<"\n--------------------------------------------\n";
    std::cout << "Best test = " << best_test_index+1 << "\n";
    std::cout << "Iter = " << output_iters << ", N size = " << output_n_size << ", T size = " << output_t_size << "\n";
    std::cout <<"--------------------------------------------\n";
    iteration_limit = output_iters;
    n_size = output_n_size;
    t_size = output_t_size;
    delete prob;
}

////////////SA_Researcher////////////
void SA_Researcher::setNShift(int shift){
    this->n_shift = shift;
}

void SA_Researcher::setTempShift(float shift){
    this->temp_shift = shift;
}

void SA_Researcher::setMultiplierShift(float shift){
    this->multiplier_shift = shift;
}

void SA_Researcher::setStepShift(int shift){
    this->step_shift = shift;
}

void SA_Researcher::setTemp(int value){
    this->temperature = value;
}
void SA_Researcher::setNsize(int size){
    this->n_size = size;
}
void SA_Researcher::setMultiplier(float value){
    this->temp_multiplier = value;
}
void SA_Researcher::setStep(int step){
    this->temp_step = step;
}

void SA_Researcher::research(){
    std::string file_name = (std::string) problem_paths[exercise_number];

    std::cout << "\n=================\n";
    std::cout << "===SA Research===\n";
    std::cout << "=================\n";

    cVRP* prob;
    Loader load_one(file_name);
    prob = load_one.loadProblem();
    
    std::cout << "Exercise number: " << this->exercise_number << "\n";
    std::cout << "Vehicle capacity: " << prob->getVehicleCapacity() << "\n";
    std::cout << "Dimension: " << prob->getDimension() << "\n";
    std::cout << "______________________________________________________\n";
    std::cout << "\nStart params:\n";
    std::cout << "Iterations = " << iteration_limit << "\n";
    std::cout << "N size = " << n_size << "\n";
    std::cout << "Start temp = " << temperature << "\n";
    std::cout << "Multiplier = " << temp_multiplier << "\n";
    std::cout << "Step = " << temp_step  << "\n";
    std::cout << "______________________________________________________\n";


    float best_avg = 10000000;
    
    int best_test_index = 0;
    int output_iters = iteration_limit;
    int output_n_size = n_size;
    float output_temp = temperature;
    float output_multiplier = temp_multiplier;
    int output_temp_step = temp_step;

    for(int i = 0; i < tests_count; i++){
        std:: cout << "Test " << i+1 << " out of " << tests_count << " . . . \n";
        float best = 100000;
        float avg = 0;
        float worst = 0;
        for(int sample = 0; sample < sample_count; sample++){
            std::cout << "[";
            for(int j = 0; j < sample_count; j++){
                if( j <= sample)    
                    std::cout << "=";
                else
                    std::cout << " ";
            }
            float progress = (sample+1)/(double)sample_count * 100;
            std::cout << "] " << progress << "%\r";

            SimulatedAnnealing solver(prob, n_size, temperature, temp_step, temp_multiplier);
            solver.annealing(iteration_limit);
            float score = solver.getBestScore();
            avg += score;
            if(score < best)
                best = score;
            if(score > worst)
                worst = score;
            std::cout.flush();
        }
        std::cout << std::endl;
        avg = avg / (double)sample_count;
        std::cout << "Avg = " << avg << "\n";
        if( avg < best_avg ){
            best_avg = avg;
            
            // Save parameters
            best_test_index = i;
            output_iters = iteration_limit;
            output_n_size = n_size;
            output_temp = temperature;
            output_multiplier = temp_multiplier;
            output_temp_step = temp_step;



        }

        std::vector <std::string> output_string;
        output_string.push_back(std::to_string(i));
        output_string.push_back(std::to_string(iteration_limit));
        output_string.push_back(std::to_string(n_size));
        output_string.push_back(std::to_string(temperature));
        output_string.push_back(std::to_string(temp_multiplier));
        output_string.push_back(std::to_string(temp_step));
        output_string.push_back(std::to_string(best));
        output_string.push_back(std::to_string(avg));
        output_string.push_back(std::to_string(worst));
        log->LogToFile(output_string);

        iteration_limit += iteration_shift;
        n_size += n_shift;
        temperature += temp_shift;
        temp_multiplier += multiplier_shift;
        temp_step += step_shift;

    }
    std::cout <<"\n--------------------------------------------\n";
    std::cout << "Best test = " << best_test_index+1 << "\n";
    std::cout << "Iter = " << output_iters << ", N size = " << output_n_size << ", Temp = " << output_temp << ", Multiplier = " << output_multiplier << ", Step = " << output_temp_step << "\n";
    std::cout <<"--------------------------------------------\n";
    iteration_limit = output_iters;
    n_size = output_n_size;
    temperature = output_temp;
    temp_multiplier = output_multiplier;
    temp_step = output_temp_step;
    delete prob;
}