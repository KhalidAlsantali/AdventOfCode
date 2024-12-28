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
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    unordered_set<string> first;
    unordered_set<string> connected;
    
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string temp;
        ss >> temp;
        first.insert(temp);
        if (line.find("->") != string::npos) {
            size_t pos = line.find("->");
            string rest = line.substr(pos + 2);
            stringstream ssRest(rest);
            while (ssRest >> temp) {
                if (temp.back() == ',') {
                    temp.pop_back();
                }
                connected.insert(temp);
            }
        }
    }

    unordered_set<string> difference;
    for (const auto& elem : first) {
        if (connected.find(elem) == connected.end()) {
            difference.insert(elem);
        }
    }

    cout << "Part one answer: " << *difference.begin() << endl;
    return 0;
}
