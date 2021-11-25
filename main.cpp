#include <iostream>
#include <vector>
#include "include/loader.hpp"
#include "include/problem.hpp"
#include "include/solution.hpp"
#include "include/solver.hpp"
#include "include/csvlogger.hpp"
#include "include/researcher.hpp"
#include <cstdio>



#define EXERCISE 7

void mutationTest(cVRP* prob){
    Evolution solver(prob, 100, 0.2, 0.2);
    solver.setTournamentSize(5);
    std::cout << "Size: " << solver.getPopulationSize() << "\n";
    Solution* sol_one = solver.generateRandomSolution();
    Solution* sol_two = solver.generateRandomSolution();
    Solution* child = solver.pmCrossover(sol_one, sol_two);

    sol_one->printPath();
    sol_two->printPath();
    child->printPath();
    delete sol_one;
    delete sol_two;
}

void crossoverTest(cVRP* prob){
    //Crosover Test
    Evolution solver(prob, 100, 0.2, 0.2);
    Solution* sol_one = solver.generateRandomSolution();
    Solution* sol_two = solver.generateRandomSolution();
    sol_one->printPath();
    sol_two->printPath();
    std::cout << "__Crossover__\n";
    Solution* child = solver.crossover(sol_one, sol_two);
    child->printPath();
    delete sol_one;
    delete sol_two;
}

void exerciseOne(cVRP* prob){
    //Logger test
    std::string number = std::to_string(EXERCISE);
    std::string output_file = "../datasheets/Evolution_perfect_log_turbo_d" + number + ".csv";
    
    Logger log(output_file, prob);

    //EA parameters
    int population_size = 2000;
    int generation_limit = 500;
    float cross_prob = 0.86;
    float mutate_prob = 0.48; 
    int tournament_size = 8;
    
    //Log parameters
    int step_evolution = 20;
    int repeat_count = 10;

    Evolution evolution_solver(prob, population_size, cross_prob, mutate_prob); 
    evolution_solver.setTournamentSize(tournament_size);

    
    //Evolution algorithm test
    // log.runTest(&evolution_solver, generation_limit, step_evolution);
    // std::cout << "Best path:\n";
    // Solution* best = evolution_solver.getBest();
    // evolution_solver.printSolution(best);
    // std::cout << "Score: " << prob->evalutateSolution(best) << "\n";
    // std::cout << "________________________________________________\n";
    // prob->evalutateSolution(best);
    
    log.runEALog(population_size, generation_limit, cross_prob, mutate_prob, tournament_size, repeat_count);
}

void exerciseTwo(cVRP* prob){
    //Tabu search test
    std::string number = std::to_string(EXERCISE);
    std::string output_file = "../datasheets/TabuSearch_perfect_log" + number + ".csv";
    Logger log(output_file, prob);

    // Sa parameters
    int neighborhood_size = 70;
    float tabu_size = 48;
    int iteration_limit = 5000;

    //Log parameters
    int step = 1;
    int repeat_count = 10;

    //log.runTsTest(iteration_limit, step, neighborhood_size, tabu_size);
    log.runTsLog(iteration_limit, step, neighborhood_size, tabu_size, repeat_count);

}

void exerciseThree(cVRP* prob){
    //Simulated annealing test
    std::string number = std::to_string(EXERCISE);
    std::string output_file = "../datasheets/Anneling_pefect_log" + number + ".csv";
    Logger log(output_file, prob);

    //SA parameters
    int neighborhood_size = 24; 
    float start_temperature = 260; 
    int anneling_step = 110; 
    float multiplier = 0.986;
    int generations_limit = 45000;

    //loger parameters
    int step = 30; 
    int repeat_count = 10;
    //log.runAnnelingTest(generations_limit, step, neighborhood_size, start_temperature, anneling_step, multiplier);
    log.runAnnelingLog(generations_limit, neighborhood_size, start_temperature, anneling_step, multiplier, repeat_count);
    

}

void eaResearch(){

    /// MAX CHILDS = 1 000 000
    //Start parameters
    int iterations = 200; //200
    mutation_type m = mutation_type::invert;
    crossing_type c = crossing_type::oc;
    selection_type s = selection_type::tournament;
    int population_size = 5000; //3500
    float cross_p = 0.86; //0.9
    float mutate_p = 0.48; // 0.83
    int tournament_size = 8; //208

    EA_Researcher ea(iterations, m, c, s, population_size, cross_p, mutate_p);
    ea.setExNumber(0);
    ea.setTournamentSize(tournament_size);

    // //Research iterations
    // ea.setIterShift(200);
    // ea.setPopShift(0);
    // ea.setMutateShift(0);
    // ea.setCrossShift(0);
    // ea.setSampleCount(10);
    // ea.setTestsCount(9);
    // ea.research();

    // //Research Pop
    //ea.setPopSize(2000);
    ea.setIterShift(200);
    ea.setPopShift(-200);
    ea.setMutateShift(0);
    ea.setCrossShift(0);

    ea.setSampleCount(10);
    ea.setTestsCount(20);
    ea.research();

    
    // //Research Cross
    // ea.setCross(0.7);
    // ea.setIterShift(0);
    // ea.setPopShift(0);
    // ea.setMutateShift(0);
    // ea.setCrossShift(0.02);
    // ea.setSampleCount(10);
    // ea.setTestsCount(12);
    // ea.research();
    
    //Research Mutation
    // ea.setMutate(0.4);
    // ea.setIterShift(0);
    // ea.setPopShift(0);
    // ea.setMutateShift(0.02);
    // ea.setCrossShift(0);
    // ea.setSampleCount(10);
    // ea.setTestsCount(12);
    // ea.research();

    // //Research Tournament Size
    // ea.setIterShift(0);
    // ea.setPopShift(0);
    // ea.setMutateShift(0);
    // ea.setCrossShift(0);
    // ea.setTournamentSize(8);
    // ea.setPTournamentShift(16);
    // ea.setSampleCount(10);
    // ea.setTestsCount(5);
    // ea.research();


}

void tsResearch(){
    /// MAX CHILDS = 1 000 000
    int iterations = 5000; //5000
    mutation_type m = mutation_type::invert;
    int n_size = 70; // 70
    int t_size = 48; 

    TS_Researcher ts(iterations, m, n_size, t_size);
    ts.setExNumber(0);
    /*
    //Iters
    ts.setIterShift(200);
    ts.setNShift(0);
    ts.setTShift(0);
    ts.setSampleCount(10);
    ts.setTestsCount(9);
    ts.research();
    */
    
    //N size
    ts.setIterShift(0);
    ts.setNSize(10);
    ts.setNShift(20);
    ts.setTShift(0);
    ts.setSampleCount(10);
    ts.setTestsCount(10);
    ts.research();

    /*
    //Tabu size
    ts.setIterShift(0);
    ts.setNShift(0);
    //ts.setTabuSize(4);
    ts.setTShift(4);
    ts.setSampleCount(10);
    ts.setTestsCount(10);
    ts.research();*/
    
}

void saResearch(){

    /// MAX CHILDS = 1 000 000
    int iterations = 45000; //
    mutation_type m = mutation_type::invert;
    int n_size = 24; //24
    float start_temp = 260; //120
    float multiplier = 0.986; //0.954
    int step = 110; //100

    
    SA_Researcher sa(iterations, m, n_size, start_temp, multiplier, step);
    sa.setExNumber(0);

    //Iter
    sa.setIterShift(1000);
    sa.setNShift(0);
    sa.setTempShift(0);
    sa.setMultiplierShift(0);
    sa.setStepShift(0);
    sa.setSampleCount(10);
    sa.setTestsCount(10);
    sa.research();

    //N size
    sa.setIterShift(0);
    sa.setNShift(2);
    sa.setTempShift(0);
    sa.setMultiplierShift(0);
    sa.setStepShift(0);
    sa.setSampleCount(10);
    sa.setTestsCount(10);
    sa.research();
    /*
    //Start temp
    sa.setTemp(100);
    sa.setIterShift(0);
    sa.setNShift(0);
    sa.setTempShift(20);
    sa.setMultiplierShift(0);
    sa.setStepShift(0);
    sa.setSampleCount(10);
    sa.setTestsCount(10);
    sa.research();

    //Multip
    sa.setMultiplier(0.950);
    sa.setIterShift(0);
    sa.setNShift(0);
    sa.setTempShift(0);
    sa.setMultiplierShift(0.004);
    sa.setStepShift(0);
    sa.setSampleCount(10);
    sa.setTestsCount(10);
    sa.research();

    //Step
    sa.setStep(64);
    sa.setIterShift(0);
    sa.setNShift(0);
    sa.setTempShift(0);
    sa.setMultiplierShift(0);
    sa.setStepShift(10);
    sa.setSampleCount(10);
    sa.setTestsCount(10);
    sa.research();*/
}

void greedyTest(cVRP* prob){

    Greedy solver(prob);
    solver.generateSolutions();
    Solution* best = solver.getSolution(solver.getbestIndex());
    solver.printSolution(best);
    std::cout << "Score : " <<prob->evalutateSolution(best) << "\n";
}

int main(int, char**) {
    //std::getchar();
    //Path to file
    std::string laptop_problem_paths[8] = {
        "D:/Dev/Uni-Metaheuristics/problem instances/test-file.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n32-k5.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n37-k6.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n39-k5.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n45-k6.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n48-k7.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n54-k7.vrp",
        "D:/Dev/Uni-Metaheuristics/problem instances/A-n60-k9.vrp"

    };


    std::string pc_problem_paths[8] = {
        "D:/Dev/Metaheuristic/problem instances/test-file.vrp", //0
        "D:/Dev/Metaheuristic/problem instances/A-n32-k5.vrp",  //1
        "D:/Dev/Metaheuristic/problem instances/A-n37-k6.vrp",  //2
        "D:/Dev/Metaheuristic/problem instances/A-n39-k5.vrp",  //3
        "D:/Dev/Metaheuristic/problem instances/A-n45-k6.vrp",  //4
        "D:/Dev/Metaheuristic/problem instances/A-n48-k7.vrp",  //5
        "D:/Dev/Metaheuristic/problem instances/A-n54-k7.vrp",  //6
        "D:/Dev/Metaheuristic/problem instances/A-n60-k9.vrp"   //7

    };

        std::string problem_paths[8] = {
        "../problem instances/test-file.vrp", //0
        "../problem instances/A-n32-k5.vrp",  //1
        "../problem instances/A-n37-k6.vrp",  //2
        "../problem instances/A-n39-k5.vrp",  //3
        "../problem instances/A-n45-k6.vrp",  //4
        "../problem instances/A-n48-k7.vrp",  //5
        "../problem instances/A-n54-k7.vrp",  //6
        "../problem instances/A-n60-k9.vrp"   //7

    };
    
    std::string file_name = (std::string) problem_paths[EXERCISE];
    //std::string file_name = (std::string) laptop_problem_paths[1];
    
    //std::cout << file_name << "\n";
    
    cVRP* prob;
    Loader load_one(file_name);
    prob = load_one.loadProblem();
    
    std::cout << "Vehicle capacity: " << prob->getVehicleCapacity() << "\n";
    std::cout << "Dimension: " << prob->getDimension() << "\n";
    std::cout << "______________________________________________________\n";
    /*
    // std::cout << "Distance check: \n";
    // //prob->printDistanceMatrix();
    */

    //Exercise One
    //Wynik średni powinien być lepszy od greedy.
    exerciseOne(prob);

    //Exercise Two
    //exerciseTwo(prob);

    //Exercise Three
    //exerciseThree(prob);
    
    //Exercise Four
    //exerciseFour();

    //greedyTest(prob);
    
    //eaResearch();
    //tsResearch();
    //saResearch();
    

    //_________________________________________________________________________________________________
    //Clean up memory and close program
    delete prob;
    //std::getchar();
    return 0;
}
