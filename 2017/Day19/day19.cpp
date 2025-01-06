#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

enum Direction {
    DOWN = 0,
    RIGHT = 1,
    UP = 2,
    LEFT = 3
};

pair<int, int> dirToCoord(Direction dir) {
    switch(dir) {
        case DOWN: return {1, 0};
        case RIGHT: return {0, 1};
        case UP: return {-1, 0};
        case LEFT: return {0, -1};
        default: return {0, 0};
    }
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    
    vector<vector<char>> map;
    string line;
   
    while (getline(inputFile, line)) {
        vector<char> row(line.begin(), line.end());
        map.push_back(row);
    }
    
    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    vector<char> letters;
    
    pair<int, int> current;
    for(int i = 0; i < map[0].size(); i++){
        if(map[0][i] == '|'){
            current = {0, i};
            break;
        }
    }
    
    Direction currentDir = DOWN;
    int steps = 1;
    while(true) {
        if (!visited[current.first][current.second]) {
            visited[current.first][current.second] = true;
            if(isalpha(map[current.first][current.second])) {
                letters.push_back(map[current.first][current.second]);
            }
        }
        
        char currentChar = map[current.first][current.second];
        pair<int, int> dirCoord = dirToCoord(currentDir);
        int newRow = current.first + dirCoord.first;
        int newCol = current.second + dirCoord.second;
        
        if(currentChar == '+') {
            bool foundTurn = false;
            for(Direction newDir : {Direction((currentDir + 1) % 4), Direction((currentDir + 3) % 4)}) {
                dirCoord = dirToCoord(newDir);
                int turnRow = current.first + dirCoord.first;
                int turnCol = current.second + dirCoord.second;
                
                if(turnRow >= 0 && turnRow < map.size() &&
                   turnCol >= 0 && turnCol < map[0].size() &&
                   map[turnRow][turnCol] != ' ') {
                    currentDir = newDir;
                    newRow = turnRow;
                    newCol = turnCol;
                    foundTurn = true;
                    break;
                }
            }
            if(!foundTurn) break;
        }
        else if(newRow < 0 || newRow >= map.size() ||
                newCol < 0 || newCol >= map[0].size() ||
                map[newRow][newCol] == ' ') {
            break;
        }
        
        current = {newRow, newCol};
        steps++;
    }
    
    cout << "Part one answer: ";
    for(char letter : letters) {
        cout << letter;
    }
    cout << endl;
    cout << "Part two answer: " << steps << endl;
    return 0;
}