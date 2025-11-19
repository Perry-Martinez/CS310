#include<iostream>
#include<string>

template <class T>
class House{
    T homeID;
    std::string homeOwner;
    void setHomeOwner();
public:
    friend std::ostream& operator<<(std::ostream& os, const House<T>& ch){
        os << ch.homeID << " street\n";
        return os;
    }
};

template <class T>
void House<T>::setHomeOwner(){
    std::string owner;
    try{
        std::cout << "Enter the name of the home owner: ";
        std::cin >> owner;
        if(owner.empty()){
            throw std::invalid_argument("Invalid input");
        }
        homeOwner = owner;
    }catch(const std::invalid_argument& e){
        std::cout << "Error occurred: " << what() << std::endl;
    }
}

int main(){
    House<std::string> userHome;
    userHome.setHomeOwner();
    return 0;
}
