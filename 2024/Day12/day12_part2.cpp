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
            pair<int, int> up = make_pair(coord.first - 1, coord.second);
            pair<int, int> down = make_pair(coord.first + 1, coord.second);
            pair<int, int> right = make_pair(coord.first, coord.second + 1);
            pair<int, int> left = make_pair(coord.first, coord.second - 1);
            pair<int, int> upleft = make_pair(coord.first - 1, coord.second - 1);
            pair<int, int> upright = make_pair(coord.first - 1, coord.second + 1);
            pair<int, int> downleft = make_pair(coord.first + 1, coord.second - 1);
            pair<int, int> downright = make_pair(coord.first + 1, coord.second + 1);

            if(map[coord.first][coord.second] != getPlant(map, up.first, up.second) && map[coord.first][coord.second] != getPlant(map, left.first, left.second)){
                entry.second.corners++;
            }

            if(map[coord.first][coord.second] == getPlant(map, up.first, up.second) && map[coord.first][coord.second] == getPlant(map, left.first, left.second) && map[coord.first][coord.second] != getPlant(map, upleft.first, upleft.second)){
                entry.second.corners++;
            }

            if (map[coord.first][coord.second] != getPlant(map, up.first, up.second) && map[coord.first][coord.second] != map[right.first][right.second]) {
                entry.second.corners++;
            }

            if (map[coord.first][coord.second] == getPlant(map, up.first, up.second) && map[coord.first][coord.second] == map[right.first][right.second] && map[coord.first][coord.second] != getPlant(map, upright.first, upright.second)) {
                entry.second.corners++;
            }

            if (map[coord.first][coord.second] != getPlant(map, down.first, down.second) && map[coord.first][coord.second] != getPlant(map, left.first, left.second)) {
                entry.second.corners++;
            }

            if (map[coord.first][coord.second] == getPlant(map, down.first, down.second) && map[coord.first][coord.second] == getPlant(map, left.first, left.second) && map[coord.first][coord.second] != getPlant(map, downleft.first, downleft.second)) {
                entry.second.corners++;
            }

            if (map[coord.first][coord.second] != getPlant(map, down.first, down.second) && map[coord.first][coord.second] != map[right.first][right.second]) {
                entry.second.corners++;
            }

            if (map[coord.first][coord.second] == getPlant(map, down.first, down.second) && map[coord.first][coord.second] == map[right.first][right.second] && map[coord.first][coord.second] != getPlant(map, downright.first, downright.second)) {
                entry.second.corners++;
            }
        }
    }

    for (const auto& entry : mapped) {
        sum += entry.second.area * entry.second.corners;
    }



    cout << "Part two answer: " << sum << endl;
    
}