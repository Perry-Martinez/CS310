#include<iostream>
#include<string>
#include<utility>
#include<iomanip>
#include<cmath>
#include<sstream>

const int16_t NUM_CANDIDATES = 5;
const int16_t COLUMN = 3;

int16_t totalVotes = 0;

// Holds the information for the current candidate with the greatest amount of votes
std::pair<std::string,int16_t> winner = {"",0};

bool isTie = false;

int main(){
    std::string electionTable[NUM_CANDIDATES][COLUMN];
    
    //  Prompts user
    for(size_t i = 0; i < NUM_CANDIDATES; i++){
        std::cout<<"Enter the last name of the candidate\n";
        std::cin>>electionTable[i][0];
        std::cout<<"Enter the number of votes that they recieved\n";
        std::cin>>electionTable[i][1];

        //  Increases total votes amount each iteration
        totalVotes += stoi(electionTable[i][1]);

        //  Updates winner and isTie variable each iteration
        if(stoi(electionTable[i][1]) > winner.second){
            winner.first = electionTable[i][0];
            winner.second = stoi(electionTable[i][1]);
            isTie = false;
        }
        else if(stoi(electionTable[i][1]) == winner.second){
            isTie = true;
        }
    }
    //  Formatting for console output
    std::cout<<std::left<<'\n';
    std::cout<<std::setw(20)<<"Candidate"<<std::setw(20)<<"Votes Received"<<std::setw(15)<<"% of Total Votes\n";
    for(size_t i = 0; i < NUM_CANDIDATES; i++){
        //  output stream object to set the precision of the float value before it is stored as a string in the 2D array
        std::ostringstream outputStream;
        outputStream<<std::fixed<<std::setprecision(2)<<(static_cast<float>(stoi(electionTable[i][1])) / totalVotes) * 100.0f;
        electionTable[i][2] = outputStream.str();
    }
    //  Outputs candidate name, votes and percentages
    for(size_t i = 0; i < NUM_CANDIDATES; i++){
        for(size_t j = 0; j < COLUMN; j++){
            std::cout<<std::setw(20)<<electionTable[i][j];
        }
        std::cout<<'\n';
    }
    std::cout<<std::setw(20)<<"Total"<<totalVotes<<"\n\n";
    //  Final output based on single winner or tie vote
    if(!isTie) std::cout<<"The Winner of the Election is "<<winner.first<<" with "<<winner.second<<" votes."<<std::endl;
    else std::cout<<"The election is a tie!"<<std::endl;

    return 0;
}