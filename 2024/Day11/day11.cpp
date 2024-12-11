#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <cctype>
#include <set>
#include <utility>

using namespace std;

int main(){
    string input_filename = "input.txt";
    ifstream inputFile(input_filename);
    unordered_map<string, int64_t> stones;
    unordered_map<string, int64_t> stones25;

    string line, number;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        while (iss >> number) {
            stones[number] = ++stones[number];
        }
    }

    for(int i = 0; i < 75; i++){
        unordered_map<string, int64_t> next_stones;
        for (const auto& stone : stones) {
            if(stoull(stone.first) == 0){
                next_stones["1"] = next_stones["1"] + stone.second;
            } else if(stone.first.size() % 2 == 0){
                size_t midpoint = stone.first.size() / 2;
                next_stones[stone.first.substr(0, midpoint)] = next_stones[stone.first.substr(0, midpoint)] + stone.second;
                next_stones[to_string(stoull(stone.first.substr(midpoint)))] = next_stones[to_string(stoull(stone.first.substr(midpoint)))] + stone.second;
            } else {
                next_stones[to_string(stoull(stone.first) * 2024)] = next_stones[to_string(stoull(stone.first) * 2024)] + stone.second;
            }
        }
        if(i == 24){
            stones25 = next_stones;
        }
        stones = next_stones;
    }
    
    int64_t sump1 = 0;
    for (const auto& stone : stones25) {
        sump1 = sump1 + stone.second;
    }
    int64_t sump2 = 0;
    for (const auto& stone : stones) {
        sump2 = sump2 + stone.second;
    }

    cout << "Part one answer: " << sump1 << endl;
    cout << "Part two answer: " << sump2 << endl;
    return 0;
}
