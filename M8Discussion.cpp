#include<iostream>
#include<string>

// const variable to set the size of the robotArmy membership array
int16_t ROBOT_ARMY_CAPACITY = 10;

// Robot class declaration
class robot{
    std::string name;
    bool poweredOn;
    public:
    robot(std::string n):name(n){
        std::cout<<"Initializing..."<<std::endl;
        poweredOn = false;
    }
    std::string getName(){
        return name;
    }
    void turnOn(){
        if(poweredOn) std::cout<<"This robot is already on!"<<std::endl;
        else{
            std::cout<<"System booting..."<<std::endl;
            poweredOn = true;
        }
    }
    void turnOff(){
        if(!poweredOn) std::cout<<"..."<<std::endl;
        else{
            std::cout<<"System shutting down..."<<std::endl;
            poweredOn = false;
        }
    }
};

// Class that contains an array of robot objects
class robotArmy{
    robot* membership[ROBOT_ARMY_CAPACITY]{nullptr};
    public:
    robotArmy(){
        int count = 0;
        //initializes each robot in the membership array by reference
        for(robot* r : membership){
            r = new robot("drone_"+std::to_string(count++));
        }
    }
    ~robotArmy(){
      // Iterates throught the membership array and deletes the existing pointers to robots
        for(robot*& r : membership){
            delete r;
            r = nullptr;
        }
    }
    void displayMembers(){
        for(robot*& r : membership){
            std::cout<<r->name<<'\n'<<std::endl;
        }
    }
    robot* getRobot(int16_t index){
            return membership[index];
    }
};

int main(){
    robotArmy swarm_1;

    std::cout<<swarm_1.getRobot(6)->getName()<<std::endl;
    swarm_1.getRobot(6)->turnOn();
    swarm_1.getRobot(6)->poweredOn = false;
    swarm_2.displayMembers();
    return 0;
}
