#include<iostream>
#include<string>

//  Write a program that prompts the user to input a string. 
//  The program then uses the function substr to remove all the vowels from the string. 
//  For example, if str = "There", then after removing all the vowels, str = "Thr".
//  After removing all the vowels, output the string. 
//  Your program must contain a function to remove all the vowels and a function to determine whether a character is a vowel.


// Function declarations
bool checkVowel(const char&);
std::string removeVowels(const std::string&);
std::string removeVowelsWithSubStr(const std::string&);

// string variable containing all vowels
const std::string vowels = "aeiouAEIOU";

int main(){
    std::string userStr = "";

    std::cout<<"Input a string\n";
    std::getline(std::cin,userStr);

    // std::cout<<removeVowels(userStr)<<std::endl;
    std::cout<<removeVowelsWithSubStr(userStr)<<std::endl;
}

// Function to detrmine to if a character is a vowel
bool checkVowel(const char& c){
    for(auto l : vowels){
        if(c == l) return true;
    }
    return false;
}

//  Removes all vowels from the string
std::string removeVowels(const std::string& str){
    std::string result = "";
    for(auto c : str){
        if(!checkVowel(c)) result.push_back(c);
    }
    return result;
}

// Removes all vowels from the string using the substr function
std::string removeVowelsWithSubStr(const std::string& str){
    std::string result = "";
    for(int i = 0;i<str.length();i++){
        if(!checkVowel(str[i])) result += str.substr(i,1);
    }
    return result;
}