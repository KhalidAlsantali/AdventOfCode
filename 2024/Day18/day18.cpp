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
#include <queue>

using namespace std;

int dijkstra(const vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    
    // Priority queue: {distance, {x, y}}
    priority_queue<pair<int, pair<int,int>>, 
                  vector<pair<int, pair<int,int>>>,
                  greater<>> pq;
                  
    // Distance matrix initialized to max
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    
    // Start at top-left (0,0)
    pq.push({0, {0, 0}});
    dist[0][0] = 0;
    
    // Directions: right, down, left, up
    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {1, 0, -1, 0};
    
    while (!pq.empty()) {
        auto [d, pos] = pq.top();
        auto [x, y] = pos;
        pq.pop();
        
        // If we've reached bottom-right corner
        if (x == n-1 && y == m-1) return d;
        
        // Skip if we've found a better path already
        if (d > dist[x][y]) continue;
        
        // Check all 4 directions
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            // Check bounds and if cell is an obstacle (#)
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] == '#') continue;
            
            int new_dist = d + 1;
            if (new_dist < dist[nx][ny]) {
                dist[nx][ny] = new_dist;
                pq.push({new_dist, {nx, ny}});
            }
        }
    }
    
    return -1; // No path found
}

int main(){
    string filename = "input.txt";
    ifstream mapFile(filename);
    vector<vector<char>> map(71, vector<char>(71, '.'));
    vector<pair<int, int>> blocks;

    string line;
    while (getline(mapFile, line)) {
        istringstream ss(line);
        int first, second;
        char comma;
        if(ss >> first >> comma >> second){
            blocks.push_back(make_pair(first, second));
        }
    }

    for(int i = 0; i < 1024; i++){
        map[blocks[i].first][blocks[i].second] = '#';
    }


    cout << "Part one answer: " << dijkstra(map) << endl;

    int left = 1024;
    int right = blocks.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        
        vector<vector<char>> map(71, vector<char>(71, '.'));
        
        for (int i = 0; i <= mid; i++) {
            map[blocks[i].first][blocks[i].second] = '#';
        }
        
        if (dijkstra(map) == -1) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    cout << "Part two answer: " << blocks[left].first << "," << blocks[left].second << endl;
}
