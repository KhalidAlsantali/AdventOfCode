#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <limits>
#include <fstream>

const int dx[] = {1, 0, -1, 0};  // Direction deltas for x
const int dy[] = {0, 1, 0, -1};  // Direction deltas for y

struct State {
    int x, y;
    int direction;
    int score;

    bool operator>(const State& other) const {
        return score > other.score;
    }
};

struct StateKey {
    int x, y, direction;
    
    bool operator<(const StateKey& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return direction < other.direction;
    }
};

struct Position {
    int x, y;
    
    bool operator<(const Position& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

class MazeSolver {
private:
    std::vector<std::string> maze;
    int startX, startY;
    int endX, endY;
    int rows, cols;
    int bestScore;
    std::set<Position> optimalTiles;
    std::map<StateKey, int> minScoreToEnd;  // Minimum score needed from any state to reach end

    bool isValid(int x, int y) const {
        return x >= 0 && x < cols && y >= 0 && y < rows && maze[y][x] != '#';
    }

    // Phase 1: Find the best score
    void findBestScore() {
        std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
        std::map<StateKey, int> visited;
        
        pq.push({startX, startY, 0, 0});
        bestScore = -1;
        
        while (!pq.empty()) {
            State current = pq.top();
            pq.pop();

            StateKey key = {current.x, current.y, current.direction};
            
            if (visited.count(key) && visited[key] <= current.score) {
                continue;
            }
            visited[key] = current.score;

            if (current.x == endX && current.y == endY) {
                if (bestScore == -1 || current.score < bestScore) {
                    bestScore = current.score;
                }
                continue;
            }

            // Try moving forward
            int newX = current.x + dx[current.direction];
            int newY = current.y + dy[current.direction];
            if (isValid(newX, newY)) {
                pq.push({newX, newY, current.direction, current.score + 1});
            }

            // Try turning left
            int leftDir = (current.direction + 3) % 4;
            pq.push({current.x, current.y, leftDir, current.score + 1000});

            // Try turning right
            int rightDir = (current.direction + 1) % 4;
            pq.push({current.x, current.y, rightDir, current.score + 1000});
        }
    }

    // Compute minimum scores from each state to the end
    void computeMinScoresToEnd() {
        std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
        minScoreToEnd.clear();

        // Start from end point, try all directions
        for (int dir = 0; dir < 4; dir++) {
            State endState = {endX, endY, dir, 0};
            pq.push(endState);
            minScoreToEnd[{endX, endY, dir}] = 0;
        }

        while (!pq.empty()) {
            State current = pq.top();
            pq.pop();

            int currentMinScore = minScoreToEnd[{current.x, current.y, current.direction}];
            if (currentMinScore < current.score) continue;

            // Try all reverse moves that could have led here
            // Forward move (becomes backward from end)
            int prevX = current.x - dx[current.direction];
            int prevY = current.y - dy[current.direction];
            if (isValid(prevX, prevY)) {
                StateKey prevKey = {prevX, prevY, current.direction};
                int newScore = current.score + 1;
                if (!minScoreToEnd.count(prevKey) || minScoreToEnd[prevKey] > newScore) {
                    minScoreToEnd[prevKey] = newScore;
                    pq.push({prevX, prevY, current.direction, newScore});
                }
            }

            // Rotations (same position, different directions)
            for (int d = 0; d < 4; d++) {
                if (d != current.direction) {
                    StateKey rotKey = {current.x, current.y, d};
                    int rotScore = current.score + 1000;
                    if (!minScoreToEnd.count(rotKey) || minScoreToEnd[rotKey] > rotScore) {
                        minScoreToEnd[rotKey] = rotScore;
                        pq.push({current.x, current.y, d, rotScore});
                    }
                }
            }
        }
    }

    // Phase 2: Find all tiles that are part of optimal paths
    void findOptimalTiles() {
        std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
        std::map<StateKey, int> visited;
        optimalTiles.clear();
        
        // Compute minimum scores to end first
        computeMinScoresToEnd();
        
        pq.push({startX, startY, 0, 0});
        
        while (!pq.empty()) {
            State current = pq.top();
            pq.pop();

            StateKey key = {current.x, current.y, current.direction};
            
            if (visited.count(key) && visited[key] <= current.score) {
                continue;
            }
            visited[key] = current.score;

            // Check if this state can be part of an optimal path
            if (minScoreToEnd.count(key) && 
                current.score + minScoreToEnd[key] == bestScore) {
                optimalTiles.insert({current.x, current.y});
            } else if (current.score + minScoreToEnd[key] > bestScore) {
                continue;
            }

            // Try moving forward
            int newX = current.x + dx[current.direction];
            int newY = current.y + dy[current.direction];
            if (isValid(newX, newY)) {
                pq.push({newX, newY, current.direction, current.score + 1});
            }

            // Try turning left
            int leftDir = (current.direction + 3) % 4;
            pq.push({current.x, current.y, leftDir, current.score + 1000});

            // Try turning right
            int rightDir = (current.direction + 1) % 4;
            pq.push({current.x, current.y, rightDir, current.score + 1000});
        }
    }

public:
    MazeSolver(const std::vector<std::string>& input) {
        maze = input;
        rows = maze.size();
        cols = maze[0].size();
        
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (maze[y][x] == 'S') {
                    startX = x;
                    startY = y;
                }
                if (maze[y][x] == 'E') {
                    endX = x;
                    endY = y;
                }
            }
        }
    }

    int solve() {
        findBestScore();
        findOptimalTiles();
        return bestScore;
    }

    int getOptimalTileCount() {
        return optimalTiles.size();
    }
};

int main() {
    std::vector<std::string> maze;
    std::string line;
    std::ifstream file("input.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    while (std::getline(file, line)) {
        if (!line.empty()) {
            maze.push_back(line);
        }
    }

    file.close();

    if (maze.empty()) {
        std::cerr << "No data read from file!" << std::endl;
        return 1;
    }

    MazeSolver solver(maze);
    int result = solver.solve();
    std::cout << "Part one answer: " << result << std::endl;
    std::cout << "Part two answer: " << solver.getOptimalTileCount() << std::endl;
    
    return 0;
}