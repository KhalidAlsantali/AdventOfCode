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
#include <stack>
#include <regex>

using namespace std;

int mod(int a, int b) {
    return ((a % b) + b) % b;
}

int main(){
    string input_filename = "input.txt";
    ifstream inputFile(input_filename);
    regex digit_pattern("-?\\d+");
    vector<vector<int>> robots;
    int rows = 103;  //TALL
    int cols = 101; //WIDE
    vector<vector<int>> map(rows, vector<int>(cols, 0));

    string line, number;
    while (getline(inputFile, line)) {
        vector<int> robot;
        auto digits_begin = sregex_iterator(line.begin(), line.end(), digit_pattern);
        auto digits_end = sregex_iterator();
        for (auto it = digits_begin; it != digits_end; ++it) {
            smatch match = *it;
            robot.push_back(stoi(match.str()));
        }
        robots.push_back(robot);
    }

    // for (const auto& row : robots) {
    //     for (const auto& element : row) {
    //         cout << element << " ";
    //     }
    //     cout << endl; // Newline after each row
    // }

    for(const auto& robot : robots){
        map[robot[1]][robot[0]]++;
    }

    for(int i = 0; i < 100; i++){
        for(auto& robot : robots){
            map[robot[1]][robot[0]]--;

            //cal new pos
            int new_i = robot[1] + robot[3];
            int new_j = robot[0] + robot[2];

            //adjust pos
            new_i = mod(new_i, rows);
            new_j = mod(new_j, cols);

            // cout << new_j << " : " << new_i << endl; 

            robot[0] = new_j;
            robot[1] = new_i;

            map[new_i][new_j]++;
        }
        // cout << endl;
    }

    for (const auto& row : map) {
        for (const auto& element : row) {
            cout << element;
        }
        cout << endl; // Newline after each row
    }

    int q1_sum = 0;
    int q2_sum = 0;
    int q3_sum = 0;
    int q4_sum = 0;
    int i_mid = (rows - 1) / 2; // 3
    int j_mid = (cols - 1) / 2; // 5
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            if(i > i_mid){
                if(j > j_mid){
                    q4_sum += map[i][j];
                    // cout << "Point (" << i << ", " << j << ") | Value: " << map[i][j] << " Added to Q4" << endl;
                } else if (j < j_mid) {
                    q3_sum += map[i][j];
                    // cout << "Point (" << i << ", " << j << ") | Value: " << map[i][j] << " Added to Q3" << endl;
                }
            } else if(i < i_mid) {
                if(j > j_mid){
                    q2_sum += map[i][j];
                    // cout << "Point (" << i << ", " << j << ") | Value: " << map[i][j] << " Added to Q2" << endl;

                } else if(j < j_mid) {
                    q1_sum += map[i][j];
                    // cout << "Point (" << i << ", " << j << ") | Value: " << map[i][j] << " Added to Q1" << endl;

                }
            }
        }
    }

    cout << q1_sum << ":" << q2_sum << ":" << q3_sum << ":" << q4_sum << endl;
    
    int safety_factor = q1_sum * q2_sum * q3_sum * q4_sum;
    cout << "Part one answer: " << safety_factor << endl;

}