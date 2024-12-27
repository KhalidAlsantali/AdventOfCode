#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

int sumAdjacent(const vector<vector<int>>& matrix, int x, int y) {
    int sum = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(i == 0 && j == 0) continue;
            sum += matrix[x + i][y + j];
        }
    }
    return sum;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file input.txt";
        return 1;
    }

    std::string line;
    std::getline(inputFile, line);
    inputFile.close();

    int input = std::stoi(line);

    const int size = 100;
    vector<vector<int>> matrix(size, vector<int>(size, 0));
    int answer = 0;

    int x = size / 2;
    int y = size / 2;
    matrix[x][y] = 1;

    int dx = 1;  
    int dy = 0;
    int steps = 1;
    int stepCount = 0;

    while (true) {
        x += dx;
        y += dy;
        

        int newValue = sumAdjacent(matrix, x, y);
        matrix[x][y] = newValue;
        
        if(newValue > input) {
            answer = newValue;
            break;
        }

        stepCount++;
        if (stepCount == steps) {
            stepCount = 0;

            int temp = dx;
            dx = -dy;
            dy = temp;

            if (dy == 0) steps++;
        }
    }

    cout << "Part two answer: " << answer << endl;

    return 0;
}