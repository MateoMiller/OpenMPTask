#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <omp.h>

using namespace std;

string readFile(const string& filename) {
    ifstream file(filename, ios::in | ios::binary);
    stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

bool isPalindrome(const string& str) {
    for (size_t i = 0; i < str.size() / 2; ++i) {
        if (str[i] != str[str.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

vector<string> nonParallel(const string& text) {
    vector<string> palindromes;
    for (int start = 0; start < text.size(); ++start) {
        for (int length = 1; start + length <= text.size(); ++length) {
            string substr = text.substr(start, length);
            if (isPalindrome(substr)) {
                palindromes.push_back(substr);
            }
        }
    }

    return palindromes;
}

vector<string> parallel(const string& text) {
    vector<string> palindromes;
    #pragma omp parallel for
    for (int start = 0; start < text.size(); start++) {
        for (int length = 1; start + length <= text.size(); length++) {
            string substr = text.substr(start, length);
            if (isPalindrome(substr)) {
                #pragma omp critical
                palindromes.push_back(substr);
            }
        }
    }

    return palindromes;
}


int main() {

    string text = readFile("C:\\Users\\yurii\\CLionProjects\\OpenMPTask\\input.txt");

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();
    vector<string> palindromesParallel = parallel(text);
    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::milliseconds duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
    cout << "Parallel Function execution time: " << duration.count() << " milliseconds" << endl;

    startTime = chrono::steady_clock::now();
    vector<string> palindromesNonParallel = nonParallel(text);
    endTime = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
    cout << "Non parallel function execution time: " << duration.count() << " milliseconds" << endl;

    return 0;
}
