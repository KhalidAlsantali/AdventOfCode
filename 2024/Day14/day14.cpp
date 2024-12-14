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
#include <cmath>

// Attempt to include BitmapPlusPlus.hpp if available
#ifdef __has_include
    #if __has_include("BitmapPlusPlus.hpp")
        #define ENABLE_BITMAP
    #endif
#endif

#ifdef ENABLE_BITMAP
#include "BitmapPlusPlus.hpp"
#endif

using namespace std;

int mod(int a, int b) {
    return ((a % b) + b) % b;
}

int calculateSafetyFactor(vector<vector<int>>& map, int rows, int cols){
    int q1_sum = 0, q2_sum = 0, q3_sum = 0, q4_sum = 0;
    int i_mid = (rows - 1) / 2;
    int j_mid = (cols - 1) / 2;
    for(int i = 0; static_cast<size_t>(i) < map.size(); i++){
        for(int j = 0; static_cast<size_t>(j) < map[i].size(); j++){
            if(i > i_mid){
                if(j > j_mid){
                    q4_sum += map[i][j];
                } else if (j < j_mid) {
                    q3_sum += map[i][j];
                }
            } else if(i < i_mid) {
                if(j > j_mid){
                    q2_sum += map[i][j];
                } else if(j < j_mid) {
                    q1_sum += map[i][j];
                }
            }
        }
    }
    int safety_factor = q1_sum * q2_sum * q3_sum * q4_sum;
    return safety_factor;
}

#ifdef ENABLE_BITMAP
void writeBitmapToFile(const vector<vector<int>>& map, const string& filename) {
    bmp::Bitmap image(map[0].size(), map.size());
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            bmp::Pixel pixel;
            if(map[i][j] > 0){
                pixel.r = 255;
                pixel.g = 255;
                pixel.b = 255;
            } else {
                pixel.r = 0;
                pixel.g = 0;
                pixel.b = 0;
            }
            image.set(j, i, pixel);
        }
    }
    image.save(filename);
}
#endif

int main(){
    string input_filename = "input.txt";
    ifstream inputFile(input_filename);
    regex digit_pattern("-?\\d+");
    vector<vector<int>> robots;
    int rows = 103;
    int cols = 101;
    vector<vector<int>> map(rows, vector<int>(cols, 0));

    int safety_factor = 0;
    int tree_location = 0;
    bool tree_found = false;

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

    for(const auto& robot : robots){
        map[robot[1]][robot[0]]++;
    }
    vector<double> safety_factors;
    // Assuming the tree is in the first 10k seconds...
    for(int i = 0; i < 10000; i++){
        for(auto& robot : robots){
            if(tree_found){
                break;
            }
            map[robot[1]][robot[0]]--;

            int new_i = robot[1] + robot[3];
            int new_j = robot[0] + robot[2];

            new_i = mod(new_i, rows);
            new_j = mod(new_j, cols);

            robot[0] = new_j;
            robot[1] = new_i;

            map[new_i][new_j]++;
        }

        if(i == 99){
            safety_factor = calculateSafetyFactor(map, rows, cols);
        }
        safety_factors.push_back(calculateSafetyFactor(map, rows, cols));

#ifdef ENABLE_BITMAP
        string filename = "output/map_iteration_" + to_string(i) + ".bmp";
        writeBitmapToFile(map, filename);
#endif
    }

    auto minElement = min_element(safety_factors.begin(), safety_factors.end());
    tree_location = distance(safety_factors.begin(), minElement) + 1;

    cout << "Part one answer: " << safety_factor << endl;
    cout << "Part two answer: " << tree_location << endl;

}
