#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

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

    int layer = 0;
    while ((2 * layer + 1) * (2 * layer + 1) < input) {
        layer++;
    }

    int sideLength = 2 * layer + 1;
    int maxInLayer = sideLength * sideLength;

    int stepsBackFromMax = maxInLayer - input;

    int sideOffset = stepsBackFromMax % (sideLength - 1);

    int distance = layer + abs(sideOffset - layer);

    std::cout << "Part one answer: " << distance << std::endl;

    return 0;
}
