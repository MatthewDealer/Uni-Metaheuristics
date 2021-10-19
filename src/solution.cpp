#include "../include/solution.hpp"

Solution::Solution(int dimension){
    path = new int[dimension-1];
}

Solution::~Solution(){
    delete[] path;
}

int Solution::getPathSize(){
    return this->size;
}

void Solution::printPath(){
    std::cout << "Solution:\n";
       for(int i = 0; i < size; i++){
            std::cout << path[i];
            if(i < size -1 )
            std::cout << "-";
        }
        std::cout << "\n";
}

int Solution::getValueAt(int index){
    return path[index];
}

void Solution::setValueAt(int index, int value){
    path[index] = value;
}
