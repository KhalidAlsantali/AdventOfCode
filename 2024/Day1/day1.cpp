#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main(){
    vector<string> list1;
    vector<string> list2;
    string filename = "input.txt";
    ifstream inputFile(filename);

    if(!inputFile.is_open()){
        cerr << "Error: Couldn't open file" << filename << endl;
    }

    string line;
    
    // stringstream implementation
    // while(getline(inputFile, line)){
    //     istringstream ss(line);
    //     string word;
    //     while(ss >> word){
    //         if(index % 2 == 0){
    //             list1.push_back(word);
    //         } else {
    //             list2.push_back(word);
    //         }
    //         index++;
    //     }
    // }

    // manual parsing implementation
    while(getline(inputFile, line)){
        size_t firstSpacePos = line.find(' ');
        list1.push_back(line.substr(0, firstSpacePos));
        list2.push_back(line.substr(firstSpacePos + 3, line.size()));
    }

    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    int total_dist = 0;
    int total_sim = 0;

    for(size_t i = 0; i < list1.size(); i++){
        total_dist += abs(stoi(list1[i]) - stoi(list2[i]));
    }

    for(size_t i = 0; i < list1.size(); i++){
        int occurances = 0;
        for(size_t j = 0; j < list2.size(); j++){
            if(list1[i] == list2[j]){
                occurances++;
            }
        }
        total_sim += stoi(list1[i]) * occurances;
    }
    
    cout << "Part one answer: " << total_dist << endl;
    cout << "Part two answer: " << total_sim << endl;
    return 0;
}