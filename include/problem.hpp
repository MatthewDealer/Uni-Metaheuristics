#include <iostream>
#include <utility> 

class cVRP{
    private:
        int vehicle_capacity;
        int dimension;
        int** distance_matrix;
        std::pair<int, int>* coordinates;

    public:
        cVRP(int, int);
        ~cVRP();
        int getVehicleCapacity();
        int getDimension();
        void calculateDitanceMatrix();
        int getDistance(int, int);
};