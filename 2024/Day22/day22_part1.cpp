#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

    int64_t result = 0;
    for(int64_t num : numbers){
        int64_t secret = num;
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
        }
        result += secret;
    }

    cout << "Part one answer: " << result << endl;
    return 0;
}