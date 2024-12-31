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

int calcDist(int q, int r){
    return (abs(q - 0) + abs(q + r - 0 - 0) + abs(r - 0)) / 2;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    vector<string> steps;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string step;
        while (getline(ss, step, ',')) {
            steps.push_back(step);
        }
    }

    unordered_map<string, pair<int, int>> moves = {
        {"n", {0, -1}},
        {"s", {0, 1}},
        {"ne", {1, -1}},
        {"nw", {-1, 0}},
        {"se", {1, 0}},
        {"sw", {-1, 1}}
    };

    int q = 0, r = 0;
    int maxDist = 0;
    for(string step : steps){
        pair<int, int> move = moves[step];
        q += move.first;
        r += move.second;
        int dist = calcDist(q, r);
        if(dist > maxDist){
            maxDist = dist;
        }
    }

    int finalDist = calcDist(q, r);

    cout << "Part one answer: " << finalDist << endl;
    cout << "Part two answer: " << maxDist << endl;

}