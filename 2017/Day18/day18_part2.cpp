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
#include <queue>
using namespace std;

unordered_map<string, int64_t> registers1, registers2;
queue<int64_t> q1, q2;
int64_t send_count_p1 = 0;

void set(string x, string y, unordered_map<string, int64_t>& registers) {
    char c1 = '\0';
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

void add(string x, string y, unordered_map<string, int64_t>& registers) {
    char c1 = '\0';
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

void mul(string x, string y, unordered_map<string, int64_t>& registers) {
    char c1 = '\0';
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

void mod(string x, string y, unordered_map<string, int64_t>& registers) {
    char c1 = '\0';
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

bool rcv(string x, unordered_map<string, int64_t>& registers, queue<int64_t>& incoming_queue) {
    if (incoming_queue.empty()) {
        return false;
    }
    
    if (x.length() == 1 && isalpha(x[0])) {
        string c(1, x[0]);
        registers[c] = incoming_queue.front();
        incoming_queue.pop();
    }
    return true;
}

void jgz(string x, string y, unordered_map<string, int64_t>& registers, int64_t& program_counter) {
    int64_t x_val = (x.length() == 1 && isalpha(x[0])) ? registers[string(1, x[0])] : stoll(x);
    int64_t y_val = (y.length() == 1 && isalpha(y[0])) ? registers[string(1, y[0])] : stoll(y);
    if (x_val > 0) {
        program_counter += y_val - 1;
    }
}

bool run_program(vector<vector<string>>& instructions, 
                unordered_map<string, int64_t>& registers,
                queue<int64_t>& outgoing_queue,
                queue<int64_t>& incoming_queue,
                int64_t& pc,
                bool is_program_1) {
    
    const auto& instruction = instructions[pc];
    bool made_progress = true;
    
    if (instruction[0] == "snd") {
        if (is_program_1) send_count_p1++;
        if (instruction[1].length() == 1 && isalpha(instruction[1][0])) {
            outgoing_queue.push(registers[string(1, instruction[1][0])]);
        } else {
            outgoing_queue.push(stoll(instruction[1]));
        }
    } 
    else if (instruction[0] == "set") {
        set(instruction[1], instruction[2], registers);
    } 
    else if (instruction[0] == "add") {
        add(instruction[1], instruction[2], registers);
    } 
    else if (instruction[0] == "mul") {
        mul(instruction[1], instruction[2], registers);
    } 
    else if (instruction[0] == "mod") {
        mod(instruction[1], instruction[2], registers);
    } 
    else if (instruction[0] == "rcv") {
        if (!rcv(instruction[1], registers, incoming_queue)) {
            made_progress = false;
            return made_progress;
        }
    } 
    else if (instruction[0] == "jgz") {
        jgz(instruction[1], instruction[2], registers, pc);
    }
    
    if (made_progress) pc++;
    return made_progress;
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
    
    registers1["p"] = 0;
    registers2["p"] = 1;
    
    int64_t pc1 = 0, pc2 = 0;
    bool p1_running = true, p2_running = true;
    
    while (p1_running || p2_running) {
        bool p1_made_progress = false;
        bool p2_made_progress = false;
        
        if (p1_running && pc1 >= 0 && static_cast<size_t>(pc1) < instructions.size()) {
            p1_made_progress = run_program(instructions, registers1, q2, q1, pc1, false);
        } else {
            p1_running = false;
        }
        
        if (p2_running && pc2 >= 0 && static_cast<size_t>(pc2) < instructions.size()) {
            p2_made_progress = run_program(instructions, registers2, q1, q2, pc2, true);
        } else {
            p2_running = false;
        }
        
        if (!p1_made_progress && !p2_made_progress && q1.empty() && q2.empty()) {
            break;
        }
    }
    
    cout << "Program 1 sent " << send_count_p1 << " values." << endl;
    return 0;
}