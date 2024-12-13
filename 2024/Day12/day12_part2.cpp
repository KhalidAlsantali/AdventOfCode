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

char getPlant(vector<vector<char>>& map, int i, int j){
    if(i >= 0 && j >= 0 && static_cast<size_t>(i) < map.size() && static_cast<size_t>(j) < map[0].size()){
        return map[i][j];
    }
    return -1;
}

int main(){
    string input_filename = "input.txt";
    ifstream inputFile(input_filename);
    vector<vector<char>> map;
    unordered_map<int, region> mapped;
    vector<pair<int, int>> dirs = {{1,0}, {-1, 0}, {0, 1}, {0, -1}};
    const int offsets[4][3][2] = {
        {{-1, 0}, {0, -1}, {-1, -1}},
        {{-1, 0}, {0, 1}, {-1, 1}},
        {{1, 0}, {0, -1}, {1, -1}},
        {{1, 0}, {0, 1}, {1, 1}}
    };
    

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

                        if(ni >= 0 && nj >= 0 && static_cast<size_t>(ni) < map.size() && static_cast<size_t>(nj) < map[0].size()){
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
    for (auto& entry : mapped) {
        for(pair<int, int> coord : entry.second.coords){
            for (const auto& corner : offsets) {
                int dx1 = corner[0][0], dy1 = corner[0][1];
                int dx2 = corner[1][0], dy2 = corner[1][1];
                int dx3 = corner[2][0], dy3 = corner[2][1];

                if (map[coord.first][coord.second] != getPlant(map, coord.first + dx1, coord.second + dy1) && 
                    map[coord.first][coord.second] != getPlant(map, coord.first + dx2, coord.second + dy2))
                    entry.second.corners++;

                if (map[coord.first][coord.second] == getPlant(map, coord.first + dx1, coord.second + dy1) && 
                    map[coord.first][coord.second] == getPlant(map, coord.first + dx2, coord.second + dy2) && 
                    map[coord.first][coord.second] != getPlant(map, coord.first + dx3, coord.second + dy3))
                    entry.second.corners++;
            }
        }
    }

    for (const auto& entry : mapped) {
        sum += entry.second.area * entry.second.corners;
    }

    cout << "Part two answer: " << sum << endl;
    
}