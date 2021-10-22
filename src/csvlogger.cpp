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

void Logger::runCompareLog(int pop_size, int generations_limit, float cross_prob, float mutate_prob,  int tournament_size){
    /*
    //Compare eloltuion, random and greedy
    Evolution evolution_solver(problem, pop_size, 0.2, 0.2);
    Greedy greedy_solver(problem);
    Random random_solver(problem, pop_size*generations_limit);

    //Log score to file
    file << "This is the first cell in the first column.\n";
    file << "a,b,c,\n";
    file << "c,s,v,\n";
    file << "1,2,3.456\n";
    file << "semi;colon";
    */
    std::cout << "Done!\n";
}