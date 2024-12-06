#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::milliseconds
#include <set>


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

    struct State {
        int x, y;
        char direction;
        
        // Need to define comparison operators for set to work
        bool operator<(const State& other) const {
            return std::tie(x, y, direction) < std::tie(other.x, other.y, other.direction);
        }
    };

    set<State> visited_states;
    int loop_count = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            if(map[i][j] == '#' || (i == guard_i && j == guard_j)){
                continue;
            }

            vector<vector<char>> copy_map = map;
            copy_map[i][j] = '#';

            int current_guard_i = guard_i;
            int current_guard_j = guard_j;
            Direction current_guard_facing = guard_facing;

            visited_states.clear();

            bool is_loop = false;
            while(true){
                State current_state{current_guard_i, current_guard_j, current_guard_facing};
                
                if(visited_states.count(current_state) > 0){
                    is_loop = true;
                    break;
                }
                
                visited_states.insert(current_state);

                int next_i = current_guard_i + directionVector[current_guard_facing][0];
                int next_j = current_guard_j + directionVector[current_guard_facing][1];

                if (next_i < 0 || next_j < 0 || next_i >= copy_map.size() || next_j >= copy_map[0].size()) {
                    break;
                }

                if(copy_map[next_i][next_j] == '#'){
                    current_guard_facing = static_cast<Direction>((current_guard_facing + 1) % 4);
                } else {
                    current_guard_i = next_i;
                    current_guard_j = next_j;
                }
            }

            if(is_loop){
                loop_count++;
            }
            cout << i << " " << j << endl;
        }
    }

    // Debug: Print final state of the map
    // cout << "Final map:" << endl;
    // for (const auto& row : map) {
    //     for (char c : row) {
    //         cout << c;
    //     }
    //     cout << endl;
    // }

    cout << "Part two answer: " << loop_count << endl;
    return 0;
}