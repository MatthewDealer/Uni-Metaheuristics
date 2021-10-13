#include "../include/solution.hpp"

int Solution::getPathsCount(){
    return this->paths.size();
}

std::vector<int> Solution::getPath(int index){
    return this->paths[index];
}

void Solution::printPaths(){
    std::cout << "Solution:\n";
       for(int i = 0; i < paths.size(); i++){
        for(int j = 0; j < paths[i].size(); j++)
            std::cout << paths[i][j];
        std::cout << "\n";
    }
}

void Solution::addPath(std::vector<int> new_path){
    paths.push_back(new_path);
}
