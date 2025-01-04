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

void spin(const string& move, vector<char>& programs){
    int num = stoi(move.substr(1));
    vector<char> result(programs.end() - num, programs.end());
    result.insert(result.end(), programs.begin(), programs.end() - num);
    programs = result;
}

void exchange(const string& move, vector<char>& programs){
    size_t slash_pos = move.find('/');
    int first_pos = stoi(move.substr(1, slash_pos - 1));
    int second_pos = stoi(move.substr(slash_pos + 1));
    swap(programs[first_pos], programs[second_pos]);
}

void partner(const string& move, vector<char>& programs){
    size_t slash_pos = move.find('/');
    char first = move[slash_pos - 1];
    char second = move[slash_pos + 1];
    auto first_pos = find(programs.begin(), programs.end(), first);
    auto second_pos = find(programs.begin(), programs.end(), second);
    swap(*first_pos, *second_pos);
}

string get_program_string(const vector<char>& programs){
    return string(programs.begin(), programs.end());
}

int main(){
    ifstream inputFile("input.txt");
    if (!inputFile){
        cerr << "Unable to open file input.txt";
        return 1;
    }
   
    string line;
    getline(inputFile, line);
    stringstream ss(line);
    vector<string> moves;
    string move;
    while (getline(ss, move, ',')){
        moves.push_back(move);
    }

    vector<char> programs;
    for (char c = 'a'; c <= 'p'; c++){
        programs.push_back(c);
    }

    for (const string& move : moves){
        if (move[0] == 's') spin(move, programs);
        else if (move[0] == 'x') exchange(move, programs);
        else if (move[0] == 'p') partner(move, programs);
    }

    cout << "Part one answer: ";
    for (char c : programs){
        cout << c;
    }
    cout << endl;


    unordered_map<string, int> seen_states;
    const int target = 1000000000 - 1;
    int i = 0;

    while (i < target){
        string current_state = get_program_string(programs);
        
        if (seen_states.count(current_state)){
            int cycle_length = i - seen_states[current_state];
            int remaining = target - i;
            i += (remaining / cycle_length) * cycle_length;
            if (i == target) break;
        }
        
        seen_states[current_state] = i;
        
        for (const string& move : moves){
            if (move[0] == 's') spin(move, programs);
            else if (move[0] == 'x') exchange(move, programs);
            else if (move[0] == 'p') partner(move, programs);
        }
        i++;
    }

    cout << "Part two answer: ";
    for (char c : programs){
        cout << c;
    }
    cout << endl;
    return 0;
}