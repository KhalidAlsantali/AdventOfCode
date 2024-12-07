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

bool isPossible(vector<int64_t> values, int64_t target, int64_t prev = 0, int index = 0){
    if (index >= values.size()) {
        return prev == target;
    }
    if (prev > target) {
        return false;
    }
    return isPossible(values, target, prev + values[index], index + 1) ||
           isPossible(values, target, prev * values[index], index + 1) ||
           isPossible(values, target, stoll(to_string(prev) + to_string(values[index])), index + 1);
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

    int64_t total = 0;
    for(const auto& [result, values] : equations){
        if(isPossible(values, result)){
            total += result;
        }
    }
    cout << total << endl;
}