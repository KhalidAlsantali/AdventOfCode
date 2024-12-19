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
    for(const auto& design : designs){
        cout << design;
        if(isDesignPossible(design)){
            sum++;
            continue;
        }
    }

    cout << "Part one answer: " << sum;
    return 0;
}
