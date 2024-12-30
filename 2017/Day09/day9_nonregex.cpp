#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void removeExclamation(string& stream) {
    for(size_t i = 0; i < stream.size(); i++) {
        if(stream[i] == '!') {
            stream.erase(i, 2);
            i--;
        }
    }
}

void removeGarbage(string& input, int& garbageCount) {
    string result;
    bool inGarbage = false;
    
    for(size_t i = 0; i < input.length(); i++) {
        if(input[i] == '<' && !inGarbage) {
            inGarbage = true;
            continue;
        }
        
        if(input[i] == '>' && inGarbage) {
            inGarbage = false;
            continue;
        }
        
        if(inGarbage) {
            garbageCount++;
        } else if(!inGarbage && input[i] != '>') {
            result += input[i];
        }
    }
    
    input = result;
}

int countGroups(const string& stream) {
    stack<int> levels;
    int totalScore = 0;
    int currentLevel = 0;
    
    for(char c : stream) {
        if(c == '{') {
            currentLevel++;
            levels.push(currentLevel);
        }
        else if(c == '}' && !levels.empty()) {
            totalScore += levels.top();
            levels.pop();
            currentLevel--;
        }
    }
    
    return totalScore;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    
    string stream;
    int garbageCount = 0;
    getline(inputFile, stream);
    
    removeExclamation(stream);
    removeGarbage(stream, garbageCount);
    
    cout << "Part one answer: " << countGroups(stream) << endl;
    cout << "Part two answer: " << garbageCount << endl;
    
    return 0;
}