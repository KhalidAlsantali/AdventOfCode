#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int sum = 0;
int mas_sum = 0;

bool checkDiagLeft(size_t i, size_t j, vector<vector<char>> data){
    if (i >= 3 && j >= 3 && 
        data[i-1][j-1] == 'M' && data[i-2][j-2] == 'A' && data[i-3][j-3] == 'S'){
        sum++;
        return true;
    }
    return false;
}

bool checkDiagRight(size_t i, size_t j, vector<vector<char>> data){
    if (i >= 3 && j < data[i].size() - 3 && 
        data[i-1][j+1] == 'M' && data[i-2][j+2] == 'A' && data[i-3][j+3] == 'S'){
        sum++;
        return true;
    }
    return false;
}

bool checkUp(size_t i, size_t j, vector<vector<char>> data){
    if (i >= 3 && 
        data[i-1][j] == 'M' && data[i-2][j] == 'A' && data[i-3][j] == 'S'){
        sum++;
        return true;
    }
    return false;
}

bool checkDown(size_t i, size_t j, vector<vector<char>> data){
    if (i < data.size() - 3 && 
        data[i+1][j] == 'M' && data[i+2][j] == 'A' && data[i+3][j] == 'S'){
        sum++;
        return true;
    }
    return false;
}

bool checkLeft(size_t i, size_t j, vector<vector<char>> data){
    if (j >= 3 && 
        data[i][j-1] == 'M' && data[i][j-2] == 'A' && data[i][j-3] == 'S'){
        sum++;
        return true;
    }
    return false;
}

bool checkRight(size_t i, size_t j, vector<vector<char>> data){
    if (j < data[i].size() - 3 && 
        data[i][j+1] == 'M' && data[i][j+2] == 'A' && data[i][j+3] == 'S'){
        sum++;
        return true;
    }
    return false;
}

bool checkBackDiagLeft(size_t i, size_t j, vector<vector<char>> data){
    if (i < data.size() - 3 && j >= 3 && 
        data[i+1][j-1] == 'M' && data[i+2][j-2] == 'A' && data[i+3][j-3] == 'S'){
        sum++;
        return true;
    }
    return false;
}

bool checkBackDiagRight(size_t i, size_t j, vector<vector<char>> data){
    if (i < data.size() - 3 && j < data[i].size() - 3 && 
        data[i+1][j+1] == 'M' && data[i+2][j+2] == 'A' && data[i+3][j+3] == 'S'){
        sum++;
        return true;
    }
    return false;
}

void checkMas(size_t i, size_t j, vector<vector<char>> data) {
   if (i > 0 && i < data.size() - 1 && j > 0 && j < data[i].size() - 1) {
       if (data[i-1][j-1] == 'M' && data[i+1][j+1] == 'S') {
           if (data[i-1][j+1] == 'M' && data[i+1][j-1] == 'S') {
               mas_sum++;
           }
           if (data[i-1][j+1] == 'S' && data[i+1][j-1] == 'M') {
               mas_sum++;
           }
       }
       if (data[i-1][j-1] == 'S' && data[i+1][j+1] == 'M') {
           if (data[i-1][j+1] == 'S' && data[i+1][j-1] == 'M') {
               mas_sum++;
           }
           if (data[i-1][j+1] == 'M' && data[i+1][j-1] == 'S') {
               mas_sum++;
           }
       }
   }
}

void checkAllDirections(size_t i, size_t j, vector<vector<char>> data) {
  checkUp(i, j, data);
  checkDown(i, j, data);
  checkLeft(i, j, data);
  checkRight(i, j, data);
  checkDiagLeft(i, j, data);
  checkDiagRight(i, j, data);
  checkBackDiagLeft(i, j, data);
  checkBackDiagRight(i, j, data);
}

int main(){
    vector<vector<char>> data;
    string filename = "input.txt";
    ifstream inputFile(filename);

    if(!inputFile.is_open()){
        cerr << "Error: Couldn't open file" << filename << endl;
    }
    string line;
    while (getline(inputFile, line)) {
        vector<char> row(line.begin(), line.end());
        data.push_back(row);
    }
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
            if(data[i][j] == 'X'){
                checkAllDirections(i, j, data);
            }
            if(data[i][j] == 'A'){
                checkMas(i, j, data);
            }
        }
    }
    cout << "Part one answer: " << sum << endl;
    cout << "Part two answer: " << mas_sum << endl;
    return 0;
}