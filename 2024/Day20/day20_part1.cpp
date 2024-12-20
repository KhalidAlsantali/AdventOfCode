#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

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
        for(const pair<int, int>& dir : directions) {
            int newRow = step.first + dir.first;
            int newCol = step.second + dir.second;
            if(newRow >= 0 && static_cast<size_t>(newRow) < map.size() && newCol >= 0 && static_cast<size_t>(newCol) < map[0].size() && map[newRow][newCol] == '#') {
                int skipRow = newRow + dir.first;
                int skipCol = newCol + dir.second;
                if(skipRow >= 0 && static_cast<size_t>(skipRow) < map.size() && skipCol >= 0 && static_cast<size_t>(skipCol) < map[0].size()) {
                    auto skip = find(path.begin(), path.end(), make_pair(skipRow, skipCol));
                    if(skip != path.end()) {
                        auto step_it = find(path.begin(), path.end(), step);
                        int dist = distance(step_it, skip);
                        if(dist > 0) {
                            cheats[make_pair(step, make_pair(skip->first, skip->second))] = dist - 2;
                        }
                    }
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

    cout << "Part one answer: " << sum << endl;
    return 0;
}