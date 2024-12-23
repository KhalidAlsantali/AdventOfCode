#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

void BronKerbosch(set<string>&& R, set<string>&& P, set<string>&& X, unordered_map<string, set<string>>& adj, vector<set<string>>& cliques){
    if(P.empty() && X.empty()){
        cliques.push_back(R);
        return;
    }
    while(!P.empty()){
        string v = *P.begin();
        set<string> newR = R;
        newR.insert(v);
        set<string> newP;
        for(string p : P){
            if(adj[v].find(p) != adj[v].end()){
                newP.insert(p);
            }
        }
        set<string> newX;
        for(string x : X){
            if(adj[v].find(x) != adj[v].end()){
                newX.insert(x);
            }
        }
        BronKerbosch(move(newR), move(newP), move(newX), adj, cliques);
        P.erase(v);
        X.insert(v);
    }
}


int main() {
    ifstream inputFile("input.txt");
    vector<pair<string, string>> connections;
    unordered_map<string, set<string>> adj;
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
        adj[connection.first].insert(connection.second);
        adj[connection.second].insert(connection.first);
    }

    set<string> allVertices;
    for(const auto& pair : adj){
        allVertices.insert(pair.first);
    }

    vector<set<string>> allCliques;
    BronKerbosch({}, move(allVertices), {}, adj, allCliques);

    size_t maxCliqueSize = 0;
    set<string> maxClique;
    for (const auto& clique : allCliques) {
        if(clique.size() > maxCliqueSize){
            maxCliqueSize = clique.size();
            maxClique = clique;
        }
    }


    
    cout << "Part two answer: ";
    for (auto it = maxClique.begin(); it != maxClique.end(); ++it) {
        if (it != maxClique.begin()) {
            cout << ",";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}