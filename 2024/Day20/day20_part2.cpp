#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<pair<int, int>> getPossibleEnds(pair<int, int> start, const vector<vector<char>>& map) {
    int distance = 20;
    vector<pair<int, int>> points;
    for (int dx = -distance; dx <= distance; dx++) {
        for (int dy = -distance; dy <= distance; dy++) {
            if (abs(dx) + abs(dy) <= distance) {
                int newX = start.first + dx;
                int newY = start.second + dy;
                
                if (newX >= 0 && static_cast<size_t>(newX) < map.size() && 
                    newY >= 0 && static_cast<size_t>(newY) < map[0].size()) {
                    if (map[newX][newY] == '.' || map[newX][newY] == 'E') {
                        points.push_back({newX, newY});
                    }
                }
            }
        }
    }
    
    return points;
}

int manhattanDistance(pair<int, int> p1, pair<int, int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
    
    std::size_t operator () (const std::pair<std::pair<int, int>, std::pair<int, int>>& p) const {
        auto h1 = pair_hash{}(p.first);
        auto h2 = pair_hash{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file";
        return 1;
    }

    vector<vector<char>> map;
    unordered_map<pair<pair<int, int>, pair<int, int>>, int, pair_hash> cheats;
    vector<pair<int, int>> path;
    pair<int, int> start;
    pair<int, int> end;
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    string line;

    while (getline(inputFile, line)) {
        vector<char> row(line.begin(), line.end());
        map.push_back(row);
    }

    inputFile.close();

    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            if(map[i][j] == 'S') {
                start = make_pair(i, j);
            }
            if(map[i][j] == 'E') {
                end = make_pair(i, j);
            }
        }
    }

    pair<int, int> current = start;
    pair<int, int> previous;
    while(current != end){
        for(const pair<int, int>& dir : directions){
            if(map[current.first + dir.first][current.second + dir.second] == '.' && make_pair(current.first + dir.first, current.second + dir.second) != previous){
                previous = current;
                path.push_back(current);
                current = make_pair(current.first + dir.first, current.second + dir.second);
            }
            if(map[current.first + dir.first][current.second + dir.second] == 'E'){
                path.push_back(current);
                path.push_back(make_pair(current.first + dir.first, current.second + dir.second));
                current = end;
                break;
            }
        }
    }

    for(const pair<int, int>& step : path) {
        vector<pair<int, int>> points = getPossibleEnds(step, map);
        for(const pair<int, int>& end : points){
            auto skip = find(path.begin(), path.end(), end);
            if(skip != path.end()){
                auto step_it = find(path.begin(), path.end(), step);
                int dist = distance(step_it, skip);
                if(dist > 0){
                    cheats[make_pair(step, make_pair(skip->first, skip->second))] = dist - manhattanDistance(step, end);
                }
            }
        }
    }

    unordered_map<int, vector<pair<pair<int, int>, pair<int, int>>>> groupedCheats;
    for (const auto& cheat : cheats) {
        groupedCheats[cheat.second].push_back(cheat.first);
    }
    int sum = 0;
    for (const auto& group : groupedCheats) {
        if(group.first >= 100){
            sum += group.second.size();
        }
    }

    cout << "Part two answer: " << sum << endl;
    return 0;
}