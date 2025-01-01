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
#include <queue>

using namespace std;

vector<int> parent;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int px = find(x), py = find(y);
    if (px != py){
        parent[px] = py;
    }
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    unordered_map<int, vector<int>> graph;
    string line;
    int maxNode = 0;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        int node;
        char arrow[4];
        ss >> node;
        maxNode = max(maxNode, node);
        ss >> arrow;
        int neighbor;
        while (ss >> neighbor) {
            maxNode = max(maxNode, neighbor);
            graph[node].push_back(neighbor);
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
    }

    int n = maxNode + 1;
    parent.resize(n);
    for(int i = 0; i < n; i++){
        parent[i] = i;
    }

    queue<int> q;
    unordered_set<int> programs;
    q.push(0);
    while(!q.empty()){
        int node = q.front();
        q.pop();
        programs.insert(node);
        for(int subNode : graph[node]){
            if(programs.find(subNode) == programs.end()){
                q.push(subNode);
            }
        }
    }

    for (const auto& entry : graph) {
        int node = entry.first;
        for (int neighbor : entry.second) {
            union_sets(node, neighbor);
        }
    }

    unordered_set<int> uniqueGroups;
    for (int i = 0; i < n; i++) {
        uniqueGroups.insert(find(i));
    }


    cout << "Part one answer: " << programs.size() << endl;
    cout << "Part two answer: " << uniqueGroups.size() << endl;
    return 0;
}