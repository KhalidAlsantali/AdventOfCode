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

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

void distributeBlocks(vector<int>& numbers, int index){
    int blocks_left = numbers[index];
    numbers[index] = 0;
    while(blocks_left > 0){
        index = (index + 1) % numbers.size();
        ++numbers[index];
        --blocks_left;
    }
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    vector<int> numbers;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string temp;
        while (ss >> temp) {
            numbers.push_back(stoi(temp));
        }
    }
    unordered_set<vector<int>, VectorHash> seen;
    int cycles = 0;
    bool cycle_started = false;
    vector<int> cycle_start;
    while(true){
        if (seen.find(numbers) != seen.end()) {
            cycle_started = true;
            cycle_start = numbers;
            break;
        }
        int max_block_index = distance(numbers.begin(), max_element(numbers.begin(), numbers.end()));
        seen.insert(numbers);
        distributeBlocks(numbers, max_block_index);
        ++cycles;
    }

    int loop_cycles = 0;
    while(true){
        int max_block_index = distance(numbers.begin(), max_element(numbers.begin(), numbers.end()));
        distributeBlocks(numbers, max_block_index);
        ++loop_cycles;
        if(numbers == cycle_start){
            break;
        }
    }
 
    cout << "Part one answer: " << cycles << endl;
    cout << "Part two answer: " << loop_cycles << endl;
    return 0;
}