#include "../include/loader.hpp"

void Loader::printInfo(){
    std::cout << this->file_name << "\n";
}

void Loader::readFile(){
    std::string line; // string holder
    std::ifstream MyReadFile(this->file_name);

    // temp variables
    int dimension = 0;
    int capacity = 0;


    while (std::getline (MyReadFile, line)) {
        //std::cout << line << "\n";
        
        //split line to vector of words
        std::vector<std::string> words;
        boost::split(words, line, boost::is_any_of("\t "));

        //get problem's dimenion
        if(words[0] == "DIMENSION"){
            dimension = std::stoi(words[2]);
            std:: cout << "Dimiension: " << dimension << "\n";
        }

        //get capacity of a truck
        if(words[0] == "CAPACITY"){
            std:: cout << "Capacity: " << words[2] << "\n";
            capacity = std::stoi(words[2]);
        }

        //get coordinates of magazines
        if(words[0] == "NODE_COORD_SECTION"){
            for(int i = 0; i < dimension; i++){
                if(std::getline (MyReadFile, line)){
                    std::cout << line << "\n";
                }
            }
        }

        //get demand section of magazines
        if(words[0] == "DEMAND_SECTION"){
            for(int i = 0; i < dimension; i++){
                if(std::getline (MyReadFile, line)){
                    std::cout << line << "\n";
                }
            }
        }
        
    }

    MyReadFile.close();
}

cVRP* Loader::loadProblem(){
    std::string line; // string holder
    std::ifstream MyReadFile(this->file_name);


    // temp variables
    int dimension = 0;
    int capacity = 0;
    std::vector<std::pair<int,int>> coords;
    std::vector<int> demands;

    while (std::getline (MyReadFile, line)) {
        //std::cout << line << "\n";
        
        //split line to vector of words
        std::vector<std::string> words;
        boost::split(words, line, boost::is_any_of("\t "));

        //get problem's dimenion
        if(words[0] == "DIMENSION"){
            dimension = std::stoi(words[2]);
        }

        //get capacity of a truck
        if(words[0] == "CAPACITY"){
            capacity = std::stoi(words[2]);
        }

        //get coordinates of magazines
        if(words[0] == "NODE_COORD_SECTION"){
            for(int i = 0; i < dimension; i++){
                if(std::getline (MyReadFile, line)){
                    boost::split(words, line, boost::is_any_of("\t "));
                    int x = std::stoi(words[1]);
                    int y = std::stoi(words[2]);
                    //std::cout << "x: " << x << ", y: " << y << "\n";
                    coords.push_back(std::pair<int,int>(x,y));
                }
            }
        }

        //get demand section of magazines
        if(words[0] == "DEMAND_SECTION"){
            for(int i = 0; i < dimension; i++){
                if(std::getline (MyReadFile, line)){
                    boost::split(words, line, boost::is_any_of("\t "));
                    int demand = std::stoi(words[1]);
                    demands.push_back(demand);

                }
            }
        }
        
    }

    MyReadFile.close();
    //Show read values
    
    std::cout << "___________________________________\n";
    std::cout << "READ VALUES:\n";
    std:: cout << "Dimiension: " << dimension << "\n";
    std:: cout << "Capacity: " << capacity<< "\n";
    std::cout << "Coordinates: \n";
    for(int i = 0; i < coords.size(); i++){
        std::cout << "\t" << i << ": " << coords[i].first << ", " << coords[i].second << "\n";
    }
    std::cout << "Demands: \n";
    for(int i = 0; i < demands.size(); i++){
        std::cout << "\t" << i << ": " << demands[i] << "\n";
    }
    std::cout << "___________________________________\n";
    
    
    //Create problem instance
    cVRP* ptr =  new cVRP(capacity, dimension);
    ptr->setCoordinates(coords);
    ptr->setDemands(demands);
    
    return ptr;
}