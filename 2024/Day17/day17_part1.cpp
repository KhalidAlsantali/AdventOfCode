#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;
int register_A = 0, register_B = 0, register_C = 0;
int program_counter = 0;
bool jumped = false;

int combo2num(int combo_operand){
    switch (combo_operand){
        case 0:
        case 1:
        case 2:
        case 3:
            return combo_operand;
        case 4:
            return register_A;
        case 5:
            return register_B;
        case 6:
            return register_C;
        default:
            return -1;
    }
}

void adv(int operand){ // COMBO - OPCODE 0
    register_A = register_A / pow(2, combo2num(operand));
}

void bxl(int operand){ // LITERAL - OPCODE 1
    register_B = register_B ^ operand;
}

void bst(int operand){ // COMBO - OPCODE 2
    register_B = combo2num(operand) % 8;
}

void jnz(int operand){ // LITERAL - OPCODE 3
    if(register_A == 0){
        return;
    } else {
        jumped = true;
        program_counter = operand;
    }
}

void bxc(){ // NO OPERAND - OPCODE 4
    register_B = register_B ^ register_C;
}

void out(int operand){ // COMBO - OPCODE 5
    static bool first_output = true;
    if (!first_output) {
        cout << ",";
    }
    cout << combo2num(operand) % 8;
    first_output = false;
}

void bdv(int operand){ // COMBO - OPCODE 6
    register_B = register_A / pow(2, combo2num(operand));
}

void cdv(int operand){ // COMBO - OPCODE 7
    register_C = register_A / pow(2, combo2num(operand));
}

int main() {
    vector<int> program;

    ifstream input_file("example.txt");
    if (!input_file) {
        cerr << "Error: Could not open the input_file." << endl;
        return 1;
    }

    string line;

    getline(input_file, line);
    register_A = stoi(line.substr(line.find(":") + 1));

    getline(input_file, line);
    register_B = stoi(line.substr(line.find(":") + 1));

    getline(input_file, line);
    register_C = stoi(line.substr(line.find(":") + 1));

    getline(input_file, line);

    if (getline(input_file, line)) {
        size_t pos = line.find(":");
        if (pos != string::npos) {
            string program_data = line.substr(pos + 1);
            
            program_data.erase(0, program_data.find_first_not_of(" \t"));
            program_data.erase(program_data.find_last_not_of(" \t") + 1);

            istringstream ss(program_data);
            int num;
            while (ss >> num) {
                program.push_back(num);
                if (ss.peek() == ',') {
                    ss.ignore();
                }
            }
        }
    }
    input_file.close();

    // cout << "Register A: " << register_A << endl;
    // cout << "Register B: " << register_B << endl;
    // cout << "Register C: " << register_C << endl;

    // cout << "Program: ";
    // for (int value : program) {
    //     cout << value << " ";
    // }
    // cout << endl;

    while(program_counter < program.size()){
        jumped = false;
        switch (program[program_counter]){
            case 0:
                adv(program[program_counter + 1]);
                break;
            case 1:
                bxl(program[program_counter + 1]);
                break;
            case 2:
                bst(program[program_counter + 1]);
                break;
            case 3:
                jnz(program[program_counter + 1]);
                break;
            case 4:
                bxc();
                break;
            case 5:
                out(program[program_counter + 1]);
                break;
            case 6:
                bdv(program[program_counter + 1]);
                break;
            case 7:
                cdv(program[program_counter + 1]);
                break;
            default:
                break;
        }
        if(jumped){
            continue;
        } else {
            program_counter = program_counter + 2;
        }
    }

    return 0;
}
