#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }

    vector<int> captcha;
    string line;
    while (getline(inputFile, line)) {
        for(char c : line){
            captcha.push_back(stoi(string(1, c)));
        }
    }
    inputFile.close();

    int sum = 0;
    int steps = 1;
    for(size_t i = 0; i < captcha.size(); i++){
        if(captcha[i] == captcha[(i + steps) % captcha.size()]){
            sum += captcha[i];
        }
    }

    cout << "Part one answer: " << sum << endl;


    sum = 0;
    steps = captcha.size() / 2;
    for(size_t i = 0; i < captcha.size(); i++){
        if(captcha[i] == captcha[(i + steps) % captcha.size()]){
            sum += captcha[i];
        }
    }

    cout << "Part two answer: " << sum << endl;

    return 0;
}