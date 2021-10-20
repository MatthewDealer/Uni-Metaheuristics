#include "../include/csvlogger.hpp"

Logger::Logger(std::string path){
    this->file_name = path;
    file.open(file_name);
}
Logger::~Logger(){
    file.close();
}