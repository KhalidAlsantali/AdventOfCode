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

// I made 10k bitmaps to manually look for the shape of the tree then automated solving the solution based on its shape. I just look for 10 robots in a row.

using namespace std;

int mod(int a, int b) {
    return ((a % b) + b) % b;
}

int part1sol(vector<vector<int>>& map, int rows, int cols){
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


// None of the image writing code is mine.
// Bitmap header structures
#pragma pack(push, 1)
struct BITMAPFILEHEADER {
    uint16_t bfType = 0x4D42; // 'BM' in little-endian
    uint32_t bfSize;
    uint16_t bfReserved1 = 0;
    uint16_t bfReserved2 = 0;
    uint32_t bfOffBits;
};

struct BITMAPINFOHEADER {
    uint32_t biSize = 40;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes = 1;
    uint16_t biBitCount = 24; // 24 bits for RGB
    uint32_t biCompression = 0;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter = 0;
    int32_t biYPelsPerMeter = 0;
    uint32_t biClrUsed = 0;
    uint32_t biClrImportant = 0;
};
#pragma pack(pop)

void writeBitmapToFile(const vector<vector<int>>& map, const string& filename) {
    int rows = map.size();
    int cols = map[0].size();

    // Bitmap file and info headers
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    infoHeader.biWidth = cols;
    infoHeader.biHeight = rows;
    infoHeader.biSizeImage = ((cols * 3 + 3) & ~3) * rows; // Each row is padded to a multiple of 4 bytes
    fileHeader.bfSize = 54 + infoHeader.biSizeImage; // 54 bytes for headers

    fileHeader.bfOffBits = 54; // Headers are 54 bytes long

    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Error opening file " << filename << " for writing!" << endl;
        return;
    }

    // Write the headers
    outFile.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    outFile.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // Write the pixel data
    for (int i = rows - 1; i >= 0; --i) {  // BMP format starts from the bottom row
        for (int j = 0; j < cols; ++j) {
            int pixelValue = map[i][j];
            // Pure black for 0, pure white for positive values
            uint8_t pixelColor = (pixelValue > 0) ? 255 : 0;  // 255 for white, 0 for black

            // Write the pixel in BGR format (BMP uses BGR instead of RGB)
            outFile.put(pixelColor);    // Blue
            outFile.put(pixelColor);    // Green
            outFile.put(pixelColor);    // Red
        }

        // Pad the row if necessary (each row must be a multiple of 4 bytes)
        for (int padding = 0; padding < (4 - (cols * 3) % 4) % 4; ++padding) {
            outFile.put(0); // Padding byte
        }
    }

    outFile.close();
}


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
    // basically while(true) but i needed the index.
    for(int i = 0; i < INT_MAX; i++){
        if(tree_found){
            break;
        }
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

        string filename = "output/map_iteration_" + to_string(i) + ".bmp";

        writeBitmapToFile(map, filename);
        if(i == 99){
            safety_factor = part1sol(map, rows, cols);
        }
        for(int k = 0; static_cast<size_t>(k) < map.size(); k++){
            int count = 0;
            for(int m = 0; static_cast<size_t>(m) < map[k].size(); m++){
                if(map[k][m] > 0){
                    count++;
                } else {
                    count = 0;
                }
                if(count > 10){
                    tree_found = true;
                    tree_location = i + 1;
                    break;
                }
            }
            if(tree_found){
                break;
            }
        }
        
    }

    cout << "Part one answer: " << safety_factor << endl;
    cout << "Part two answer: " << tree_location << endl;

}
