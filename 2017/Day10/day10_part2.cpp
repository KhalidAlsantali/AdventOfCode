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
#include <iomanip>

using namespace std;

int skip = 0;
int index = 0;

int oneHash(const vector<int>& lengths, vector<int>& list){
    for(int num : lengths) {
        int start_pos = index % list.size();
        size_t needed_length = num;
        vector<int> sublist;

        while (sublist.size() < needed_length) {
            int curr_pos = (start_pos + sublist.size()) % list.size();
            sublist.push_back(list[curr_pos]);
        }

        reverse(sublist.begin(), sublist.end());
        int sublist_index = start_pos;
        for(int mem : sublist){
            list[sublist_index] = mem;
            sublist_index = (sublist_index + 1) % list.size();
        }

        index = (index + num + skip) % list.size();
        ++skip;
    }
    return list[0] * list[1];
}

int main() {
    ifstream inputFile("input.txt");
    int max = 256;
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    vector<int> list;
    for(int i = 0; i < max; i++){
        list.push_back(i);
    }
    vector<int> lengths;
    string line;
    getline(inputFile, line);
    for(char c : line){
        lengths.push_back(static_cast<int>(c));
    }
    lengths.insert(lengths.end(), {17, 31, 73, 47, 23});

    for(int i = 0; i < 64; i++){
        oneHash(lengths, list);
    }

    vector<vector<int>> splits;

    for(size_t i = 0; i < 256; i += 16){
        splits.emplace_back(list.begin() + i, list.begin() + i + 16);
    }
    vector<int> total;
    for(vector<int> split : splits){
        int xorTotal = 0;
        for(int num : split) {
            xorTotal ^= num;
        }
        total.push_back(xorTotal);
    }
    
    cout << "Part two answer: ";

    for (int num : total) {
        cout << setfill('0') << setw(2) << hex << num;
    }
    cout << endl;
    return 0;
}