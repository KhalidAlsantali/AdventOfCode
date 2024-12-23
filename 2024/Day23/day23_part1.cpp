#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;


int main() {
    ifstream inputFile("input.txt");
    vector<pair<string, string>> connections;
    unordered_map<string, vector<string>> adj;
    vector<vector<string>> cycles;
    string line;
    
    if (!inputFile) {
        cerr << "Unable to open file example.txt";
        return 1;
    }
    
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string first, second;
        if (getline(iss, first, '-') && getline(iss, second)) {
            connections.emplace_back(first, second);
        }
    }
    inputFile.close();
    
    for(const auto& connection : connections) {
        adj[connection.first].push_back(connection.second);
        adj[connection.second].push_back(connection.first);
    }

    for (const auto& pair : adj) {
        for (const auto& neighbor : pair.second) {
            vector<string> cycle;
            for(int i = 0; i < pair.second.size(); i++){
                if(find(adj[neighbor].begin(), adj[neighbor].end(), pair.second[i]) != adj[neighbor].end()){
                    if (pair.first[0] == 't' || neighbor[0] == 't' || pair.second[i][0] == 't') {
                        cycles.push_back({pair.first, neighbor, pair.second[i]});
                    }
                }
            }
        }
    }

    set<set<string>> uniqueCycles;

    for (const auto& cycle : cycles) {
        set<string> cycleSet(cycle.begin(), cycle.end());
        uniqueCycles.insert(cycleSet);
    }

    cycles.clear();
    for (const auto& uniqueCycle : uniqueCycles) {
        cycles.push_back(vector<string>(uniqueCycle.begin(), uniqueCycle.end()));
    }

    cout << "Part one answer: " << cycles.size() << endl;

    return 0;
}