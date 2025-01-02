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

bool checkIfCaught(int& packet_layer, map<int, pair<int, int>>& scanner_positions){
    if(scanner_positions[packet_layer].first == 0){
        return true;
    }
    return false;
}

void moveScanners(map<int, int>& layers, map<int, pair<int, int>>& scanner_positions){
    for(auto& layer : layers){
        pair<int, int>& scanner = scanner_positions[layer.first];
        int* scanner_dir = &(scanner.second);
        int* scanner_pos = &(scanner.first);
        if((*scanner_pos + *scanner_dir) == -1 || (*scanner_pos + *scanner_dir) == layer.second){
            *scanner_dir *= -1;
        }
        *scanner_pos = *scanner_pos + *scanner_dir;
    }
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    map<int, int> layers;
    map<int, pair<int, int>> scanner_positions;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        int layer, depth;
        char colon;
        ss >> layer >> colon >> depth;
        layers[layer] = depth;
    }

    int num_layers = layers.empty() ? 0 : layers.rbegin()->first;

    for(int i = 0; i <= num_layers; i++) {
        scanner_positions[i] = {0, 1};
    }

    int result = 0;
    for(int i = 0; i <= num_layers; i++){
        if(layers.find(i) == layers.end()){
            moveScanners(layers, scanner_positions);
            continue;
        }
        if(layers.find(i) != layers.end() && checkIfCaught(i, scanner_positions)){
            result += i * layers[i];
        }
        moveScanners(layers, scanner_positions);
    }

    cout << "Part one answer: " << result << endl;
    return 0;
}