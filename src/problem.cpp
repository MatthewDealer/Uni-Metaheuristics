#include "../include/problem.hpp"


//Set distance first to initialize arrays
cVRP::cVRP(int capacity,int dimension){
    this->vehicle_capacity = capacity;
    this->dimension = dimension;
   
    distance_matrix = new int*[dimension];
    for(int i = 0; i < dimension; i++){
        distance_matrix[i] = new int[dimension];
    }

    coordinates = new std::pair<int, int>[dimension];
    demands = new int[dimension];
    
}


//Destructor, must remember to clean up the memory!
cVRP::~cVRP(){

    for(int i = 0; i < dimension; i++){
        delete distance_matrix[i];
    }

    delete[] distance_matrix;
    delete coordinates;
    delete demands;
}


int cVRP::getDimension(){
    return this->dimension;
}

void cVRP::setDimension(int new_dimension){
    this->dimension = new_dimension;
}

int cVRP::getVehicleCapacity(){
    return this->vehicle_capacity;
}

void cVRP::setVehicleCapacity(int new_capacity){
    this->vehicle_capacity = new_capacity;
}

void cVRP::setCoordinates(std::vector<std::pair<int,int>> coords){
    if (dimension == coords.size()){
        for(int i = 0; i < dimension; i++){
            this->coordinates[i] = coords[i];
        }
        this->calculateDitanceMatrix();
        std::cout << "Coords set, Distance matrix calculated!\n";
    }
    else
        std::cout << "Wrong size of vector!\n";
}

void cVRP::setDemands(std::vector<int> new_demands){
    if(dimension == new_demands.size()){
        for(int i = 0; i < dimension; i++){
            this->demands[i] = new_demands[i];
        }
        std::cout << "Demands set!\n";
    }
    else
        std::cout << "Wrong size!\n";
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

//Print distance matrix
void cVRP::printDistanceMatrix(){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            std::cout << this->distance_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}


//Return calculated distance between two magazines
int cVRP::getDistance(int from, int to){
    return this->distance_matrix[from][to];
}
