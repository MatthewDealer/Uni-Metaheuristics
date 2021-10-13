#pragma once
#include "problem.hpp"
#include "solution.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>  

class Solver{
    public:
        Solution* generateRandomSolution(cVRP* problem);
        Solution* genetareGreedySolution(cVRP* problem);
};
