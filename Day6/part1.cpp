#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::milliseconds


using namespace std;

int main(){
    string filename = "input.txt";
    ifstream inputFile(filename);
    vector<vector<char>> map;

    if(!inputFile.is_open()){
        cerr << "Error: Couldn't open file" << filename << endl;
        return 1;
    }
    string line;

    while (getline(inputFile, line)) {
        vector<char> row;
        for(char c : line){
            row.push_back(c);
        }
        map.push_back(row);
    }
    inputFile.close();
    // for (const auto& line : map) {
    //     for (char c : line) {
    //         std::cout << c << " ";
    //     }
    //     std::cout << std::endl;
    // }

    enum Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    int directionVector[4][2] = {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}
    };
    
    Direction guard_facing = UP;
    int guard_i, guard_j;
    bool guard_found = false;

    for(int i = 0; i < map.size(); ++i){
        for(int j = 0; j < map[i].size(); ++j){
            auto guard_location = find(map[i].begin(), map[i].end(), '^');
            if(guard_location != map[i].end()){
                guard_i = i;
                guard_j = distance(map[i].begin(), guard_location);
                guard_found = true;
                break;
            }
        }
        if(guard_found){
            break;
        }
    }

    while(true){
        map[guard_i][guard_j] = 'X';

        int next_i = guard_i + directionVector[guard_facing][0];
        int next_j = guard_j + directionVector[guard_facing][1];

        cout << next_i << ", " << next_j << endl; 

        if (next_i < 0 || next_j < 0 || next_i >= map.size() || next_j >= map[0].size()) {
            break;
        }

        if(map[guard_i + directionVector[guard_facing][0]][guard_j + directionVector[guard_facing][1]] == '#'){
            guard_facing = static_cast<Direction>((guard_facing + 1) % 4);
        } else {
            guard_i += directionVector[guard_facing][0];
            guard_j += directionVector[guard_facing][1];
        }

        // std::this_thread::sleep_for(std::chrono::seconds(1));
        // for (const auto& line : map) {
        //     for (char c : line) {
        //         std::cout << c << " ";
        //     }
        //     std::cout << std::endl;
        // }
        // cout << endl << endl << endl << endl;
    }

    int x_count = 0;
    for (int i = 0; i < map.size(); ++i) {
        x_count += count(map[i].begin(), map[i].end(), 'X');
    }

    // Debug: Print final state of the map
    // cout << "Final map:" << endl;
    // for (const auto& row : map) {
    //     for (char c : row) {
    //         cout << c;
    //     }
    //     cout << endl;
    // }

    cout << "Part one answer: " << x_count << endl;
    return 0;
}