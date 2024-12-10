#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <cctype>
#include <set>
#include <utility>

using namespace std;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

vector<pair<int, int>> getStartingPoints(vector<vector<int>>& map){
    vector<pair<int, int>> zeros;
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if(map[i][j] == 0){
                zeros.push_back({i, j});
            }
        }
    }
    return zeros;
}

set<pair<int, int>> isClimbable(vector<vector<int>>& map, pair<int, int> startingPoint, set<pair<int, int>>& visited) {
    set<pair<int, int>> results;

    // Boundary checks
    if (startingPoint.first < 0 || static_cast<size_t>(startingPoint.first) >= map.size() || 
        startingPoint.second < 0 || static_cast<size_t>(startingPoint.second) >= map[0].size() || 
        visited.count(startingPoint)) {
        return results;
    }

    visited.insert(startingPoint);

    // If we've reached the goal
    if (map[startingPoint.first][startingPoint.second] == 9) {
        // cout << startingPoint.first << " " << startingPoint.second << " SUCCESS" << endl;
        results.insert(startingPoint);
        return results;
    }

    int current = map[startingPoint.first][startingPoint.second];

    // Define movement directions
    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    for (auto& dir : directions) {
        int newRow = startingPoint.first + dir.first;
        int newCol = startingPoint.second + dir.second;

        // Check boundaries and climbable condition
        if (newRow >= 0 && static_cast<size_t>(newRow) < map.size() && 
            newCol >= 0 && static_cast<size_t>(newCol) < map[0].size() && 
            map[newRow][newCol] == current + 1) {
            // cout << startingPoint.first << " " << startingPoint.second << " Looking (" << dir.first << ", " << dir.second << ")" << endl;

            // Combine results from recursive calls
            auto branchResults = isClimbable(map, {newRow, newCol}, visited);
            results.insert(branchResults.begin(), branchResults.end());
        }
    }

    if (results.empty()) {
        // cout << startingPoint.first << " " << startingPoint.second << " FAIL" << endl;
    }

    return results;
}


int main(){
    string input_filename = "input.txt";
    ifstream inputFile(input_filename);
    vector<vector<int>> map;

    string line;
    while (getline(inputFile, line)) {
        vector<int> row;
        for(char c : line){
            row.push_back(c - '0');
        }
        map.push_back(row);
    }
    // cout << "Map:" << endl;
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            // cout << map[i][j];
        }
        // cout << endl;
    }
    
    unordered_map<pair<int, int>, set<pair<int, int>>, pair_hash> trail_startends;
    vector<pair<int, int>> startingPoints = getStartingPoints(map);
    for(auto start : startingPoints){
        set<pair<int, int>> visited; // Reset visited for each starting point
        // cout << start.first << " " << start.second << endl;
        set<pair<int, int>> results  = isClimbable(map, start, visited);
        for (const auto& endpoint : results) {
            trail_startends[start].insert(endpoint);
        }
    }
    

    int total_trail_connections = 0;
    for (const auto& [key, trail_set] : trail_startends) {
        total_trail_connections += trail_set.size();
    }

    cout << "Part one answer: " << total_trail_connections;
    return 0;
}
