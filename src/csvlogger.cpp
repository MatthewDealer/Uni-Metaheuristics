#include "../include/csvlogger.hpp"


Logger::Logger(std::string path, cVRP* problem){
    this->problem = problem;
    this->file_name = path;
    file.open(file_name);
}
Logger::~Logger(){
    file.close();
}

void Logger::runTest(Evolution* evolution_solver, int generations_limit,int evolution_step){

    //evolution_solver->printPop();
    std::cout << "__________________________________________________________________\n";
    //Test evolution 
    //file << "iteration,best,avg,worst,\n";
    int iterations = generations_limit/evolution_step;
    for(int i = 0; i <=iterations; i++){
        if(i == 0){
            float best = evolution_solver->getBestScore();
            float avg = evolution_solver->getAvgScore();
            float worst = evolution_solver->getWorstScore();
            std::cout << best << " - " << avg << " - " << worst <<"\n";
            file << i << "," << best << "," << avg << "," << worst <<",\n";
        }
        else{
            std::cout << "Iteration no. " << i +1<<"\n";
            evolution_solver->evolution(evolution_step);
            //evolution_solver->printPop();
            float best = evolution_solver->getBestScore();
            float avg = evolution_solver->getAvgScore();
            float worst = evolution_solver->getWorstScore();
            std::cout << best << " - " << avg << " - " << worst <<"\n";
            file << i << "," << best << "," << avg << "," << worst <<",\n";
        }
    }
    std::cout << "Done!\n";
}

//Test Tabu Search
void Logger::runTsTest(int generations_limit, int step, int neighborhood_size, int tabu_size){
    //Test Ts 
    TabuSearch ts(problem, neighborhood_size, tabu_size);

    int iterations = generations_limit/step;
    for(int i = 0; i < iterations; i++){
        std::cout << "Iteration no. " << i + 1 <<"\n";
        ts.search(step);
        float best = ts.getBestEvaluation();
        float current = ts.getBestScore();
        float avg = ts.getAvgScore();
        float worst = ts.getWorstScore();
        //std::cout << best << " - "  << current << " - " << avg << " - " << worst <<"\n";
        file << i+1 << "," << best << ", " << current << "," << avg << "," << worst <<",\n";
    }
    std::cout << "Done!\n";
    std::cout << "Best: ";
    ts.getBest()->printPath();
    std::cout << "Score: " << ts.getBestEvaluation() << "\n";
    /*
    std::cout <<"\n_______________\n";
    std::cout <<"TABU: \n";
    ts.printTabu();
    */
    
}

//Anneling test
void Logger::runAnnelingTest(int generations_limit, int step, int n_size, float start_temperature, int a_step, float multiplier){
    SimulatedAnnealing sa(problem, n_size, start_temperature, a_step, multiplier);

    int iterations = generations_limit/step;
    for(int i = 0; i < iterations; i++){
        std::cout << "Iteration no. " << i + 1 << " \tTemperature = " << sa.getTemperature() <<"\n";
        sa.annealing(step);
        float best = sa.getBestEvaluation();
        float current = sa.getCurrentScore();

        //std::cout << best << " - "  << current << " - " << avg << " - " << worst <<"\n";
        file << i+1 << "," << best << ", " << current <<",\n";
    }
    std::cout << "Done!\n";
    std::cout << "Best: ";
    sa.printSolution(sa.getBest());
    std::cout << "Score: " << sa.getBestEvaluation() << "\n";
}


//Compare evoltuion, random and greedy
void Logger::runCompareLog(int pop_size, int generations_limit, float cross_prob, float mutate_prob,  int tournament_size, int repeat_count){
    
    //Evolution scores
    float best_evolution[repeat_count];
    float avg_evolution[repeat_count];
    float worst_evolution[repeat_count];

    //Random scores
    float best_random[repeat_count];
    float avg_random[repeat_count];
    float worst_random[repeat_count];

    //Greedy scores
    float best_greedy;
    float avg_greedy;
    float worst_greedy;

    std::cout << "Running tests...\n";

    //Run greedy test (will always give the same results)
    Greedy greedy_solver(problem);
    greedy_solver.generateSolutions();
    best_greedy = greedy_solver.getBestScore();
    avg_greedy = greedy_solver.getAvgScore();
    worst_greedy = greedy_solver.getWorstScore();

    std::cout << "Greedy done.\n";
    std::cout << best_greedy << " - " << avg_greedy <<" - " << worst_greedy <<"\n";
    //Test algorithms
    for(int i = 0; i < repeat_count; i++){
        float best, avg, worst;
        std::cout << "Iteration no. " << i +1 <<"\n";

        //Evolution test
        Evolution evolution_solver(problem, pop_size, cross_prob, mutate_prob);
        evolution_solver.setTournamentSize(tournament_size);
        evolution_solver.evolution(generations_limit);
        best = evolution_solver.getBestScore();
        avg = evolution_solver.getAvgScore();
        worst = evolution_solver.getWorstScore();
        best_evolution[i] = best;
        avg_evolution[i] = avg;
        worst_evolution[i] = worst;
        std::cout << best << " - " << avg << " - " << worst <<"\n";
            
    
        //Random test
        Random random_solver(problem, (pop_size*generations_limit));
        random_solver.genarateSolutions();
        best = random_solver.getBestScore();
        avg = random_solver.getAvgScore();
        worst = random_solver.getWorstScore();
        best_random[i] = best;
        avg_random[i] = avg;
        worst_random[i] = worst;
        std::cout << best << " - " << avg << " - " << worst <<"\n";
       


    }
    std::cout << "Evolution done.\n";
    std::cout << "Random done.\n";

    //Log score to file
    file << ",Evolution,,,Random,,,Greedy,,,\n";
    file << "iteration,best,avg,worst,best,avg,worst,best,avg,worst,\n";
    for(int i = 0; i < repeat_count; i++){
    file << i+1 << "," << best_evolution[i] << "," << avg_evolution[i] << "," << worst_evolution[i] <<",";
    file <<  best_random[i] << "," << avg_random[i] << "," << worst_random[i] <<",";
    file <<  best_greedy << "," << avg_greedy << "," << worst_greedy <<",\n";
    }
    std::cout << "Done!\n";
}

void Logger::runAnnelingLog(int generations_limit,int neighborhood_size,int start_temperature, int anneling_step, float multiplier, int repeat_count){
    
    float scores[repeat_count];

    for(int i = 0; i < repeat_count; i++){
        SimulatedAnnealing sa(problem, neighborhood_size, start_temperature, anneling_step, multiplier);
        std::cout << "Anneling no. " << i + 1 << "\n";
        sa.annealing(generations_limit);
        float best = sa.getBestEvaluation();
        scores[i] = best;
    }
    float best = std::numeric_limits<float>::max(); float avg = 0; float worst = -1;

    for(int i = 0; i < repeat_count; i++){
        avg += scores[i];
        if(best > scores[i])
            best = scores[i];
        
        if(worst < scores[i])
            worst = scores[i];
    }
    avg = avg / repeat_count;

    float std = 0;

    for(int i = 0; i < repeat_count; i++){
        std += pow(avg - scores[i], 2);
    }
    std = sqrt(std/repeat_count);

    file << ", Anneling , ,\n";
    file << best << "," << avg << "," << worst << "," << std <<",\n";


}