#include<iostream>

class UnmannedSystem{
    int id;
    std::string payload;
    std::string callsign;
    bool isActive;
    void shutdownSystem();
    public:
    UnmannedSystem(int i, std::string p, std::string c) : id(i), payload(p), callsign(c){
        std::cout<<"Unmanned system online\n";
        isActive = true;
    }
    void getSystemStatus();
    void bootSystem();
};

class AerialUnmannedSystem : public UnmannedSystem{

    public:
    AerialUnmannedSystem(int i, std::string p, std::string c) : UnmannedSystem( i, p, c){
        std::cout<<"Unmanned Aerial system online...\n";
    }
    void takeOff();
    void land();
};

class GroundUnmannedSystem : public UnmannedSystem{

    public:
    GroundUnmannedSystem(int i, std::string p, std::string c) : UnmannedSystem(i, p, c){
        std::cout<<"Unmanned Ground system online...\n";
    }
    void drive();
};

void UnmannedSystem::getSystemStatus(){
    isActive ? std::cout<<"System is active\n" : std::cout<<"System is offline\n";
}

void UnmannedSystem::bootSystem(){
    if(!isActive) isActive = true;
    else std::cout<<"System already offline\n";
}

void UnmannedSystem::shutdownSystem(){
    if(isActive) isActive = false;
    else std::cout<<"System already online\n";
}

void AerialUnmannedSystem::takeOff(){
    std::cout<<"System taking off\n";
}

void AerialUnmannedSystem::land(){
    std::cout<<"System landing\n";
}

void GroundUnmannedSystem::drive(){
    std::cout<<"System driving\n"; 
}

int main(){

    AerialUnmannedSystem uas_1(38473,"IR_Camera","BRAVO_12");
    GroundUnmannedSystem ugv_4(38940,"Launcher","GOLF_32");
    uas_1.bootSystem();
    ugv_4.bootSystem();
    ugv_4.getSystemStatus();
    uas_1.takeOff();
    ugv_4.drive();
    ugv_4.doDonuts();
    uas_1.land();
    uas_1.shutdownSystem();
    ugv_4.shutdownSystem();

    return 0;
}
