#include "../include/researcher.hpp"

//////////////Researcher//////////////
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

    std::cout << file_name << "\n";
    cVRP* prob;
    Loader load_one(file_name);
    prob = load_one.loadProblem();
    
    std::cout << "Vehicle capacity: " << prob->getVehicleCapacity() << "\n";
    std::cout << "Dimension: " << prob->getDimension() << "\n";
    std::cout << "______________________________________________________\n";

    float best_avg = 10000000;

    int output_iters = iteration_limit;
    int output_pop_size = pop_size;
    float output_cross_probability = cross_probability;
    float output_mutate_probability = mutate_probability;
    int output_t_size = tournament_size;

    for(int i = 0; i < tests_count; i++){
        std:: cout << "Test " << i+1 << " out of " << tests_count << " . . . \n";
        float best = 100000;
        float avg = 0;

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
            
            std::cout.flush();
        }
        std::cout << std::endl;
        avg = avg / (double)sample_count;
        std::cout << "Avg = " << avg << "\n";
        if( avg < best_avg ){
            best_avg = avg;
            
            // Save parameters
            output_iters = iteration_limit;
            output_pop_size = pop_size;
            output_cross_probability = cross_probability;
            output_mutate_probability = mutate_probability;
            output_t_size = tournament_size;

        }

        iteration_limit += iteration_shift;
        pop_size += pop_shift;
        cross_probability += cross_shift;
        mutate_probability += mutate_shift;
        tournament_size += tournament_shift;

    }

    std::cout << "Iter = " << output_iters << ", Pop size = " << output_pop_size << ", Cross p = " << output_cross_probability << ", Mutate p = " << output_mutate_probability << ", T size = " << output_t_size << "\n";
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