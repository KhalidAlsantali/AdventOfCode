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

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    
    string line;
    getline(inputFile, line);


    vector<int> buffer = {0};
    int step = stoi(line);
    int index = 0;
    int counter = 0;
    while(counter < 2017){
        index = (index + step) % buffer.size();
        buffer.insert(buffer.begin() + index + 1, ++counter);
        ++index;
    }

    vector<int>::iterator it = find(buffer.begin(), buffer.end(), 2017);
    int result = (it != buffer.end() && next(it) != buffer.end()) ? *next(it) : -1;

    int result2 = 0;
    index = 0;
    counter = 1;
    while(counter <= 50000000){
        index = (index + step) % counter;
        ++index;
        if(index == 1) result2 = counter;
        ++counter;
    }

    cout << "Part one answer: " << result << endl;
    cout << "Part two answer: " << result2 << endl;
    return 0;
}