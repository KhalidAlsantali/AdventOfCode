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

vector<string> findInstruction(const string& output, const vector<vector<string>>& instructions) {
    for (const auto& instruction : instructions) {
        if (instruction[0] == output || instruction[2] == output) {
            return instruction;
        }
    }
    return {};
}

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
    vector<vector<string>> wrong_instructions;
    for(const auto& inst : instructions){
        string op = inst[1];
        string wire1 = inst[0];
        string wire2 = inst[2];
        string output = inst[3];
        if(op == "AND"){
            if((inst[0] == "x00" && inst[2] == "y00") || (inst[0] == "y00" && inst[2] == "x00")){
                continue;
            }
            if(inst[3][0] == 'z'){
                wrong_instructions.push_back(inst);
            } else {
                vector<string> next_inst = findInstruction(inst[3], instructions);
                if(next_inst[1] != "OR"){
                    wrong_instructions.push_back(inst);
                }
            }
        }
        if(op == "XOR"){
            if(!((inst[0][0] == 'x' && inst[2][0] == 'y') || (inst[0][0] == 'y' && inst[2][0] == 'x') || inst[3][0] == 'z')){
                wrong_instructions.push_back(inst);
                continue;
            }
            if(inst[3][0] != 'z'){
                vector<string> next_inst = findInstruction(inst[3], instructions);
                if(next_inst[1] == "OR"){
                    wrong_instructions.push_back(inst);
                }
            }
        }
        if(op == "OR"){
            if(inst[3][0] == 'z'){
                if(inst[3] != "z45"){
                    wrong_instructions.push_back(inst);
                }
            }
        }
    }
    vector<string> wrong_wires;
    for (const auto& inst : wrong_instructions) {
        wrong_wires.push_back(inst[3]);
    }
    sort(wrong_wires.begin(), wrong_wires.end());
    cout << "Part two answer: ";
    for (size_t i = 0; i < wrong_wires.size(); ++i) {
        cout << wrong_wires[i];
        if (i != wrong_wires.size() - 1) {
            cout << ",";
        }
    }
    return 0;
}