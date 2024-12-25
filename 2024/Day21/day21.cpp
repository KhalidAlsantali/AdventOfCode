#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

vector<string> numpad = {"789", "456", "123", " 0A"};
vector<string> dirpad = {" ^A", "<v>"};
map<char, pair<int, int>> digits, directions;
map<pair<pair<char, char>, int>, uint64_t> cache;
int globalDirpadLayers;

vector<string> pathsBetweenTwoKeys(vector<string> grid, pair<int, int> a, pair<int, int> b) {
    if (!grid[a.first][a.second] || grid[a.first][a.second] == ' ')
        return {};
    if (a == b)
        return {"A"};
    vector<string> paths;
    if (a.first > b.first) {
        vector<string> subPaths = pathsBetweenTwoKeys(grid, {a.first - 1, a.second}, b);
        for (auto path : subPaths)
            paths.push_back("^" + path);
    }
    if (a.first < b.first) {
        vector<string> subPaths = pathsBetweenTwoKeys(grid, {a.first + 1, a.second}, b);
        for (auto path : subPaths)
            paths.push_back("v" + path);
    }
    if (a.second > b.second) {
        vector<string> subPaths = pathsBetweenTwoKeys(grid, {a.first, a.second - 1}, b);
        for (auto path : subPaths)
            paths.push_back("<" + path);
    }
    if (a.second < b.second) {
        vector<string> subPaths = pathsBetweenTwoKeys(grid, {a.first, a.second + 1}, b);
        for (auto path : subPaths)
            paths.push_back(">" + path);
    }
    return paths;
}

uint64_t shortestPathAtLayer(char a, char b, int layer) {
    if (layer == globalDirpadLayers)
        return 1;
    pair<pair<char, char>, int> key = {{a, b}, layer};
    if (cache.find(key) != cache.end())
        return cache[key];
    
    uint64_t shortestPath = UINT64_MAX;
    vector<string> paths;
    if (layer == 0)
        paths = pathsBetweenTwoKeys(numpad, digits[a], digits[b]);
    else
        paths = pathsBetweenTwoKeys(dirpad, directions[a], directions[b]);
        
    for (string path : paths) {
        uint64_t sum = shortestPathAtLayer('A', path[0], layer + 1);
        for (size_t i = 0; i < path.size()-1; i++)
            sum += shortestPathAtLayer(path[i], path[i+1], layer + 1);
        shortestPath = min(shortestPath, sum);
    }
    cache[key] = shortestPath;
    return shortestPath;
}

uint64_t shortestPathForCode(string code) {
    uint64_t sum = shortestPathAtLayer('A', code[0], 0);
    for (size_t i = 0; i < code.size()-1; i++)
        sum += shortestPathAtLayer(code[i], code[i+1], 0);
    return sum;
}

uint64_t shortestPathForCodes(vector<string> codes) {
    uint64_t sum = 0;
    for (auto code : codes)
        sum += shortestPathForCode(code) * stoi(code.substr(0, 3));
    return sum;
}

void initializeGrids() {
    for (size_t i = 0; i < dirpad.size(); i++)
        for (size_t j = 0; j < dirpad[i].size(); j++)
            if (dirpad[i][j] != ' ')
                directions[dirpad[i][j]] = {i, j};
                
    for (size_t i = 0; i < numpad.size(); i++)
        for (size_t j = 0; j < numpad[i].size(); j++)
            if (numpad[i][j] != ' ')
                digits[numpad[i][j]] = {i, j};
}

int main() {

    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }
    string line;
    vector<string> codes;
    while(getline(inputFile, line))
        codes.push_back(line);
    inputFile.close();

    initializeGrids();
    
    globalDirpadLayers = 3;
    cache.clear();
    cout << "Part one answer: " << shortestPathForCodes(codes) << endl;
    
    globalDirpadLayers = 26;
    cache.clear();
    cout << "Part two answer: " << shortestPathForCodes(codes) << endl;
    return 0;
}