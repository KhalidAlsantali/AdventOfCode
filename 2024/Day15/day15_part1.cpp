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

pair<int, int> robot_pos;

void printMap(vector<vector<char>>& map){
    for(const auto& row : map){
        for(const auto& c : row){
            cout << c;
        }
        cout << endl;
    }
}

bool moveObject(vector<vector<char>>& map, pair<int, int> pos, pair<int, int> dir, char c){
    int new_i = pos.first + dir.first;
    int new_j = pos.second + dir.second;

    if(new_i < 0 || new_j < 0 || new_i >= map.size() || new_j >= map[0].size()){
        return false;
    }

    if(map[new_i][new_j] == '#'){
        return false;
    }
    if(map[new_i][new_j] == '.'){
        if(c == '@'){
            robot_pos = {new_i, new_j};
        }
        map[pos.first][pos.second] = '.';
        map[new_i][new_j] = c;
        return true;
    }
    if(map[new_i][new_j] == 'O'){
        if(moveObject(map, {new_i, new_j}, dir, 'O')){
            if(c == '@'){
                robot_pos = {new_i, new_j};
            }
            map[pos.first][pos.second] = '.';
            map[new_i][new_j] = c;
            return true;
        }
        return false;
    }
    return false;
    
}

int main(){
    string map_filename = "map.txt";
    ifstream mapFile(map_filename);
    vector<vector<char>> map;
    vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};


    string line;
    while (getline(mapFile, line)) {
        vector<char> row;
        for(char c : line){
            row.push_back(c);
        }
        map.push_back(row);
    }

    string moves_filename = "moves.txt";
    ifstream movesFile(moves_filename);
    string moves = "";

    while(getline(movesFile, line)){
        moves += line;
    }

    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].size(); j++){
            if(map[i][j] == '@'){
                robot_pos = {i, j};
            }
        }
    }


    for(char c : moves){
        if(c == '^'){
            moveObject(map, robot_pos, dirs[0], map[robot_pos.first][robot_pos.second]);
        }
        if(c == '>'){
            moveObject(map, robot_pos, dirs[1], map[robot_pos.first][robot_pos.second]);
        }
        if(c == 'v'){
            moveObject(map, robot_pos, dirs[2], map[robot_pos.first][robot_pos.second]);
        }
        if(c == '<'){
            moveObject(map, robot_pos, dirs[3], map[robot_pos.first][robot_pos.second]);
        }
        // printMap(map);
        // cout << endl << endl;
    }

    int sum = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map.size(); j++){
            if(map[i][j] == 'O'){
                sum += (i * 100) + j;
            }
        }
    }

    cout << sum << endl;

    

}
    
