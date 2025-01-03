#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <map>
#include <unordered_set>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }

    map<int, int> layers;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        int depth, range;
        char colon;
        ss >> depth >> colon >> range;
        layers[depth] = range;
    }

    int delay = 0;
    bool found = false;
    while (!found) {
        found = true;
        for (const auto& layer : layers) {
            int depth = layer.first;
            int range = layer.second;
            int cycle_length = 2 * (range - 1);
            
            if ((delay + depth) % cycle_length == 0) {
                found = false;
                break;
            }
        }
        if (!found) delay++;
    }

    cout << "Part two answer: " << delay << endl;
    return 0;
}