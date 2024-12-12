#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>
#include <tuple>


using namespace std;

int main(){
    string input_filename = "input.txt";
    ifstream inputFile(input_filename);
    vector<vector<char>> map;
    string xcoords_filename = "x_coordinates.txt";
    vector<pair<int, int>> coordinates;
    ifstream inFile(xcoords_filename);
    string line;
    
    while (getline(inFile, line)) {
        stringstream ss(line);
        int i, j;
        char comma;
        
        if (ss >> i >> comma >> j) {
            coordinates.push_back({i, j});
        }
    }

    if(!inputFile.is_open()){
        cerr << "Error: Couldn't open file" << xcoords_filename << endl;
        return 1;
    }

    while (getline(inputFile, line)) {
        vector<char> row;
        for(char c : line){
            row.push_back(c);
        }
        map.push_back(row);
    }
    inputFile.close();

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
    int guard_i = 0, guard_j = 0;
    bool guard_found = false;

    for(size_t i = 0; i < map.size(); ++i){
        for(size_t j = 0; j < map[i].size(); ++j){
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
        // This overloads the < operator so I can use the set data structure. Not my code.
        bool operator<(const State& other) const {
            return std::tie(x, y, direction) < std::tie(other.x, other.y, other.direction);
        }
    };

    set<State> visited_states;
    int loop_count = 0;
    for(size_t k = 0; k < coordinates.size(); k++){
        int i = coordinates[k].first;
        int j = coordinates[k].second;
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

            if (next_i < 0 || next_j < 0 || static_cast<size_t>(next_i) >= copy_map.size() || static_cast<size_t>(next_j) >= copy_map[0].size()) {
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
    }

    cout << "Part two answer: " << loop_count << endl;
    return 0;
}