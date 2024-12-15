
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

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

using namespace std;
pair<int, int> robot_pos;

void printMap(vector<vector<char>>& map){
    cout << "\033[2J\033[H";  // Clear screen and move cursor to top-left
    for(const auto& row : map){
        for(const auto& c : row){
            cout << c;
        }
        cout << endl;
    }
}

bool checkMoveHorizontal(vector<vector<char>>& map, int dir, pair<int, int> pos) {
    if(pos.second + dir < 0 || static_cast<size_t>(pos.second + dir) >= map[0].size()) {
        return false;
    }
   
    char next = map[pos.first][pos.second + dir];
    
    if(next == '#') {
        return false;
    }
    if(next == '.') {
        return true;
    }
    if(next == '[' || next == ']') {
        return checkMoveHorizontal(map, dir, {pos.first, pos.second + dir});
    }
    
    return false;
}

bool checkMoveVertical(vector<vector<char>>& map, int dir, pair<int, int> pos) {
    if(pos.first + dir < 0 || static_cast<size_t>(pos.first + dir) >= map.size()) {
        return false;
    }
   
    char next = map[pos.first + dir][pos.second];
    
    if(next == '#') {
        return false;
    }
    if(next == '.') {
        return true;
    }
    if(next == '[') {
        return checkMoveVertical(map, dir, {pos.first + dir, pos.second}) &&
               checkMoveVertical(map, dir, {pos.first + dir, pos.second + 1});
    }
    if(next == ']') {
        return checkMoveVertical(map, dir, {pos.first + dir, pos.second}) &&
               checkMoveVertical(map, dir, {pos.first + dir, pos.second - 1});
    }
    
    return false;
}

void moveObjectHorizontal(vector<vector<char>>& map, int dir, pair<int, int> pos) {
    char temp = map[pos.first][pos.second];
    
    if(map[pos.first][pos.second + dir] != '.') {
        moveObjectHorizontal(map, dir, {pos.first, pos.second + dir});
    }
    map[pos.first][pos.second + dir] = temp;
    map[pos.first][pos.second] = '.';
}

void moveObjectVertical(vector<vector<char>>& map, int dir, pair<int, int> pos) {
    char temp = map[pos.first][pos.second];
    
    if(map[pos.first + dir][pos.second] == '[') {
        moveObjectVertical(map, dir, {pos.first + dir, pos.second});
        moveObjectVertical(map, dir, {pos.first + dir, pos.second + 1});
    }
    else if(map[pos.first + dir][pos.second] == ']') {
        moveObjectVertical(map, dir, {pos.first + dir, pos.second});
        moveObjectVertical(map, dir, {pos.first + dir, pos.second - 1});
    }
    
    map[pos.first + dir][pos.second] = temp;
    map[pos.first][pos.second] = '.';
}

bool moveObject(vector<vector<char>>& map, pair<int, int> pos, pair<int, int> dir, char c) {
    if(dir.first == 0) {
        if(checkMoveHorizontal(map, dir.second, pos)) {
            moveObjectHorizontal(map, dir.second, pos);
            if(c == '@') {
                robot_pos = {pos.first, pos.second + dir.second};
            }
            return true;
        }
    }
    else {
        if(checkMoveVertical(map, dir.first, pos)) {
            moveObjectVertical(map, dir.first, pos);
            if(c == '@') {
                robot_pos = {pos.first + dir.first, pos.second};
            }
            return true;
        }
    }
    
    return false;
}

#ifdef _WIN32
// Windows implementation
char getCharacter() {
    if (_kbhit()) {
        return _getch();
    }
    return 0;
}
#else
// Unix implementation
char getCharacter() {
    struct termios oldSettings, newSettings;
    char ch = 0;

    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;

    newSettings.c_lflag &= ~(ICANON | ECHO);
    newSettings.c_cc[VMIN] = 0;
    newSettings.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);

    return ch;
}
#endif

int main() {
    string map_filename = "map.txt";
    ifstream mapFile(map_filename);
    if (!mapFile.is_open()) {
        cerr << "Error: Could not open map.txt" << endl;
        return 1;
    }

    vector<vector<char>> map;
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

    // Find initial robot position
    for(int i = 0; static_cast<size_t>(i) < map.size(); i++){
        for(int j = 0; static_cast<size_t>(j) < map[0].size(); j++){
            if(map[i][j] == '@'){
                robot_pos = {i, j};
            }
        }
    }

    cout << "Controls: WASD to move, Q to quit" << endl;
    printMap(map);

    while(true) {
        char direction = getCharacter();
        
        if(direction != 0) {
            if(direction == 'w') {
                moveObject(map, robot_pos, dirs[0], map[robot_pos.first][robot_pos.second]);
            }
            else if(direction == 'd') {
                moveObject(map, robot_pos, dirs[1], map[robot_pos.first][robot_pos.second]);
            }
            else if(direction == 's') {
                moveObject(map, robot_pos, dirs[2], map[robot_pos.first][robot_pos.second]);
            }
            else if(direction == 'a') {
                moveObject(map, robot_pos, dirs[3], map[robot_pos.first][robot_pos.second]);
            }
            else if(direction == 'q') {
                break;
            }
            printMap(map);
        }
        
        // Prevent CPU hogging
        #ifdef _WIN32
            Sleep(50);
        #else
            usleep(50000);
        #endif
    }

    // Calculate final score
    int sum = 0;
    for(int i = 0; static_cast<size_t>(i) < map.size(); i++){
        for(int j = 0; static_cast<size_t>(j) < map[0].size(); j++){
            if(map[i][j] == '['){
                sum += (i * 100) + j;
            }
        }
    }

    cout << "Final score: " << sum << endl;
    return 0;
}