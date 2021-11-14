#include "../include/researcher.hpp"

//////////////Researcher//////////////
void Researcher::setTestsCount(int count){
    this->tests_count = count;
}
void Researcher::setSampleCount(int count){
    this->sample_count = count;
}

void Researcher::setIterShift(int shift){
    this->iteration_shift = shift;
}

////////////EA_Researcher////////////
void EA_Researcher::setCrossShift(float shift){
    this->cross_shift = shift;
}

void EA_Researcher::setMutateShift(float shift){
    this->mutate_shift = shift;
}

void EA_Researcher::setPopShift(int shift){
    this->pop_shift = shift;
}


////////////TS_Researcher////////////
void TS_Researcher::setNShift(int shift){
    this->n_shift = shift;
}

void TS_Researcher::setTShift(int shift){
    this->t_shift = shift;
}


////////////SA_Researcher////////////
void SA_Researcher::setNShift(int shift){
    this->n_shift = shift;
}

void SA_Researcher::setTempShift(float shift){
    this->temp_shift = shift;
}

void SA_Researcher::setMultiplierShift(float shift){
    this->multiplier_shift = shift;
}

void SA_Researcher::setStepShift(int shift){
    this->step_shift = shift;
}