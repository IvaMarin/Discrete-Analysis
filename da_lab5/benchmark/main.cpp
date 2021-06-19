#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "SuffixTree.hpp"

using namespace std;
using TDuration = chrono::microseconds;
 
// Returns length of longest common substring of X[0..m-1] and Y[0..n-1] 
int LCSubStr(string X, string Y, int m, int n) {
    // Create a table to store lengths of longest common suffixes of substrings.  
    // Note that LCSuff[i][j] contains length of longest common suffix of X[0..i-1] and Y[0..j-1].
    vector<vector<int>> LCSuff(m + n, vector<int>(m + n));
    int result = 0; // To store length of the longest common substring
 
    // Following steps build LCSuff[m+1][n+1] in bottom up fashion.
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // The first row and first column entries have no logical meaning,
            // they are used only for simplicity of program
            if (i == 0 || j == 0)
                LCSuff[i][j] = 0;
 
            else if (X[i - 1] == Y[j - 1]) {
                LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
                result = max(result, LCSuff[i][j]);
            }
            else
                LCSuff[i][j] = 0;
        }
    }
    return result;
}

int main() {
    string str1, str2;
    cin >> str1; 
    cin >> str2; 
    int m = str1.size();
    int n = str2.size();

    chrono::time_point<chrono::system_clock> start, end;
    int64_t UkkonenTS = 0, dynamicTS = 0;
    
    start = chrono::system_clock::now();
    int dynamicAnswer = LCSubStr(str1, str2, m, n);
    end = chrono::system_clock::now();
    dynamicTS += chrono::duration_cast<TDuration>(end - start).count();
    cout << "Dynamic Programming answer: " << dynamicAnswer << endl;
    cout << "Time of Dynamic Programming method: " << dynamicTS << " microsecond(s)" << endl << endl;

    start = chrono::system_clock::now();
    str1 += "#";
    str2 += "$";
    str1 += str2;
    cout << "Ukkonen's Algorithm answer: ";
    TSuffixTree tree(str1, str2);
    end = chrono::system_clock::now();
    UkkonenTS += chrono::duration_cast<TDuration>(end - start).count();
    cout << "Time of Ukkonen's Algorithm: " << UkkonenTS << " microsecond(s)" << endl;
}