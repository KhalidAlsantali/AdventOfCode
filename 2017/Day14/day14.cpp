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
#include <stack>
using namespace std;

string oneHash(string key) {
    int max = 256;
    vector<int> list;
    for(int i = 0; i < max; i++) {
        list.push_back(i);
    }
    int skip = 0;
    int index = 0;
    vector<int> lengths;
    for(char c : key) {
        lengths.push_back(static_cast<int>(c));
    }
    lengths.insert(lengths.end(), {17, 31, 73, 47, 23});
    
    for(int round = 0; round < 64; round++) {
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
            for(int mem : sublist) {
                list[sublist_index] = mem;
                sublist_index = (sublist_index + 1) % list.size();
            }
            index = (index + num + skip) % list.size();
            ++skip;
        }
    }

    vector<vector<int>> splits;
    for(size_t i = 0; i < 256; i += 16) {
        splits.emplace_back(list.begin() + i, list.begin() + i + 16);
    }

    vector<int> total;
    for(vector<int> split : splits) {
        int xorTotal = 0;
        for(int num : split) {
            xorTotal ^= num;
        }
        total.push_back(xorTotal);
    }

    string result;
    for (int num : total) {
        stringstream ss;
        ss << setfill('0') << setw(2) << hex << num;
        result += ss.str();
    }
    return result;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }


    string key;
    getline(inputFile, key);

    vector<string> disk;
    for(int i = 0; i < 128; i++){
        string new_key = key + "-" + to_string(i);
        disk.push_back(oneHash(new_key));
    }

    vector<string> binaryDisk;
    for (const string& hexStr : disk) {
        string binaryStr;
        for (char hexChar : hexStr) {
            switch (hexChar) {
                case '0': binaryStr += "0000"; break;
                case '1': binaryStr += "0001"; break;
                case '2': binaryStr += "0010"; break;
                case '3': binaryStr += "0011"; break;
                case '4': binaryStr += "0100"; break;
                case '5': binaryStr += "0101"; break;
                case '6': binaryStr += "0110"; break;
                case '7': binaryStr += "0111"; break;
                case '8': binaryStr += "1000"; break;
                case '9': binaryStr += "1001"; break;
                case 'a': binaryStr += "1010"; break;
                case 'b': binaryStr += "1011"; break;
                case 'c': binaryStr += "1100"; break;
                case 'd': binaryStr += "1101"; break;
                case 'e': binaryStr += "1110"; break;
                case 'f': binaryStr += "1111"; break;
            }
        }
        binaryDisk.push_back(binaryStr);
    }

    int usedSquares = 0;
    for (const string& binaryStr : binaryDisk) {
        for(char c : binaryStr){
            if(c == '1'){
                usedSquares++;
            }
        }
    }
    vector<pair<int, int>> dirs = {{1,0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<vector<bool>> visited_map(binaryDisk.size(), vector<bool>(binaryDisk[0].size(), false));
    int region_id = 0;
    for (size_t i = 0; i < binaryDisk.size(); i++){
        for (size_t j = 0; j < binaryDisk[i].size(); j++){
            if(visited_map[i][j] || binaryDisk[i][j] == '0'){
                continue;
            } else {
                stack<pair<int, int>> stack;
                stack.push(make_pair(i, j));
                visited_map[i][j] = true;

                while(!stack.empty()){
                    pair<int, int> current = stack.top();
                    stack.pop();

                    for(pair<int, int> dir : dirs){
                        int ni = current.first + dir.first;
                        int nj = current.second + dir.second;

                        if(ni >= 0 && nj >= 0 && static_cast<size_t>(ni) < binaryDisk.size() && static_cast<size_t>(nj) < binaryDisk[0].size()){

                            if(binaryDisk[i][j] == binaryDisk[ni][nj] && !visited_map[ni][nj]){
                                stack.push(make_pair(ni, nj));
                                visited_map[ni][nj] = true;
                            }
                        }
                    }
                }
                region_id++;
            }
        }
    }


    
    
    cout << "Part one answer: " << usedSquares << endl;
    cout << "Part two answer: " << region_id << endl;
    return 0;
}