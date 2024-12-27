#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool isAnagram(const string &s1, const string &s2) {
    

    unordered_map<char, int> charCount;
    

    for(char ch: s1) 
        charCount[ch] += 1;
  

    for(char ch: s2) 
        charCount[ch] -= 1;
  
    for (auto& pair : charCount) {
        if (pair.second != 0) {
            return false;
        }
    }
    
    return true;
}


bool checkValid(unordered_map<string, int>& passphrase){
    for(const auto& pair : passphrase){
        if(pair.second > 1){
            return false;
        }
    }

    for(const auto& pair : passphrase){
        for(const auto& second_pair : passphrase){
            if(pair == second_pair) continue;
            if(isAnagram(pair.first, second_pair.first)){
                return false;
            }
        }
    }
    return true;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    vector<vector<string>> passphrases;
    
    string line;
    while (getline(inputFile, line)) {
        vector<string> parts;
        stringstream ss(line);
        string temp;
        while(ss >> temp){
            parts.push_back(temp);
        }
        passphrases.push_back(parts);
    }
    
    int totalValid = 0;
    for(const auto& pp : passphrases){
        unordered_map<string, int> occurances;
        for(const auto& part : pp){
            occurances[part] = ++occurances[part];
        }
        if(checkValid(occurances)){
            totalValid++;
        }
    }

    cout << "Part two answer: " << totalValid << endl;
    return 0;
}