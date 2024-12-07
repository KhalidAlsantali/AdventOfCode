#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(){
    vector<vector<string>> string_data;
    vector<vector<int>> data;
    int i = 0;
    string filename = "input.txt";
    ifstream inputFile(filename);

    if(!inputFile.is_open()){
        cerr << "Error: Couldn't open file" << filename << endl;
    }
    string line;
    string acc;
    while(getline(inputFile, line)){
        string_data.emplace_back();
        data.emplace_back();
        for(char c : line){
            if(c == ' '){
                string_data[i].push_back(acc);
                acc = "";
            } else {
                acc += c;
            }
        }
        string_data[i].push_back(acc);
        acc = "";
        for(size_t j = 0; j < string_data[i].size(); j++){
            data[i].push_back(stoi(string_data[i][j]));
        }
        i++;
    }
    int safe_count = 0;
    int safe_count_original = 0;
    for (size_t j = 0; j < data.size(); j++) {
        bool safe = true;
        bool increases = data[j][1] - data[j][0] > 0;
        for (size_t k = 1; k < data[j].size(); k++) {
            int compare = data[j][k] - data[j][k - 1];
            if (increases) {
                if (compare > 3 || compare < 1) {
                    safe = false;
                    break; 
                }
            } else {
                if (compare < -3 || compare > -1) {
                    safe = false;
                    break;
                }
            }
        }
        if(safe){
            safe_count_original++;
        }
    }
    for (size_t j = 0; j < data.size(); j++) {
        vector<int> levels = data[j]; 
        bool safe = true;
        bool isIncreasing = levels[1] > levels[0]; 

   
        for (size_t k = 1; k < levels.size(); k++) {
            int diff = levels[k] - levels[k - 1];
            if (isIncreasing) {
                if (diff > 3 || diff < 1) {
                    safe = false;
                    break;
                }
            } else {
                if (diff < -3 || diff > -1) {
                    safe = false;
                    break;
                }
            }
        }

       
        if (!safe) {
          
            bool fixed = false;
            for (size_t x = 0; x < levels.size(); x++) {
                vector<int> newLevels;
                for (size_t y = 0; y < levels.size(); y++) {
                    if (y != x) {
                        newLevels.push_back(levels[y]);
                    }
                }

        
                bool isSafe = true;
                bool newIsIncreasing = newLevels[1] > newLevels[0];  

                for (size_t k = 1; k < newLevels.size(); k++) {
                    int diff = newLevels[k] - newLevels[k - 1];
                    if (newIsIncreasing) {
                        if (diff > 3 || diff < 1) {
                            isSafe = false;
                            break;
                        }
                    } else {
                        if (diff < -3 || diff > -1) {
                            isSafe = false;
                            break;
                        }
                    }
                }
                if (isSafe) {
                    fixed = true;
                    break;  
                }
            }
            if (fixed) {
                safe_count++;
            }
        } else {
            safe_count++;
        }
    }

    cout << "Part one answer: " << safe_count_original << endl;
    cout << "Part two answer: " << safe_count << endl;
    return 0;
}