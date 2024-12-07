#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main(){
    string rules_filename = "rules.txt";
    string updates_filename = "updates.txt";
    ifstream updates_file(updates_filename);
    ifstream rules_file(rules_filename);
    vector<pair<int, int>> rules;
    vector<vector<int>> updates;

    if(!rules_file.is_open()){
        cerr << "Error: Couldn't open file" << rules_filename << endl;
    }
    if(!updates_file.is_open()){
        cerr << "Error: Couldn't open file" << updates_filename << endl;
    }
    string line;

    while (getline(rules_file, line)) {
        istringstream ss(line);
        int firstVal, secondVal;
        char delimiter;

        if(ss >> firstVal >> delimiter >> secondVal && delimiter == '|'){
            rules.emplace_back(firstVal, secondVal);
        }
    }
    rules_file.close();

    while (getline(updates_file, line)) {
        vector<int> row;
        istringstream ss(line);
        string token;
        char delimiter = ',';

        while(getline(ss, token, delimiter)){
            row.push_back(stoi(token));
        }
        updates.push_back(row);

    }
    updates_file.close();

    int sum = 0;
    int broken_sum = 0;
    bool rule_broken = false;
    bool rules_changed = false;
    for(size_t i = 0; i < updates.size(); ++i){
        rule_broken = false;
        vector<int> update = updates[i];
        do {
            rules_changed = false;
            for(size_t j = 0; j < rules.size(); ++j){
                auto it_1 = find(update.begin(), update.end(), rules[j].first);
                auto it_2 = find(update.begin(), update.end(), rules[j].second);

                if(it_1 != update.end() && it_2 != update.end()){ 
                    if(distance(update.begin(), it_1) < distance(update.begin(), it_2)){
                        //do nothing
                    } else {
                        rule_broken = true;
                        rules_changed = true;
                        int temp;
                        temp = update[distance(update.begin(), it_1)];
                        update[distance(update.begin(), it_1)] = update[distance(update.begin(), it_2)];
                        update[distance(update.begin(), it_2)] = temp;
                    }
                }
            }
        } while(rules_changed);

        if(rule_broken){
            broken_sum += update[update.size() / 2];
        } else{
            sum += update[update.size() / 2];
        }
    }
    
    cout << "Part one answer: " << sum << endl;
    cout << "Part two answer: " << broken_sum << endl;
    return 0;
}