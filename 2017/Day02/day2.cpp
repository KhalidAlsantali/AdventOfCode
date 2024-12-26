#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <cmath>

using namespace std;

bool isDivisible(int a, int b){
    return (a % b == 0) || (b % a == 0);
}

int commutativeDivision(int a, int b){
    return round(exp(abs(log(a) - log(b))));
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    vector<vector<int>> spreadsheet;
    string line;
    while (getline(inputFile, line)) {
        vector<int> numbers;
        stringstream ss(line);
        string temp;
        while (ss >> temp) {
            numbers.push_back(stoi(temp));
        }
        spreadsheet.push_back(numbers);
    }

    int sum = 0;
    for(const auto& line : spreadsheet){
        sum += *max_element(line.begin(), line.end()) - *min_element(line.begin(), line.end());
    }

    cout << "Part one answer: " << sum << endl;

    sum = 0; 
    for(const auto& line : spreadsheet){
        for(size_t i = 0; i < line.size(); i++){
            for(size_t j = i; j < line.size(); j++){
                if(line[i] == line[j]){
                    continue;
                }
                if(isDivisible(line[i], line[j])){
                    sum += commutativeDivision(line[i], line[j]);
                }
            }
        }
    }

    cout << "Part two answer: " << sum << endl;

    inputFile.close();

}