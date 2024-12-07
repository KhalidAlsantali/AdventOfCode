#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::milliseconds
#include <cstdlib>
#include <cmath>


using namespace std;

bool isPossiblePart1(vector<int64_t> values, int64_t target, int64_t prev = 0, size_t index = 0){
    if (index >= values.size()) {
        return prev == target;
    }
    if (prev > target) {
        return false;
    }
    return isPossiblePart1(values, target, prev + values[index], index + 1) ||
           isPossiblePart1(values, target, prev * values[index], index + 1);
}

bool isPossiblePart2(vector<int64_t> values, int64_t target, int64_t prev = 0, size_t index = 0){
    if (index >= values.size()) {
        return prev == target;
    }
    if (prev > target) {
        return false;
    }
    return isPossiblePart2(values, target, prev + values[index], index + 1) ||
           isPossiblePart2(values, target, prev * values[index], index + 1) ||
           isPossiblePart2(values, target, stoll(to_string(prev) + to_string(values[index])), index + 1);
}

int main(){
    string filename = "input.txt";
    unordered_map<int64_t , vector<int64_t >> equations;
    ifstream inputFile(filename);

    if(!inputFile.is_open()){
        cerr << "Error: Couldn't open file" << filename << endl;
        return 1;
    }
    string line;

    while (getline(inputFile, line)) {
        istringstream ss1(line);
        int64_t  result;
        char delimiter;

        ss1 >> result >> delimiter;
        vector<int64_t > values;
        int64_t  value;
        while(ss1 >> value){
            values.push_back(value);
        }
        equations[result] = values;
    }
    inputFile.close();

    int64_t total_1 = 0, total_2 = 0;
    for(const auto& [result, values] : equations){
        if(isPossiblePart1(values, result)){
            total_1 += result;
        }
    }
    for(const auto& [result, values] : equations){
        if(isPossiblePart2(values, result)){
            total_2 += result;
        }
    }
    cout << "Part one answer: " << total_1 << endl;
    cout << "Part two answer: " << total_2 << endl;
    return 0;
}