#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

void doInstruction(vector<string> instruction, map<string,int>& valuesMap){
    string op = instruction[1];
    string wire1 = instruction[0];
    string wire2 = instruction[2];
    string output = instruction[3];
    if(op == "AND"){
         valuesMap[output] = valuesMap[wire1] & valuesMap[wire2];
    }
    if(op == "XOR"){
        valuesMap[output] = valuesMap[wire1] ^ valuesMap[wire2];
    }
    if(op == "OR"){
        valuesMap[output] = valuesMap[wire1] | valuesMap[wire2];
    }
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    map<string,int> valuesMap;
    vector<vector<string>> instructions;
    string line;
    bool readingValues = true;


    while (getline(inputFile, line)) {
        if (line.empty()) {
            readingValues = false;
            continue;
        }

        if (readingValues) {
            istringstream iss(line);
            string key;
            int value;
            

            getline(iss, key, ':');
            iss >> value;
            valuesMap[key] = value;
        } else {

            size_t arrowPos = line.find("->");
            string operation = line.substr(0, arrowPos);
            string output = line.substr(arrowPos + 2);
            
            output.erase(0, output.find_first_not_of(" "));
            output.erase(output.find_last_not_of(" ") + 1);
            
            istringstream iss(operation);
            vector<string> instruction(4);
            iss >> instruction[0] >> instruction[1] >> instruction[2];
            instruction[3] = output;
            instructions.push_back(instruction);
        }
    }

    inputFile.close();

    // cout << "Values Map:" << endl;
    // for (const auto& pair : valuesMap) {
    //     cout << pair.first << ": " << pair.second << endl;
    // }

    // cout << "Instructions:" << endl;
    // for (const auto& instruction : instructions) {
    //     cout << instruction[0] << " " << instruction[1] << " " << instruction[2] << " -> " << instruction[3] << endl;
    // }
    queue<vector<string>> instQ;
    for(const auto& instruction : instructions){
        instQ.push(instruction);
    }

    while(!instQ.empty()){
        vector<string> instruction = instQ.front();
        instQ.pop();
        if(valuesMap.find(instruction[0]) != valuesMap.end() && valuesMap.find(instruction[2]) != valuesMap.end()){
            doInstruction(instruction, valuesMap);
        } else {
            instQ.push(instruction);
        }
    }
    string output = "";

    for (const auto& pair : valuesMap) {
        if(pair.first[0] == 'z'){
            output += to_string(pair.second);
        }
    }

    reverse(output.begin(), output.end());
    int64_t decimal = 0;
    int power = 0;
    
    for(int i = output.length()-1; i >= 0; i--) {
        if(output[i] == '1') {
            decimal += pow(2, power); 
        }
        power++;
    }

    cout << "Part one answer: " << decimal;
    return 0;
}