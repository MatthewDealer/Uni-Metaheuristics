#include "../include/problem.hpp"
#include <math.h>

//Set distance first to initialize arrays
cVRP::cVRP(int capacity,int distance){
    this->vehicle_capacity = capacity;
    this->dimension = distance;

    distance_matrix = new int*[distance];
    for(int i = 0; i < distance; i++){
        distance_matrix[i] = new int[distance];
    }

    coordinates = new std::pair<int, int>[distance];
}

//Destructor, must remember to clean up the memory!
cVRP::~cVRP(){
    for(int i = 0; i < dimension; i++){
        delete distance_matrix[i];
    }

    delete[] distance_matrix;
    delete coordinates;
}

//Fill the distance matrix with distance between two magazines
void cVRP::calculateDitanceMatrix(){
    //First check if distance matrix is already initialized
    //if(distance_matrix == nullptr)
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            //Calculate distance with Euclidean equation 
            distance_matrix[i][j] = sqrt(pow(coordinates[i].first - coordinates[j].first,2) 
                    + pow(coordinates[i].second-coordinates[j].second,2));
        }
    }
}

//Return calculated distance between two magazines
int cVRP::getDistance(int from, int to){
    return 0;
};

int cVRP::getDimension(){
    return this->dimension;
}

int cVRP::getVehicleCapacity(){
    return this->vehicle_capacity;
}