#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
using namespace std;

constexpr int64_t MASK = 0xFFFFFF;  // 16777216 - 1
constexpr int ITERATIONS = 2000;

inline int64_t compute_secret(int64_t secret) {
    secret = ((secret << 6) ^ secret) & MASK;
    secret = ((secret >> 5) ^ secret) & MASK;
    secret = ((secret << 11) ^ secret) & MASK;

    return secret;
}

int main() {
    ifstream inputFile("input.txt");
    vector<int64_t> numbers;
    vector<vector<int64_t>> all_numbers;
    unordered_map<int64_t, vector<int64_t>> prices;
    unordered_map<string, int64_t> bananas;
    set<string> seen;
    string line;
        
    if (!inputFile.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    
    while (getline(inputFile, line)) {
        numbers.push_back(stoll(line));
    }
    inputFile.close();
    
    all_numbers.reserve(numbers.size());
    for (int64_t num : numbers) {
        vector<int64_t> row;
        row.reserve(ITERATIONS);
        int64_t secret = num;
        int64_t prev = num;
        
        for (int i = 0; i < ITERATIONS; i++) {
            secret = compute_secret(secret);
            prices[num].push_back(secret % 10 - prev % 10);
            row.push_back(secret);
            prev = secret;
        }
        all_numbers.push_back(move(row)); 
    }
    
    string seq;
    seq.reserve(16);  // reserve space for 4 numbers and 3 commas
    
    for (size_t idx = 0; idx < numbers.size(); idx++) {
        int64_t num = numbers[idx];
        cout << num << endl;
        
        for (int i = 3; i < ITERATIONS; i++) {
            seq = to_string(prices[num][i-3]) + "," +
                  to_string(prices[num][i-2]) + "," +
                  to_string(prices[num][i-1]) + "," +
                  to_string(prices[num][i]);
            
            if (seen.insert(seq).second) {
                for (size_t test_idx = 0; test_idx < numbers.size(); test_idx++) {
                    int64_t test_num = numbers[test_idx];
                    auto& test_prices = prices[test_num];
                    
                    for (int j = 3; j < ITERATIONS; j++) {
                        if (test_prices[j-3] == prices[num][i-3] &&
                            test_prices[j-2] == prices[num][i-2] &&
                            test_prices[j-1] == prices[num][i-1] &&
                            test_prices[j] == prices[num][i]) {
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