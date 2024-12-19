#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

vector<string> patterns;
unordered_map<string, bool> memo;
unordered_map<string, int64_t> memo_ways;

bool findPattern(string pattern, vector<string>& patterns){
    if(memo.count(pattern) > 0){
        return memo[pattern];
    }
    bool result = binary_search(patterns.begin(), patterns.end(), pattern);
    memo[pattern] = result;
    return result;
}

bool isDesignPossible(const string& design) {
    if(design.empty()) {
        return true;
    }
   
    for(int len = 1; len <= design.length(); len++) {
        string prefix = design.substr(0, len);
        if(findPattern(prefix, patterns)) {
            if(isDesignPossible(design.substr(len))) {
                return true;
            }
        }
    }
   
    return false;
}

int64_t countWays(const string& design) {
    if(design.empty()) {
        return 1;
    }
    if(memo_ways.count(design) > 0) {
        return memo_ways[design];
    }
   
    int64_t ways = 0;
    for(int len = 1; len <= design.length(); len++) {
        string prefix = design.substr(0, len);
        if(findPattern(prefix, patterns)) {
            ways += countWays(design.substr(len));
        }
    }
    memo_ways[design] = ways;
    return ways;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
    string line;
    vector<string> designs;
    if (getline(inputFile, line)) {
        stringstream ss(line);
        string item;
        while (getline(ss, item, ',')) {
            item.erase(0, item.find_first_not_of(' '));
            item.erase(item.find_last_not_of(' ') + 1);
            patterns.push_back(item);
        }
    }
    getline(inputFile, line);
    while (getline(inputFile, line)) {
        designs.push_back(line);
    }
    inputFile.close();
    
    sort(patterns.begin(), patterns.end());
    int sum = 0;
    int64_t sum2 = 0;
    for(const auto& design : designs){
        if(isDesignPossible(design)){
            sum++;
        }
        memo_ways.clear(); 
        int64_t ways = countWays(design);
        sum2 += ways;
    }
    cout << "Part one answer: " << sum << endl;
    cout << "Part two answer: " << sum2 << endl;
    return 0;
}