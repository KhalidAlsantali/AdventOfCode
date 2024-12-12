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
#include <stack>

using namespace std;

struct region {
    vector<pair<int, int>> coords;
    int area = 0;
    int perimeter = 0;
    int corners = 0;
};

bool visited(int i, int j, unordered_map<int, region>& map){
    for(const auto& entry : map){
        auto it = find(entry.second.coords.begin(), entry.second.coords.end(), make_pair(i, j));
        if(it != entry.second.coords.end()){
            return true;
        }
    }
    return false;
}

int getRegionKeyFromCoordinate(int x, int y, unordered_map<int, region>& mapped) {
    // Iterate through the unordered map
    for (const auto& entry : mapped) {
        const region& r = entry.second;
        // Iterate through the coordinates in the region
        for (const auto& coord : r.coords) {
            if (coord.first == x && coord.second == y) {
                // If the coordinate matches, return the corresponding key
                return entry.first;
            }
        }
    }
    // Return -1 or another indication if the coordinate is not found
    return -1;
}


int main(){
    string input_filename = "example.txt";
    ifstream inputFile(input_filename);
    vector<vector<char>> map;
    unordered_map<int, region> mapped;
    vector<pair<int, int>> dirs = {{1,0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<pair<int, int>> vert_dirs = {{1,0}, {-1, 0}};
    vector<pair<int, int>> hor_dirs = {{0, 1}, {0, -1}};
    

    string line, number;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        vector<char> row;
        char c;
        while (iss >> c) {
            row.push_back(c);
        }
        map.push_back(row);
    }

    // for (size_t i = 0; i < map.size(); i++){
    //     for (size_t j = 0; j < map[i].size(); j++){
    //         cout << map[i][j];
    //     }
    //     cout << endl;
    // }
    vector<vector<bool>> visited_map(map.size(), vector<bool>(map[0].size(), false));
    int region_id = 1;
    for (size_t i = 0; i < map.size(); i++){
        for (size_t j = 0; j < map[i].size(); j++){
            if(visited_map[i][j]){
                continue;
            } else {
                stack<pair<int, int>> stack;
                stack.push(make_pair(i, j));
                visited_map[i][j] = true;
                mapped[region_id].coords.push_back(make_pair(i, j));
                mapped[region_id].area++;

                while(!stack.empty()){
                    pair<int, int> current = stack.top();
                    stack.pop();

                    set<char> neighbour_types;

                    for(pair<int, int> dir : dirs){
                        int ni = current.first + dir.first;
                        int nj = current.second + dir.second;

                        if(ni >= 0 && nj >= 0 && ni < map.size() && nj < map[0].size()){
                            if(map[i][j] == map[ni][nj] && !visited_map[ni][nj]){
                                stack.push(make_pair(ni, nj));
                                visited_map[ni][nj] = true;
                                mapped[region_id].coords.push_back(make_pair(ni, nj));
                                mapped[region_id].area++;
                            } else if(map[i][j] != map[ni][nj]) {
                                mapped[region_id].perimeter++;
                            }
                        } else {
                            mapped[region_id].perimeter++;
                        }
                    }
                }
                region_id++;
            }
        }
    }
    int sum = 0;
    for (const auto& entry : mapped) {
        // set<pair<int, char>> edges;
        set<tuple<int, char, int>> edges;
        for(pair<int, int> coord : entry.second.coords){
            // i loop
            for(auto dir : vert_dirs){
                int ni = coord.first + dir.first;
                int nj = coord.second + dir.second;
                // cout << ni << ":" << nj << endl;
                if(ni < 0 || nj < 0 || ni > map.size() - 1 || nj > map[0].size() - 1 || map[coord.first][coord.second] != map[ni][nj]){
                    edges.insert(make_tuple(coord.first, ni - coord.first == 1 ? 'U' : 'D', getRegionKeyFromCoordinate(ni, nj, mapped)));
                }
            }
            // j loop
            for(auto dir : hor_dirs){
                int ni = coord.first + dir.first;
                int nj = coord.second + dir.second;
                if(ni < 0 || nj < 0 || ni > map.size() - 1 || nj > map[0].size() - 1 || map[coord.first][coord.second] != map[ni][nj]){
                    cout << coord.first << ":" << coord.second << "|||" << ni << ":" << nj << endl;
                    edges.insert(make_tuple(coord.second, nj - coord.second == 1 ? 'L' : 'R', getRegionKeyFromCoordinate(ni, nj, mapped)));
                }
            }
        }
        // for (const auto& edge : edges) {
        //     cout << "(" << edge.first << ", " << edge.second << ")" << endl;
        // }

        cout << endl << endl << endl;
        mapped[entry.first].corners = edges.size();
    }

    for (const auto& entry : mapped) {
        cout << "Key: " << entry.first << endl;
        cout << "Area: " << entry.second.area << endl;
        cout << "Perimeter: " << entry.second.perimeter << endl;
        cout << "Corners: " << entry.second.corners << endl;
        cout << "Coordinates: ";
        for (const auto& coord : entry.second.coords) {
            cout << "(" << coord.first << ", " << coord.second << ") ";
        }
        cout << endl << endl;
        sum += entry.second.area * entry.second.corners;
    }



    cout << "Part one answer: " << sum << endl;
    
}