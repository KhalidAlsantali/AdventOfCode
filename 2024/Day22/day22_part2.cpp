#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
using namespace std;

int64_t prune(int64_t num){
    return num % 16777216;
}

int64_t mix(int64_t num1, int64_t num2){
    return num1 ^ num2;
}

int main(){
    ifstream inputFile("input.txt");
    vector<int64_t> numbers;
    vector<vector<int64_t>> all_numbers;
    unordered_map<int64_t, vector<int64_t>> prices;
    unordered_map<string, int64_t> bananas;
    set<string> seen;
    string line;
    
    if(inputFile.is_open()){
        while (getline(inputFile, line)) {
            int64_t number = stoll(line);
            numbers.push_back(number);
        }
        inputFile.close();
    } else{
        cerr << "Unable to open file" << endl;
    }

    for(int64_t num : numbers){
        int64_t secret = num;
        int64_t prev = num;
        vector<int64_t> row;
        for(int i = 0; i < 2000; i++){
            // step 1
            secret = mix(secret * 64, secret);
            secret = prune(secret);
            // step 2
            secret = mix(secret / 32, secret);
            secret = prune(secret);
            // step 3
            secret = mix(secret * 2048, secret);
            secret = prune(secret);
            prices[num].push_back(secret%10 - prev%10);
            row.push_back(secret);
            prev = secret;
        }
        all_numbers.push_back(row);
    }

    for(size_t idx = 0; idx < numbers.size(); idx++){
        int64_t num = numbers[idx];
        cout << num << endl;
        for(int i = 3; i < 2000; i++){
            string seq = to_string(prices[num][i-3]) + "," +
                        to_string(prices[num][i-2]) + "," +
                        to_string(prices[num][i-1]) + "," +
                        to_string(prices[num][i]);
           
            if(seen.find(seq) == seen.end()){
                seen.insert(seq);
                for(size_t test_idx = 0; test_idx < numbers.size(); test_idx++){
                    int64_t test_num = numbers[test_idx];
                    for(int j = 3; j < 2000; j++){
                        if(prices[test_num][j-3] == prices[num][i-3] &&
                           prices[test_num][j-2] == prices[num][i-2] &&
                           prices[test_num][j-1] == prices[num][i-1] &&
                           prices[test_num][j] == prices[num][i]){

                            bananas[seq] += all_numbers[test_idx][j] % 10;
                            break;
                        }
                    }
                }
            }
        }
    }

    int64_t maxBananaValue = 0;
    string maxBananaKey;
    for (const auto& pair : bananas) {
        if (pair.second > maxBananaValue) {
            maxBananaValue = pair.second;
            maxBananaKey = pair.first;
        }
    }

    cout << "Part two answer: " << maxBananaValue << endl;
    return 0;
}