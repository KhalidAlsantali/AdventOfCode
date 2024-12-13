#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

using namespace std;

vector<vector<int64_t>> mulMat(vector<vector<int64_t>>& m1, vector<vector<int64_t>>& m2){
    vector<vector<int64_t>> result;
    int r1 = m1.size();
    int c1 = m1[0].size();
    int r2 = m2.size();
    int c2 = m2[0].size();

    if (c1 != r2) {
        cout << "Invalid Input" << endl;
        exit(EXIT_FAILURE);
    }

    result.resize(r1, vector<int64_t>(c2, 0)); 
  
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}

vector<vector<int64_t>> inverseMat(vector<vector<int64_t>>& matrix){
    vector<vector<int64_t>> inverted_matrix(matrix.size(), vector<int64_t>(matrix[0].size(), 0));

    inverted_matrix[0][0] = matrix[1][1];
    inverted_matrix[0][1] = matrix[0][1] * -1;
    inverted_matrix[1][0] = matrix[1][0] * -1;
    inverted_matrix[1][1] = matrix[0][0];

    return inverted_matrix;
}

float calculateDet(int64_t a, int64_t b, int64_t c, int64_t d){
    return ((a*d) - (b*c)); 
}


int main() {
    string input_filename = "input.txt";
    ifstream inputFile(input_filename);

    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file " << input_filename << endl;
        return 1;
    }

    vector<vector<vector<int64_t>>> input;
    vector<vector<vector<int64_t>>> output;

    regex digit_pattern("\\d+");

    string line;
    while (getline(inputFile, line)) {
        if (line.find("Button A") != string::npos) {
            vector<vector<int64_t>> layer_input(2, vector<int64_t>(2, 0));
            vector<vector<int64_t>> layer_output(2, vector<int64_t>(1, 0));

            // Parse Button A
            vector<int64_t> button_a;
            auto digits_begin = sregex_iterator(line.begin(), line.end(), digit_pattern);
            auto digits_end = sregex_iterator();
            for (auto it = digits_begin; it != digits_end; ++it) {
                smatch match = *it;
                button_a.push_back(stoll(match.str()));
            }
            layer_input[0][0] = button_a[0];
            layer_input[1][0] = button_a[1];

            // Parse Button B
            getline(inputFile, line);
            vector<int64_t> button_b;
            digits_begin = sregex_iterator(line.begin(), line.end(), digit_pattern);
            digits_end = sregex_iterator();
            for (auto it = digits_begin; it != digits_end; ++it) {
                smatch match = *it;
                button_b.push_back(stoll(match.str()));
            }
            layer_input[0][1] = button_b[0];
            layer_input[1][1] = button_b[1];

            // Parse Prize
            getline(inputFile, line);
            vector<int64_t> prize;
            digits_begin = sregex_iterator(line.begin(), line.end(), digit_pattern);
            digits_end = sregex_iterator();
            for (auto it = digits_begin; it != digits_end; ++it) {
                smatch match = *it;
                prize.push_back(stoll(match.str()));
            }
            layer_output[0][0] = prize[0];
            layer_output[1][0] = prize[1];

            // Add to input and output vectors
            input.push_back(layer_input);
            output.push_back(layer_output);
        }
    }

    int64_t sum = 0;
    for(size_t i = 0; i < input.size(); ++i){
        vector<vector<int64_t>> a = input[i];
        vector<vector<int64_t>> aminus1 = inverseMat(a);
        int64_t det = calculateDet(a[0][0], a[0][1], a[1][0], a[1][1]);
        vector<vector<int64_t>> result = mulMat(aminus1, output[i]);
        int64_t x = result[0][0] / det;
        int64_t y = result[1][0] / det;
        if(x > 100 || y > 100 || result[0][0] % det != 0 || result[1][0] % det != 0){
            continue;
        }
        sum += (x*3) + y;
    }

    cout << "Part one answer: " << sum;
    return 0;
}
