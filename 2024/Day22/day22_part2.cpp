#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
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
    string line;
    
    if (!inputFile.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    
    while (getline(inputFile, line)) {
        numbers.push_back(stoll(line));
    }
    inputFile.close();

    unordered_map<string, int64_t> totals;
    unordered_map<string, bool> seen_this_buyer;
    string seq;
    seq.reserve(16);  // Reserve space for 4 numbers and 3 commas

    for (int64_t num : numbers) {
        seen_this_buyer.clear();
        vector<int> diffs;
        diffs.reserve(ITERATIONS);
        

        int64_t secret = num;
        int64_t prev = num;
        
        for (int i = 0; i < ITERATIONS; i++) {
            secret = compute_secret(secret);
            diffs.push_back(secret % 10 - prev % 10);
            prev = secret;
        }


        for (int i = 3; i < ITERATIONS; i++) {
            seq = to_string(diffs[i-3]) + "," +
                  to_string(diffs[i-2]) + "," +
                  to_string(diffs[i-1]) + "," +
                  to_string(diffs[i]);
            

            if (!seen_this_buyer[seq]) {
                seen_this_buyer[seq] = true;

                int64_t price = compute_secret(num);
                for (int j = 0; j < i; j++) {
                    price = compute_secret(price);
                }
                totals[seq] += price % 10;
            }
        }
    }

    int64_t maxTotal = 0;
    string maxSeq;
    for (const auto& [seq, total] : totals) {
        if (total > maxTotal) {
            maxTotal = total;
            maxSeq = seq;
        }
    }

    cout << "Part two answer: " << maxTotal << endl;
    return 0;
}