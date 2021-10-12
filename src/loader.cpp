#include "../include/loader.hpp"
#include <boost/algorithm/string.hpp>
#include <vector>

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