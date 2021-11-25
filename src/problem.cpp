#include "../include/problem.hpp"


//Set distance first to initialize arrays
cVRP::cVRP(int capacity,int dimension){
    this->vehicle_capacity = capacity;
    this->dimension = dimension;
   
    distance_matrix = new float*[dimension];
    for(int i = 0; i < dimension; i++){
        distance_matrix[i] = new float[dimension];
        for(int j = 0; j < dimension; j ++)
            distance_matrix[i][j] = 0;
    }

    coordinates = new std::pair<int, int>[dimension];
    demands = new int[dimension];
    
}

//Destructor, must remember to clean up the memory!
cVRP::~cVRP(){

    for(int i = 0; i < dimension; i++){
        delete[] distance_matrix[i];
    }

    delete[] distance_matrix;
    delete[] coordinates;
    delete[] demands;
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
        //std::cout << "Coords set, Distance matrix calculated!\n";
    }
    else
        std::cout << "Wrong size of vector!\n";
}

//Set demands of magazines from vector
void cVRP::setDemands(std::vector<int> new_demands){
    if(dimension == new_demands.size()){
        for(int i = 0; i < dimension; i++){
            this->demands[i] = new_demands[i];
        }
        //std::cout << "Demands set!\n";
    }
    else
        std::cout << "Wrong size!\n";
}

//Return demand of magzine
int cVRP::getDemands(int index){
    return this->demands[index];
}

//Fill the distance matrix with distance between two magazines
void cVRP::calculateDitanceMatrix(){
    //First check if distance matrix is already initialized
    //if(distance_matrix == nullptr)
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            //Calculate distance with Euclidean equation 
            distance_matrix[i][j] = sqrt(pow((coordinates[i].first - coordinates[j].first),2) 
                    + pow((coordinates[i].second-coordinates[j].second),2));
        }
    }
}

//Print distance matrix
void cVRP::printDistanceMatrix(){
    //std::ofstream file;
    //std::string path ="matrix.csv";
    //file.open(path);
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            //file << (int)this->distance_matrix[i][j] << ",";
            std::cout << (int)this->distance_matrix[i][j] << ",";
        }
        //file << ",\n";
        std::cout << "\n";

    }
    //file.close();
}

//Return calculated distance between two magazines
float cVRP::getDistance(int from, int to){
    return this->distance_matrix[from][to];
}

//Evaluate given solution
float cVRP::evalutateSolution(Solution* solution){
    //For each path calculate the sum of distances
    // Check if vehicle isnt overload
    float sum = 0;
    int start_point = 0; // 0 is an index of magazine
    int current_capacity = 0;


    for(int i = 0; i < solution->getPathSize(); i++){

        int end_point = solution->getValueAt(i);
        int demand = this->getDemands(end_point);
        
        if(current_capacity + demand > vehicle_capacity){
            end_point = 0;
            current_capacity = -demand;
            i--;
        }
        current_capacity += demand;
        sum += this-> getDistance(start_point, end_point);
        start_point = end_point;
    }
    sum += this -> getDistance(start_point, 0);
    start_point = 0;
    return sum;
}