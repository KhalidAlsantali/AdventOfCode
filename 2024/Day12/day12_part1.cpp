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


int main(){
    string input_filename = "example.txt";
    ifstream inputFile(input_filename);
    vector<vector<char>> map;
    unordered_map<int, region> mapped;
    vector<pair<int, int>> dirs = {{1,0}, {-1, 0}, {0, 1}, {0, -1}};

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
    for (const auto& entry : mapped) {
        sum += entry.second.area * entry.second.perimeter;
    }

    cout << "Part one answer: " << sum << endl;
    
}