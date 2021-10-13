#pragma once
#include <iostream>
#include <utility> 
#include <vector>
#include <math.h>

class cVRP{
    private:
        int dimension;
        int vehicle_capacity;
        int* demands;
        int** distance_matrix;
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

        void calculateDitanceMatrix();
        void printDistanceMatrix();
        int getDistance(int, int);  
        


};