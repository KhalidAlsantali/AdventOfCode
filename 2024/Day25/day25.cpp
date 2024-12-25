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

void processSchematic(vector<vector<char>>& schematic, vector<vector<int>>& keys, vector<vector<int>>& locks){
    bool is_lock = false;
    if (all_of(schematic[0].begin(), schematic[0].end(), [](char c){ return c == '#'; }) &&
        all_of(schematic[schematic.size()-1].begin(), schematic[schematic.size()-1].end(), [](char c){ return c == '.'; })) {
        is_lock = true;
    }
    vector<int> heights;
    for(size_t j = 0; j < schematic[0].size(); j++){
        int count = -1;
        for(size_t i = 0; i < schematic.size(); i++){
            if(schematic[i][j] == '#'){
                count++;
            }
        }
        heights.push_back(count);
    }

    if(is_lock){
        locks.push_back(heights);
    } else {
        keys.push_back(heights);
    }

}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    vector<vector<int>> keys;
    vector<vector<int>> locks;

    string line;
    vector<vector<char>> schematic;
    while(getline(inputFile, line)){
        if(line.empty() && !schematic.empty()){
            processSchematic(schematic, keys, locks);
            schematic.clear();
            continue;
        }
        if(!line.empty()) {
            schematic.push_back(vector<char>(line.begin(), line.end()));
        }
    }

    if(!schematic.empty()) {
        processSchematic(schematic, keys, locks);
    }

    int combs = 0;
    for(const auto& lock : locks){
        for(const auto& key : keys){
            bool valid = true;
            for(size_t i = 0; i < key.size(); i++){
                if(key[i] + lock[i] >= 6){
                    valid = false;
                    break;
                }
            }
            if(valid) {
                combs++;
            }
        }
    }

    cout << "Part one answer: " << combs << endl;

}
