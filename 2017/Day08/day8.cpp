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
#include <map>
#include <functional>

using namespace std;

std::map<std::string, std::function<bool(int, int)>> operators = {
    {"==", [](int a, int b) { return a == b; }},
    {"!=", [](int a, int b) { return a != b; }},
    {">=", [](int a, int b) { return a >= b; }},
    {"<=", [](int a, int b) { return a <= b; }},
    {">",  [](int a, int b) { return a > b;  }},
    {"<",  [](int a, int b) { return a < b;  }}
};

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    vector<vector<string>> instructions;
    unordered_map<string, int> registers;
    
    string line;
    while (getline(inputFile, line)) {
        vector<string> instruction;
        stringstream ss(line);
        string temp;
        while(ss >> temp){
            instruction.push_back(temp);
        }
        instructions.push_back(instruction);
    }

    int maxValDuring = INT_MIN;  
    for(const auto& inst : instructions){
        string reg = inst[0];
        string dir = inst[1];
        int amount = stoi(inst[2]);
        string checkReg = inst[4];
        string op = inst[5];
        int compNum = stoi(inst[6]);
        if(operators[op](registers[checkReg], compNum)){
            if(dir == "inc"){
                registers[reg] += amount;
            } else if (dir == "dec"){
                registers[reg] -= amount;
            }
        }
        for (const auto& pair : registers) {
            if (pair.second > maxValDuring) {
                maxValDuring = pair.second;
            }
        }
    }

    int maxVal = INT_MIN;
    for (const auto& pair : registers) {
        if (pair.second > maxVal) {
            maxVal = pair.second;
        }
    }

    cout << "Part one answer: " << maxVal << endl;
    cout << "Part two answer: " << maxValDuring << endl;
    return 0;
}