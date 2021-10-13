#pragma once
#include <iostream>
#include <utility> 
#include <vector>
#include <math.h>
#include "solution.hpp"

class cVRP{
    private:
        int dimension;
        int vehicle_capacity;
        int* demands;
        float** distance_matrix;
        std::pair<int, int>* coordinates;
        
        

    public:
        cVRP(int capacity, int dimension);
        
        ~cVRP();
        
        int getVehicleCapacity();
        void setVehicleCapacity(int);

        int getDimension();
        void setDimension(int);
        
        void setCoordinates(std::vector<std::pair<int,int>> cords);
        void setDemands(std::vector<int> demands);
        int getDemands(int index);

        void calculateDitanceMatrix();
        void printDistanceMatrix();
        float getDistance(int, int);  
        
        //Count only once, remember the evaluation
        float evalutateSolution(Solution* soution);


};