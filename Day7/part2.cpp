#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::milliseconds
#include <cstdlib>
#include <cmath>


using namespace std;

vector<string> generateCombinations(int length) {
    int num_combs = pow(3, length - 1);
    // cout << "num_combs: " << num_combs << endl;
    vector<string> combinations;
    
    for (int i = 0; i < num_combs; ++i) {
        string combination;
        for (int j = length - 2; j >= 0; --j) {
            int ternary_digit = i / (int(pow(3, j))) % 3;
            if(ternary_digit == 0){
                combination += '+';
            } else if (ternary_digit == 1){
                combination += '*';
            } else if (ternary_digit == 2){
                combination += '|';
            }
        }
        // cout << combination << endl;
        combinations.push_back(combination);
    }
   
    return combinations;
}

int64_t calculateResult(vector<int64_t> values, string operator_comb){
    int64_t result = 0;
    if(operator_comb[0] == '+'){
        result = values[0] + values[1];
    } else if (operator_comb[0] == '*'){
        result = values[0] * values[1];
    } else if (operator_comb[0] == '|'){
        result = stoll(to_string(values[0]) + to_string(values[1]));
    }

    for(int i = 1; i < operator_comb.length(); ++i){
        if(operator_comb[i] == '+'){
            result = result + values[i+1];
        } else if (operator_comb[i] == '*'){
            result = result * values[i+1];
        } else if (operator_comb[i] == '|'){
            result = stoll(to_string(result) + to_string(values[i+1]));
        }
    }
    return result;
}

int main(){
    string filename = "input.txt";
    unordered_map<int64_t , vector<int64_t >> equations;
    ifstream inputFile(filename);

    if(!inputFile.is_open()){
        cerr << "Error: Couldn't open file" << filename << endl;
        return 1;
    }
    string line;

    while (getline(inputFile, line)) {
        istringstream ss1(line);
        int64_t  result;
        char delimiter;

        ss1 >> result >> delimiter;
        vector<int64_t > values;
        int64_t  value;
        while(ss1 >> value){
            values.push_back(value);
        }
        equations[result] = values;
    }
    inputFile.close();

    // vector<string> combs_print = generateCombinations(6);
    // for(string c : combs_print){
    //     cout << c << endl;
    // }

    int64_t total = 0;
    for(const auto& [result, values] : equations){
        vector<string> combs = generateCombinations(values.size());
        for(string comb : combs){
            if(result == calculateResult(values, comb)){
                total += result;
                break;
            }
        }
    }
    cout << total << endl;
}