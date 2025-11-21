#include<iostream>
#include<random>

void populateArr(int, int*, int);

const int RAND_ARRAY_SIZE = 25;

int main(){

    int arr[RAND_ARRAY_SIZE];

    std::random_device rdObj;
    std::mt19937 gen(rdObj());
    std::uniform_int_distribution<> dis(-100,100);

    for(int i = 0;i < RAND_ARRAY_SIZE;){
        try{
            populateArr(dis(gen),arr,i);
            i++;
        }
        catch(std::invalid_argument &e){
            std::cout<<"Error: "<<e.what()<<std::endl;
        }
    }
    std::cout<<'[';
    for(int i = 0; i < RAND_ARRAY_SIZE; i++){
        std::cout<<*(arr+i);
        if(i < RAND_ARRAY_SIZE - 1) std::cout<<" : ";
    }
    std::cout<<']'<<std::endl;

    return 0;
}

void populateArr(int randNum, int *arr, int index){
    if(randNum < 10 || randNum > 100){
        throw std::invalid_argument("Value "+std::to_string(randNum)+" is outside of acceptable range");
    }
    *(arr+index) = randNum;
}
