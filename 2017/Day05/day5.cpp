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

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    vector<int> instructions;
    string line;
    while (getline(inputFile, line)) {
        instructions.push_back(stoi(line));
    }

    int i = 0;
    int steps = 0;
    int current = 0;
    vector<int> instructions_1 = instructions;
    while(static_cast<size_t>(i) < instructions_1.size()){
        current = i;
        i += instructions_1[i];
        ++instructions_1[current];
        steps++;
    }

    cout << "Part one answer: " << steps << endl;

    i = 0;
    steps = 0;
    current = 0;
    vector<int> instructions_2 = instructions;
    while(static_cast<size_t>(i) < instructions_2.size()){
        current = i;
        i += instructions_2[i];
        if(instructions_2[current] >= 3){
            --instructions_2[current];
        } else {
            ++instructions_2[current];
        }
        steps++;
    }

    cout << "Part two answer: " << steps << endl;


}