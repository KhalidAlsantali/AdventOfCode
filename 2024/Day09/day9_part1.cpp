#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <cctype>
#include <set>

using namespace std;

int main(){
    string input_filename = "input.txt";
    ifstream inputFile(input_filename);
    vector<string> diskmap;
    vector<string> layout;

    string line;
    while (getline(inputFile, line)) {
        for(char c : line){
            diskmap.push_back(string(1, c));
        }
    }
    int file_sum = 0;
    for(size_t i = 0; i < diskmap.size(); ++i){
        for(int j = 0; j < stoi(diskmap[i]); ++j){
            if(i % 2 == 0){
                layout.push_back(to_string(i / 2));
                file_sum++;
            } else {
                layout.push_back(string(1, '.'));
            }
        }
    }

    for(int i = layout.size() - 1; i >= -1; --i){
        string file_block = layout[i];
        auto insert_loc = find(layout.begin(), layout.end(), ".");
        if(distance(layout.begin(), insert_loc) > file_sum - 1){
            break;
        }
        layout[i] = ".";
        layout[distance(layout.begin(), insert_loc)] = file_block;
    }

    int64_t checksum_total = 0;
    for(size_t i = 0; i < layout.size(); ++i){
        if(layout[i] == "."){
            break;
        }
        checksum_total += stoi(layout[i]) * i;
    }
    cout << "Part one answer: " << checksum_total << endl;
    return 0;
}
