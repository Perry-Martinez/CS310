#include<iostream>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<random>

const int INVENTORY_CAPACITY = 10;
int WEAKEST_WEAPON = 5;

//  Game weapon types
enum Weapons{
    dagger = WEAKEST_WEAPON,
    bow,
    hatchet,
    spear,
    sword
};

// Game item types
enum Items{
    empty,
    torch,
    compass,
    cloak,
    potion,
    food,
    hatchet
};

// Player hunger level
enum HungerLevels{
    full,
    starving
};

// Main methods and attributes used throughout the game
class Hero{
    int health;
    HungerLevels hunger;
    Weapons equippedWeapon;
    Items inventory[INVENTORY_CAPACITY];
    int stock;
    int achievements = 0;
    int gold;

    public:
        Hero();
        int getOutcome(int, int);
        void sustainInjury(int);
        void explore();
        void trade();
        void addItem(int, Items);
        bool consumeItem(Items);
        void eat();
        void loseItem();
        void gainTreasure(int);
        void gainAchievement(int);
        void printStatus();
        void printMenu();
        std::string weaponToString(Weapons);
        std::string itemToString(Items);
        void getInventory();
};

// Causes gameloop to continue until true
bool gameOver = false;

// When true the screen will be cleared after user input
bool introComplete = false;

// Counter to track the number of days that pass in game
int day = 0;

// Function to clear the text from the console
void clearScreen();

int main(){
    Hero player;

    // Game intro
    std::cout<<"\n\n\nWelcome traveler...\n\nYou are a hero who will embark on many adventures\n\n";
    std::cout<<"Here is your inventory...\n\n";
    player.getInventory();

    // Gameloop 
    while(!gameOver){
        player.printStatus();
        player.printMenu();
        char userInput;
        std::cin>>userInput;
        if(introComplete) clearScreen();
        std::cout<<"\n";

        // User input for game menu
        switch(userInput){
            case 'e': player.explore();
            break;
            case 't': player.trade();
            break;
            case 'i': player.getInventory();
            break;
            case 'f': player.eat();
            break;
            case 'p': 
                clearScreen();
                if(!player.consumeItem(potion)){
                    std::cout<<"You don't have any potions unforetunately...\n";
                }
                else{
                    player.sustainInjury(-20);
                }
            break;
            case 'h': 
                clearScreen();
                std::cout<<"Try to see how many achievements you can earn before you perish\n";
                std::cout<<"If you run out of food or sustain too main injuries you will perish";
                std::cout<<"Consume potion to recover health\n";
                std::cout<<"Each game you will start with a new random weapon\n";
                std::cout<<"More tips in future installment\n";
            break;
            default:
                std::cout<<"Invalid entry, please try again...\n";
            break;
        }

        // At this point the intro has been given and can be cleared
        introComplete = true;
    }

}

// Hero class constructor
Hero::Hero(){
    health = 12;
    hunger = full;
    stock = 0;
    equippedWeapon = (Weapons)getOutcome(5,9);
    gold = 5;
    std::fill(inventory,inventory + INVENTORY_CAPACITY - 6,empty);
    inventory[INVENTORY_CAPACITY -1] = potion;
    inventory[INVENTORY_CAPACITY -2] = food;
    inventory[INVENTORY_CAPACITY -3] = food;
    inventory[INVENTORY_CAPACITY -4] = cloak;
    inventory[INVENTORY_CAPACITY -5] = torch;
    inventory[INVENTORY_CAPACITY -6] = compass;
}

// Random number generation for game events
int Hero::getOutcome(int l, int u){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(l, u);
    return dis(gen);
}

// Health reduction mechanism
void Hero::sustainInjury(int damage){
    this->health -= damage;
    if(health <= 0){
        std::cout<<"... You have lost all you health and have perished.\n";
        std::cout<<"You will be remembered for ages, Hero.\n";
        std::cout<<"Your achievement count was "<<achievements<<std::endl;
        gameOver = true;
    }
}

// Main game events function
void Hero::explore(){
    // If player is starving when exploration starts they will lose health
    if(hunger == starving){
        std::cout<<"You're starving\n";
        bool ate = consumeItem(food);
        if(ate){
            std::cout<<"You ate some bread and you're ready to explore.\n";
            hunger = full;
        }
        else{
            std::cout<<"...and you don't have food. You're health was reduced but you're ready to explore.\n";
            sustainInjury(10);
        }
    }
    int explorationOutcome = getOutcome(1,4);

    // Exploration events
    switch(explorationOutcome){

        // Beast encounter
        case 1: {
            clearScreen();
            printStatus();
            getInventory();
            std::cout<<"You encountered a beast! [Strenght 2 - 15]\n";
            std::cout<<"Do you want to fight or flee?('f' = fight | 'r' = flee)\n";
            char userInput1;
            std::cin>>userInput1;
            if(userInput1 == 'f'){
                int beastStrength = getOutcome(2,15);
                if(beastStrength > this->equippedWeapon){
                    std::cout<<"\nYou sustained an injury from the beast and your weapon broke... you returned home\n";
                    sustainInjury(beastStrength);
                    bool recovered = consumeItem(food);
                    equippedWeapon = (Weapons)getOutcome(5,9);
                    std::cout<<"\nWhen you returned home you were given a "<<weaponToString(equippedWeapon)<<"\n";
                }
                else{
                    std::cout<<"\nYou defeated the beast!\n";
                    sustainInjury(2);
                    gainAchievement(10);
                }
            }
            else if(userInput1 == 'r'){
                if(consumeItem(cloak)){
                    std::cout<<"Since you had a cloak you quietly disappeared before the beast noticed you...\n";
                }
                else{
                    std::cout<<"During your attempt to run...\n";
                    loseItem();
                }
            }
            else{
                std::cout<<"You became disoriented and \n";
                loseItem();
                hunger = starving;
            }
        }
        break;

        // Cave discovery
        case 2:{
            clearScreen();
            printStatus();
            getInventory();
            std::cout<<"You discovered a cave!\n";
            std::cout<<"Do you want to explore it or keep away?('e' = explore | 'n' = no, leave )\n";
            char userInput2;
            std::cin>>userInput2;
            if(userInput2 == 'e'){
                if(consumeItem(torch)){
                    Weapons foundWeapon = (Weapons)getOutcome(5,9);
                    std::cout<<"Since you had a torch you discovered a "<<weaponToString(foundWeapon)<<" [Strenght "<<foundWeapon<<"] in the cave!\n";
                    gainAchievement(3);
                    std::cout<<"Do you want to equip the new weapon and leave your "<<weaponToString(equippedWeapon)<<" behind?('y' = Yes | 'n' = No)\n";
                    char u;
                    std::cin>>u;
                    if(u == 'y'){
                        equippedWeapon = foundWeapon; 
                        std::cout<<"You equipped the new "<<weaponToString(foundWeapon)<<" that you found!\n";
                    }
                    else if(u == 'n'){
                        std::cout<<"Okay you're going to leave the "<<weaponToString(foundWeapon)<<" behind...\n";
                    }
                    else{
                        std::cout<<"You became disoriented in the cave and had to return home...\n";
                    }
                    break;
                }
                int caveOutcome = getOutcome(1,4);
                switch(caveOutcome){
                    case 1: 
                        std::cout<<"You became lost in the cave for days...\n";
                        
                        if(!consumeItem(food)){
                            sustainInjury(5);
                            std::cout<<"\nYou're hungry and don't have food. Now you sustained an injury...\n";
                        }
                        else{
                            std::cout<<"\nYou had to eat some of your food to survive while lost...\n";
                        }
                    break;

                    case 2:{
                        std::cout<<"You discovered a lost traveller!\n";
                        Items gift = (Items)getOutcome(1,5);
                        std::cout<<"They gifted you a "<<itemToString(gift)<<" for helping them escape the cave!\n";
                        addItem(1,gift);
                    }
                        break;
                    case 3:{
                        std::cout<<"You encountered a large spider! [Strenght 1 - 12]\n";
                        if(equippedWeapon == spear || equippedWeapon == bow){
                            std::cout<<"Since you have a "<<weaponToString(equippedWeapon)<<", you defeated the spider before it could strike!\n";
                            gainAchievement(6);
                            break;
                        }
                        int spiderStrength = getOutcome(1,12);
                        if(spiderStrength > this->equippedWeapon){
                            std::cout<<"You sustained an injury from the spider and returned home";
                            sustainInjury(spiderStrength);
                            bool recovered = consumeItem(food);
                            equippedWeapon = (Weapons)getOutcome(5,9);
                            std::cout<<"\nWhen you returned home you were given a "<<weaponToString(equippedWeapon)<<"\n";
                        }
                        else{
                            std::cout<<"You defeated the spider!\n";
                            sustainInjury(2);
                            gainAchievement(10);
                        }
                        break;
                    }
                    case 4:
                        std::cout<<"You discovered a treasure chest!\n";
                        gainAchievement(15);
                        gainTreasure(20);
                        break;
                    default:
                        std::cout<<"You returned home...\n";
                        break;
                }
            }
            else if(userInput2 == 'n'){
                std::cout<<"You decided to return home in shame... \n";
                gainAchievement(-5);
            }
            else{
                std::cout<<"You became disoriented and \n";
                loseItem();
                hunger = starving;
            }
        }
        break;

        // Forest discovery
        case 3: {
            clearScreen();
            printStatus();
            getInventory();
            std::cout<<"You found a forest...\n";
            std::cout<<"Do you want to explore it or keep away?('e' = explore | 'n' = no, leave )\n\n";
            char userInput;
            std::cin>>userInput;
            if(userInput == 'e'){
                if(consumeItem(compass)){
                    std::cout<<"Since you had a compass you discovered a lost civilization!\n";
                    gainAchievement(20);
                    gainTreasure(5);
                    break;
                }
                int forestOutcome = getOutcome(1,2);
                switch(forestOutcome){
                    case 1: 
                        std::cout<<"\nYou found honey!\n";
                        gainAchievement(1);
                        addItem(2,food);
                        break;
                    case 2:
                        std::cout<<"\nYou became lost in the forest for days...\n";
                        if(!consumeItem(food)){
                            std::cout<<"\nYou're hungry and don't have food. Now you sustained an injury...\n";
                            sustainInjury(5);
                            hunger = starving;
                        }
                        else{
                            std::cout<<"\nYou had to eat some of your food to survive while lost...\n";
                        }
                        break;    
                }
            }
            else if(userInput == 'n'){
                std::cout<<"You decided to return home in shame... \n";
                gainAchievement(-5);
            }
            else{
                std::cout<<"You became disoriented and \n";
                loseItem();
                hunger = starving;
            }
        }
        break;

        // Visit village
        case 4:
            clearScreen();
            printStatus();
            getInventory();
            std::cout<<"You entered a village...\n";
            std::cout<<"Nothing else happened...this time\n";
            gainAchievement(2);
        break;
        default:
            std::cout<<"Error 021\n";
        break;
    }
}

// Adds items to player inventory
void Hero::addItem(int quantity,Items discovery){
    // while(stock < INVENTORY_CAPACITY && quantity > 0){
        for(int i = 0;i < INVENTORY_CAPACITY && quantity > 0;i++){
            if(inventory[i] == empty){
                inventory[i] = discovery;
                stock++;
                quantity--;
            }
        }
    // }
    if(quantity > 0){
        std::cout<<"Inventory full. Item left behind\n";
    }
}

// Removes items from player inventory
bool Hero::consumeItem(Items item){
    int itemSlot = 0;
    while(inventory[itemSlot] != item && itemSlot != INVENTORY_CAPACITY){
        itemSlot++;
    }

    if(itemSlot == INVENTORY_CAPACITY){
        return false;
    }
    else{
        inventory[itemSlot] = empty;
        stock--;
        return true;
    }
}

// Randomly removes one item from player inventory
void Hero::loseItem(){
    if(stock != 0){
        int itemSlot = getOutcome(0,9);
        int luck = 0;
        while(inventory[itemSlot] == empty && luck < 3){
            itemSlot = getOutcome(0,9);
            luck++;
        }
        if(inventory[itemSlot] != empty){
            std::cout<<"...you lost a "<<itemToString(inventory[itemSlot])<<"!\n";
            inventory[itemSlot] = empty;
        }
        else{
            std::cout<<"\nyou were lucky and didn't lose any items\n";
        }
    }
}

// Increases achievement score
void Hero::gainAchievement(int value){
    achievements += value;
    std::string gainOrLoss = "";
    value > 0 ? gainOrLoss = "gained" : gainOrLoss = "lost";
    if(value < 0) value *= -1;
    std::cout<<"\nYou "<<gainOrLoss<<" "<<value<<" achievements\n";
}

// Displays player status
void Hero::printStatus(){
    std::cout<<"\nDay: "<<day++<<"\n";
    std::cout<<"\n\n|| ------------------------------------------- ||\n";
    std::cout<<"|\t\t\t\t\t\t|\n";
    std::cout<<"|\tHero status\t\t\t\t|\n";
    std::cout<<"|\t\t\t\t\t\t|\n";
    std::cout<<"|\tHealth:\t\t"<<health<<"\t\t\t|\n";
    std::string hungerStatus = "";
    hunger == full ? hungerStatus = "Full\t\t\t" : hungerStatus = "Starving\t\t"; 
    std::cout<<"|\tHunger:\t\t"<<hungerStatus<<"|\n";
    std::cout<<"|\tAchievements:\t"<<achievements<<"\t\t\t|\n";
    std::cout<<"|\tGold:\t\t"<<gold<<"\t\t\t|\n";
    std::cout<<"|\tWeapon:\t\t"<<weaponToString(equippedWeapon)<<"\t\t\t|\n";
    std::cout<<"|\tStrength:\t"<<equippedWeapon<<"\t\t\t|\n";
    std::cout<<"|\t\t\t\t\t\t|\n";
    std::cout<<"|| ------------------------------------------- ||\n\n";
}

// Displays game menu
void Hero::printMenu(){
    std::cout<<"What action do you want to take, Hero?\n\n";
    std::cout<<"[e] - Explore: gain achievement, find items and encounter monsters\n";
    std::cout<<"[t] - Trade: exchange gold for food\n";
    std::cout<<"[i] - View inventory\n";
    std::cout<<"[f] - Eat food\n";
    std::cout<<"[p] - Consume a potion to recover some health\n";
    std::cout<<"[h] - Help: see guide and tips\n";
    std::cout<<"\n";
}

// Converts weapon enum value to a string representation
std::string Hero::weaponToString(Weapons w){
    switch(w){
        case dagger: return "Dagger";
        case bow: return "Bow";
        case hatchet: return "Hatchet";
        case spear: return "Spear";
        case sword: return "Sword";
        default: return "Error";
    }
}

// Converts item enum value to a string representation
std::string Hero::itemToString(Items i){
    switch(i){
        case torch: return "Torch";
        case compass: return "Compass";
        case cloak: return "Cloak";
        case potion: return "Potion";
        case food: return "Food";
        case empty: return "empty";
        default: return "Error";
    }
}

// Displays player inventory
void Hero::getInventory(){
    std::cout<<"\n|| ------------------------------------------- ||\n";
    std::cout<<"|\t\t\t\t\t\t|\n";
    std::cout<<"|\tInventory:\t\t\t\t|\n";
    std::cout<<"|\t\t\t\t\t\t|\n";
    for(auto i : inventory){
        if(i != empty){
            std::cout<<"|\t"<<itemToString(i)<<"\t\t\t\t\t|\n";
        }
    }
    std::cout<<"|\t\t\t\t\t\t|\n";
    std::cout<<"|| ------------------------------------------- ||\n\n";
    std::cout<<"\n\n";
}

// Increases player gold count
void Hero::gainTreasure(int g){
    gold += g;
    std::cout<<"\nYou gained "<<g<<" gold!\n";
}

// Exchanges player gold for food
void Hero::trade(){
    if(gold > 0 && stock < INVENTORY_CAPACITY){
        addItem(1,food);
        gold--;
        std::cout<<"\nYou exchanged one gold for one food\n";
    }
    else{
        std::cout<<"\nYou don't have gold\n";
    }
}

// Reduces player food if available and increase player health
void Hero::eat(){
    if(consumeItem(food)){
        std::cout<<"\nYou ate some food and recovered some health\n";
        health +=5;
    }
    else{
        std::cout<<"\nYou don't have any food in your inventory\n";
    }
}

// Removes text from console
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
