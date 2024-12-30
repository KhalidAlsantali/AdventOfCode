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
#include <regex>
#include <boost/regex.hpp>
using namespace std;

void removeExclamation(string& stream){
    for(size_t i = 0; i < stream.size(); i++){
        if(stream[i] == '!'){
            stream.erase(i, 2);
            i--;
        }
    }
}

void removeGarbage(string& input, int& garbageCount) {
    boost::regex pattern(R"(<[^>]*>)");
    string result = input;
    
    boost::sregex_iterator iter(input.begin(), input.end(), pattern);
    boost::sregex_iterator end;
    
    vector<pair<int, int>> positions;
    while (iter != end) {
        positions.push_back({iter->position(), iter->length()});
        garbageCount += iter->length() - 2;
        ++iter;
    }
    
    sort(positions.rbegin(), positions.rend());
    for (const auto& pos : positions) {
        result.erase(pos.first, pos.second);
    }
    
    input = result;
}

int countValue(const string& stream, int sum = 0, int level = 1) {
    if(stream.empty()) {
        return sum;
    }
   
    std::vector<std::string> matches;
    boost::regex pattern(R"(\{(?:[^{}]|(?R))*\})");
   
    boost::sregex_iterator iter(stream.begin(), stream.end(), pattern);
    boost::sregex_iterator end;
   
    int totalSum = sum;
   
    while (iter != end) {
        std::string match = iter->str();
        match.erase(0, 1);
        match.erase(match.size() - 1, 1);
        totalSum = countValue(match, totalSum + level, level + 1);
        ++iter;
    }
   
    return totalSum;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
   
    string stream;
    int garbageCount = 0;
    getline(inputFile, stream);
    removeExclamation(stream);
    removeGarbage(stream, garbageCount);
    cout << "Part one answer: " << countValue(stream) << endl;
    cout << "Part two answer: " << garbageCount << endl;
    return 0;
}