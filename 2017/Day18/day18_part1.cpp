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

unordered_map<string, int64_t> registers;
int64_t program_counter = 0;
int64_t snd_freq = 0;

void snd(string x) {
    if (x.length() == 1 && isalpha(x[0])) {
        string c(1, x[0]);
        snd_freq = registers[c];
    }
    else {
        int64_t num = stoll(x);
        snd_freq = num;
    }
}

void set(string x, string y) {
    char c1;
    if (x.length() == 1 && isalpha(x[0])) {
        c1 = x[0];
    }
   
    if (y.length() == 1 && isalpha(y[0])) {
        char c2 = y[0];
        registers[string(1, c1)] = registers[string(1, c2)];
    }
    else {
        int64_t num = stoll(y);
        registers[string(1, c1)] = num;
    }
}

void add(string x, string y) {
    char c1;
    if (x.length() == 1 && isalpha(x[0])) {
        c1 = x[0];
    }
   
    if (y.length() == 1 && isalpha(y[0])) {
        char c2 = y[0];
        registers[string(1, c1)] += registers[string(1, c2)];
    }
    else {
        int64_t num = stoll(y);
        registers[string(1, c1)] += num;
    }
}

void mul(string x, string y) {
    char c1;
    if (x.length() == 1 && isalpha(x[0])) {
        c1 = x[0];
    }
    if (y.length() == 1 && isalpha(y[0])) {
        char c2 = y[0];
        registers[string(1, c1)] *= registers[string(1, c2)];
    } 
    else {
        int64_t num = stoll(y);
        registers[string(1, c1)] *= num;
    }
}

void mod(string x, string y) {
    char c1;
    if (x.length() == 1 && isalpha(x[0])) {
        c1 = x[0];
    }
    if (y.length() == 1 && isalpha(y[0])) {
        char c2 = y[0];
        registers[string(1, c1)] %= registers[string(1, c2)];
    } 
    else {
        int64_t num = stoll(y);
        registers[string(1, c1)] %= num;
    }
}

bool rcv(string x) {
    if (x.length() == 1 && isalpha(x[0])) {
        string c(1, x[0]);
        if (registers[c] != 0) {
            cout << snd_freq << endl;
            return true;
        }
    }
    return false;
}

void jgz(string x, string y) {
    int64_t x_val = (x.length() == 1 && isalpha(x[0])) ? registers[string(1, x[0])] : stoll(x);
    int64_t y_val = (y.length() == 1 && isalpha(y[0])) ? registers[string(1, y[0])] : stoll(y);
    if (x_val > 0) {
        program_counter += y_val - 1;
    }
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    vector<vector<string>> instructions;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string temp;
        vector<string> instruction;
        while(ss >> temp) {
            instruction.push_back(temp);
        }
        instructions.push_back(instruction);
    }
    
    program_counter = 0;
    bool should_stop = false;
    while (program_counter >= 0 && program_counter < instructions.size() && !should_stop) {
        const auto& instruction = instructions[program_counter];
        if (instruction[0] == "snd") {
            snd(instruction[1]);
        } 
        else if (instruction[0] == "set") {
            set(instruction[1], instruction[2]);
        } 
        else if (instruction[0] == "add") {
            add(instruction[1], instruction[2]);
        } 
        else if (instruction[0] == "mul") {
            mul(instruction[1], instruction[2]);
        } 
        else if (instruction[0] == "mod") {
            mod(instruction[1], instruction[2]);
        } 
        else if (instruction[0] == "rcv") {
            should_stop = rcv(instruction[1]);
        } 
        else if (instruction[0] == "jgz") {
            jgz(instruction[1], instruction[2]);
        } 
        else {
            cerr << "Unknown instruction: " << instruction[0] << endl;
        }
        program_counter++;
    }
    return 0;
}