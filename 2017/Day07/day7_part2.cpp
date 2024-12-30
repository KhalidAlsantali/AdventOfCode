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


int lastUnbalancedWeight = 0;


int calculateTotalWeight(const string& node, 
                        const unordered_map<string, vector<string>>& graph,
                        const unordered_map<string, int>& values);

string findOddOneOut(const vector<string>& children,
                    const unordered_map<string, int>& totalWeights) {
    if (children.size() < 2) return "";
    

    unordered_map<int, int> weightCount;
    for (const auto& child : children) {
        weightCount[totalWeights.at(child)]++;
    }
    

    for (const auto& child : children) {
        if (weightCount[totalWeights.at(child)] == 1) {
            return child;
        }
    }
    
    return "";
}

int calculateTotalWeight(const string& node, 
                        const unordered_map<string, vector<string>>& graph,
                        const unordered_map<string, int>& values) {
    int total = values.at(node);
    auto it = graph.find(node);
    if (it != graph.end()) {
        for (const auto& child : it->second) {
            total += calculateTotalWeight(child, graph, values);
        }
    }
    return total;
}

void findUnbalancedNode(const unordered_map<string, vector<string>>& graph,
                       const unordered_map<string, int>& values,
                       const string& root,
                       const unordered_map<string, int>& totalWeights) {
    auto it = graph.find(root);
    if (it == graph.end()) return;
    
    const vector<string>& children = it->second;
    string oddTower = findOddOneOut(children, totalWeights);
    
    if (oddTower.empty()) return;
    

    int expectedWeight = -1;
    int actualWeight = totalWeights.at(oddTower);
    
    for (const auto& sibling : children) {
        if (sibling != oddTower) {
            expectedWeight = totalWeights.at(sibling);
            break;
        }
    }
    

    int weightDiff = expectedWeight - actualWeight;
    int currentNodeWeight = values.at(oddTower);
    

    lastUnbalancedWeight = currentNodeWeight + weightDiff;
    

    findUnbalancedNode(graph, values, oddTower, totalWeights);
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    
    unordered_set<string> first;
    unordered_set<string> connected;
    unordered_map<string, vector<string>> graph;
    unordered_map<string, int> values;

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string nodeName;
        ss >> nodeName;
        first.insert(nodeName);
        
        if (line.find("->") != string::npos) {
            size_t pos = line.find("->");
            string rest = line.substr(pos + 2);
            stringstream ssRest(rest);
            string child;
            while (ssRest >> child) {
                if (child.back() == ',') {
                    child.pop_back();
                }
                connected.insert(child);
                graph[nodeName].push_back(child);
            }
        }
    }
    
    inputFile.clear();
    inputFile.seekg(0);
    while(getline(inputFile, line)) {
        stringstream ss(line);
        string nodeName;
        ss >> nodeName;
        
        regex weightPattern("\\d+");
        smatch match;
        if (regex_search(line, match, weightPattern)) {
            values[nodeName] = stoi(match.str());
        }
    }

    string root;
    for (const auto& elem : first) {
        if (connected.find(elem) == connected.end()) {
            root = elem;
            break;
        }
    }

    cout << "Part one answer: " << root << endl;
    
    unordered_map<string, int> totalWeights;
    for (const auto& node : first) {
        totalWeights[node] = calculateTotalWeight(node, graph, values);
    }
    
    findUnbalancedNode(graph, values, root, totalWeights);
    
    cout << "Part two answer: " << lastUnbalancedWeight << endl;
    return 0;
}