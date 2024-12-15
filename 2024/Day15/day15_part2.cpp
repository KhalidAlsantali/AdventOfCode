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
    cout << endl << endl;
    for(const auto& row : map){
        for(const auto& c : row){
            cout << c;
        }
        cout << endl;
    }
}

bool checkMoveHorizontal(vector<vector<char>>& map, int dir, int r, int c) {
    if(c + dir < 0 || c + dir >= map[0].size()) return false;
    
    char next = map[r][c + dir];
    switch(next) {
        case '#': return false;
        case '.': return true;
        case '[':
        case ']': return checkMoveHorizontal(map, dir, r, c + dir);
    }
    return false;
}

bool checkMoveVertical(vector<vector<char>>& map, int dir, int r, int c) {
    if(r + dir < 0 || r + dir >= map.size()) return false;
    
    char next = map[r + dir][c];
    switch(next) {
        case '#': return false;
        case '.': return true;
        case '[': return checkMoveVertical(map, dir, r + dir, c) && 
                        checkMoveVertical(map, dir, r + dir, c + 1);
        case ']': return checkMoveVertical(map, dir, r + dir, c) && 
                        checkMoveVertical(map, dir, r + dir, c - 1);
    }
    return false;
}

void moveObjectHorizontal(vector<vector<char>>& map, int dir, int r, int c) {
    char temp = map[r][c];
    
    if(map[r][c + dir] != '.') {
        moveObjectHorizontal(map, dir, r, c + dir);
    }
    map[r][c + dir] = temp;
    map[r][c] = '.';
}

void moveObjectVertical(vector<vector<char>>& map, int dir, int r, int c) {
    char temp = map[r][c];
    
    if(map[r + dir][c] == '[') {
        moveObjectVertical(map, dir, r + dir, c);
        moveObjectVertical(map, dir, r + dir, c + 1);
    }
    else if(map[r + dir][c] == ']') {
        moveObjectVertical(map, dir, r + dir, c);
        moveObjectVertical(map, dir, r + dir, c - 1);
    }
    
    map[r + dir][c] = temp;
    map[r][c] = '.';
}

bool moveObject(vector<vector<char>>& map, pair<int, int> pos, pair<int, int> dir, char c) {
    
    if(dir.first == 0) {
        if(checkMoveHorizontal(map, dir.second, pos.first, pos.second)) {
            moveObjectHorizontal(map, dir.second, pos.first, pos.second);
            if(c == '@') {
                robot_pos = {pos.first, pos.second + dir.second};
            }
            return true;
        }
    }

    else {
        if(checkMoveVertical(map, dir.first, pos.first, pos.second)) {
            moveObjectVertical(map, dir.first, pos.first, pos.second);
            if(c == '@') {
                robot_pos = {pos.first + dir.first, pos.second};
            }
            return true;
        }
    }
    
    return false;
}

int main(){
    string map_filename = "map.txt";
    ifstream mapFile(map_filename);
    vector<vector<char>> map; //      UP     RIGHT   DOWN     LEFT
    vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    string line;
    while (getline(mapFile, line)) {
        vector<char> row;
        for(char c : line){
            if(c == '#'){
                row.push_back('#');
                row.push_back('#');
            }
            if(c == 'O'){
                row.push_back('[');
                row.push_back(']');
            }
            if(c == '.'){
                row.push_back('.');
                row.push_back('.');
            }
            if(c == '@'){
                row.push_back('@');
                row.push_back('.');
            }
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
        bool moved = false;
        if(c == '^'){
            moved = moveObject(map, robot_pos, dirs[0], map[robot_pos.first][robot_pos.second]);
        }
        if(c == '>'){
            moved = moveObject(map, robot_pos, dirs[1], map[robot_pos.first][robot_pos.second]);
        }
        if(c == 'v'){
            moved = moveObject(map, robot_pos, dirs[2], map[robot_pos.first][robot_pos.second]);
        }
        if(c == '<'){
            moved = moveObject(map, robot_pos, dirs[3], map[robot_pos.first][robot_pos.second]);
        }
    
        for(int i = 0; i < map.size(); i++){
            for(int j = 0; j < map[0].size(); j++){
                if(map[i][j] == '@'){
                    robot_pos = {i, j};
                    break;
                }
            }
        }
    }

    int sum = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].size(); j++){
            if(map[i][j] == '['){
                sum += (i * 100) + j;
            }
        }
    }
    cout << sum << endl;
   
}