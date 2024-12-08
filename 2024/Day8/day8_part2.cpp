#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <cctype>
#include <set>


using namespace std;

bool inBounds(const pair<int, int>& point, const vector<vector<char>>& map) {
    return point.first >= 0 && static_cast<size_t>(point.first) < map.size() &&
           point.second >= 0 && static_cast<size_t>(point.second) < map[0].size();
}

pair<int, int> calculateDifference(pair<int, int> first_antenna, pair<int, int> second_antenna){
    int i_diff = second_antenna.first - first_antenna.first;
    int j_diff = second_antenna.second - first_antenna.second;
    return {i_diff, j_diff};
}

vector<pair<int, int>> getAntinodes(pair<int, int> first_antenna, pair<int, int> second_antenna, pair<int, int> diff, vector<vector<char>>& map) {
    vector<pair<int, int>> antinodes;
    pair<int, int> points[3] = {first_antenna, second_antenna, first_antenna};
    
    while(true){
        points[0] = {(diff.first * -1) + points[0].first, (diff.second * -1) + points[0].second};
        points[1] = {diff.first + points[1].first, diff.second + points[1].second};
        points[2] = {diff.first + points[2].first, diff.second + points[2].second};
        
        bool allOutOfBounds = true;
        for(const auto& point : points){
            if (inBounds(point, map)){
                antinodes.push_back(point);
                allOutOfBounds = false;
            }
        }
        
        if(allOutOfBounds){
            break;
        }
    }

    return antinodes;
}

int main(){
    string input_filename = "input.txt";
    ifstream inputFile(input_filename);
    vector<vector<char>> map;
    unordered_map<char, vector<pair<int, int>>> antennas;

    string line;
    while (getline(inputFile, line)) {
        vector<char> row(line.begin(), line.end());
        map.push_back(row);
    }

    for(size_t i = 0; i < map.size(); ++i){
        for(size_t j = 0; j < map[i].size(); ++j){
            if(isalnum(map[i][j])){
                antennas[map[i][j]].push_back({i, j});
            }
        }
    }

    set<pair<int, int>> all_antinodes;
    for(const auto& [antenna, positions] : antennas){
        for(size_t i = 0; i < positions.size(); ++i){
            for(size_t j = 0; j < positions.size(); ++j){
                if(positions[i] == positions[j]){
                    continue;
                }
                pair<int, int> diff = calculateDifference(positions[i], positions[j]);
                vector<pair<int, int>> antinodes = getAntinodes(positions[i], positions[j], diff, map);
                if(!antinodes.empty()){
                    all_antinodes.insert(antinodes.begin(), antinodes.end());
                }
            }
        }
    }
    
    cout << "Part two answer: " << all_antinodes.size();
    return 0;
}