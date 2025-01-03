#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int getNextNum(int factor, int num) {
    return ((long long)factor * (num % 2147483647)) % 2147483647;
}

bool compareNums(int GenA, int GenB) {
    return (GenA & 0xFFFF) == (GenB & 0xFFFF);
}

int getNextValid(int current, int factor, int divisor) {
    do {
        current = getNextNum(factor, current);
    } while (current % divisor != 0);
    return current;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
   
    string line;
    getline(inputFile, line);
    int GenA_init = stoi(line.substr(line.find_last_of(" ") + 1));
    getline(inputFile, line);
    int GenB_init = stoi(line.substr(line.find_last_of(" ") + 1));
    
    int GenA_current = GenA_init, GenB_current = GenB_init;
    const int GenA_factor = 16807, GenB_factor = 48271;
    int total = 0;
    
    for(int i = 0; i < 40000000; i++) {
        GenA_current = getNextNum(GenA_factor, GenA_current);
        GenB_current = getNextNum(GenB_factor, GenB_current);
        if(compareNums(GenA_current, GenB_current)) {
            total++;
        }
    }
    
    GenA_current = GenA_init;
    GenB_current = GenB_init;
    int total2 = 0;
    
    for(int i = 0; i < 5000000; i++) {
        GenA_current = getNextValid(GenA_current, GenA_factor, 4);
        GenB_current = getNextValid(GenB_current, GenB_factor, 8);
        if(compareNums(GenA_current, GenB_current)) {
            total2++;
        }
    }
    
    cout << "Part one answer: " << total << endl;
    cout << "Part two answer: " << total2 << endl;
    return 0;
}