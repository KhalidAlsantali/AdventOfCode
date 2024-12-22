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
    unordered_map<int64_t, vector<int64_t>> prices;
    unordered_map<string, int64_t> bananas;
    set<string> seen;  // Moved outside all loops
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
            prev = secret;
        }
    }


    for(int64_t num : numbers){
        cout << num << endl;
        for(int i = 3; i < 2000; i++){
            string seq = to_string(prices[num][i-3]) + "," + 
                        to_string(prices[num][i-2]) + "," + 
                        to_string(prices[num][i-1]) + "," + 
                        to_string(prices[num][i]);
            
            if(seen.find(seq) == seen.end()){
                seen.insert(seq);

                for(int64_t test_num : numbers){

                    for(int j = 3; j < 2000; j++){
                        if(prices[test_num][j-3] == prices[num][i-3] &&
                           prices[test_num][j-2] == prices[num][i-2] &&
                           prices[test_num][j-1] == prices[num][i-1] &&
                           prices[test_num][j] == prices[num][i]){

                            int64_t secret = test_num;
                            for(int k = 0; k <= j; k++){
                                secret = mix(secret * 64, secret);
                                secret = prune(secret);
                                secret = mix(secret / 32, secret);
                                secret = prune(secret);
                                secret = mix(secret * 2048, secret);
                                secret = prune(secret);
                            }
                            bananas[seq] += secret % 10;
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