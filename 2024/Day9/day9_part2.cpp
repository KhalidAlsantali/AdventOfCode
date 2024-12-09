#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <cctype>
#include <set>

using namespace std;

int getEmptySize(const vector<string>& layout, int file_size) {
    int current_length = 0;
    for (size_t i = 0; i < layout.size(); ++i) {
        if (layout[i] == ".") {
            current_length++;
            if (current_length == file_size) {
                return i - file_size + 1; 
            }
        } else {
            current_length = 0;
        }
    }
    return -1;
}

int main(){
    string input_filename = "input.txt";
    ifstream inputFile(input_filename);
    vector<string> diskmap;
    vector<string> layout;
    map<int, int> file_ids;

    string line;
    while (getline(inputFile, line)) {
        for(char c : line){
            diskmap.push_back(string(1, c));
        }
    }
    int file_sum = 0;
    for(size_t i = 0; i < diskmap.size(); ++i){
        int length;
        for(int j = 0; j < stoi(diskmap[i]); ++j){
            if(i % 2 == 0){
                layout.push_back(to_string(i / 2));
                length = stoi(diskmap[i]);
                file_sum++;
                file_ids[i / 2] = length;
            } else {
                layout.push_back(string(1, '.'));
            }
        }
    }

    for (auto it = file_ids.rbegin(); it != file_ids.rend(); ++it) {
        auto block_it = find(layout.begin(), layout.end(), to_string(it->first));
        int block_index = distance(layout.begin(), block_it);
        string c;
        int empty_index = getEmptySize(layout, it->second);
        if(empty_index == -1 || empty_index >= block_index){
            continue;
        }

        for(int i = 0; i < it->second; ++i){
            layout[empty_index + i] = to_string(it->first);
            layout[block_index + i] = ".";
        }
    }

    int64_t checksum_total = 0;
    for(size_t i = 0; i < layout.size(); ++i){
        if(layout[i] == "."){
            continue;
        }
        checksum_total += stoi(layout[i]) * i;
    }
    cout << "Part two answer: " << checksum_total << endl;
    return 0;
}
