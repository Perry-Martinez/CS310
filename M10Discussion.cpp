#include<iostream>
#include<math.h>

const int ARRAY_SIZE = 8;

double getPopStandardDeviation(double*,const int);

int main(){

    double valArr = new double[ARRAY_SIZE]{13.0,78.9,-2.3,15.4,-8.0,23.3,-12.1,8.9};
    double *stdDeviation = new double(getPopStandardDeviation(valArr,ARRAY_SIZE));

    std::cout<<*stdDeviation<<std::endl;

    delete[] valArr;
    delete stdDeviation;

    return 0;
}

// function that takes an pointer to a static array and returns the population standard deviation
double getPopStandardDeviation(double arr, const int size){
    // finds the mean of the values in arr
    double mean = 0;
    for(int i = 0; i < size; i++){
        mean += *(arr+i);
    }
    mean /= size;

    // finds the mean of the differences of the mean value and the value in each index of arr 
    double diffSum = 0;
    for(int i = 0; i < size; i++){
        diffSum += pow(mean - *(arr+i),2);
    }
    diffSum /= size;

    return sqrt(diffSum);
}
