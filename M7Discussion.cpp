#include<iostream>
#include<string>
const int16_t CARS = 4;
const int16_t CAR_ATTRIBUTES = 4;

std::string carInventory[CARS][CAR_ATTRIBUTES] = {
                    {"Audi","A4","blue",2018},
                    {"Ford","Fiesta","red",2020},
                    {"Nissan","Ultima","grey",2017},
                    {"Tesla","Model 3","white",2024}
                };

void getInventory(const std::string m[][4]);

int main(){

    getInventory(carInventory);

    return 0;
}

void getInventory(const std::string m[][4]){
    std::cout<<"Make\tModel\tColor\tYear\n";
    for(int j = 0; j < CAR_ATTRIBUTES; j++){
        std::cout<<'\n';
        for(int i = 0; i < CARS; i++){
            std::cout<<m[j][i]<<"\t";
        }
    }
}