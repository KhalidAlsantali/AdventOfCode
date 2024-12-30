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
    int max = 256;
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    vector<int> list;
    for(int i = 0; i < max; i++){
        list.push_back(i);
    }
    vector<int> values;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string item;
        while (getline(ss, item, ',')) {
            values.push_back(stoi(item));
        }
    }

    int skip = 0;
    int index = 0;
    for(int num : values) {
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

    cout << "Part one answer: " << list[0] * list[1] << endl;


}