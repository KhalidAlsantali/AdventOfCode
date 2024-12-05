#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

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
    string total;
    while(getline(inputFile, line)){
        total += line;
    }

    vector<string> part1_matches;
    regex p1mul_pattern("mul\\(\\d{1,3},\\d{1,3}\\)");
    auto p1words_begin = sregex_iterator(total.begin(), total.end(), p1mul_pattern);
    auto p1words_end = sregex_iterator();
    bool p1enabled = true;
    for(sregex_iterator i = p1words_begin; i != p1words_end; ++i){
        smatch match = *i;
        // cout << match.str() << endl;
        if(match.str() == "do()"){
            p1enabled = true;
        }
        if(match.str() == "don't()"){
            p1enabled = false;
        }
        if(p1enabled){
            part1_matches.push_back(match.str());
        }
    }

    vector<string> part2_matches;
    regex mul_pattern("(mul\\(\\d{1,3},\\d{1,3}\\))|(do\\([^)]*\\))|(don't\\([^)]*\\))");
    auto words_begin = sregex_iterator(total.begin(), total.end(), mul_pattern);
    auto words_end = sregex_iterator();
    bool enabled = true;
    for(sregex_iterator i = words_begin; i != words_end; ++i){
        smatch match = *i;
        // cout << match.str() << endl;
        if(match.str() == "do()"){
            enabled = true;
        }
        if(match.str() == "don't()"){
            enabled = false;
        }
        if(enabled){
            part2_matches.push_back(match.str());
        }
    }

    int sum = 0;
    int adjusted_sum = 0;
    regex num_pattern("(\\d{1,3}),(\\d{1,3})");
    for(int i = 0; i < part1_matches.size(); i++){
        auto matches_begin = sregex_iterator(part1_matches[i].begin(), part1_matches[i].end(), num_pattern);
        auto matches_end = sregex_iterator();
        for(sregex_iterator j = matches_begin; j != matches_end; ++j){
            smatch match = *j;
            sum += stoi(match[1]) * stoi(match[2]);
        }
    }

    for(int i = 0; i < part2_matches.size(); i++){
        auto matches_begin = sregex_iterator(part2_matches[i].begin(), part2_matches[i].end(), num_pattern);
        auto matches_end = sregex_iterator();
        for(sregex_iterator j = matches_begin; j != matches_end; ++j){
            smatch match = *j;
            adjusted_sum += stoi(match[1]) * stoi(match[2]);
        }
    }
    
    cout << "Part one answer: " << sum << endl;
    cout << "Part two answer: " << adjusted_sum << endl;


}