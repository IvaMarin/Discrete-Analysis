#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP


#include <algorithm>
#include <string>
#include <vector>
#include <map>

void BadCharRule(const std::vector<std::string> &pattern, std::map<std::string, int> &badChar) { 
    // mapping each letter in pattern to its rightmost position
    for (int i = 0; i < (int)(int)pattern.size() - 1; ++i) { // loop to penultimate letter, last letter by default is one position shift
        badChar[pattern[i]] = i;
    }
}

void GoodSuffixRule(const std::vector<std::string> &pattern, std::vector<int> &goodSuff) {
    int m = (int)pattern.size(); // pattern size
    int left = 0;
    int right = 0;
   
    std::vector<int> zFunction(m, 0); // Z-function for reversed pattern (a.k.a. N-function)
    for (int i = 1; i < m; ++i) {
        if (i <= right) {
            // current position is inside rightmost Z-block
            zFunction[i] = std::min(right - i + 1, zFunction[i - left]);
        }

        // increasing z-function if Z-block right bound equals i + Z-function 
        while (i + zFunction[i] < m && (pattern[m - 1 - zFunction[i]] == pattern[m - 1 - (i + zFunction[i])])) {
            zFunction[i]++;
        }

        if (i + zFunction[i] - 1 > right) {
            // we should update coords of rightmost Z-block
            left = i; // left bound
            right = i + zFunction[i] - 1; // right bound
        }
    }

    // N-function
    std::vector<int> N(zFunction.rbegin(), zFunction.rend());

    // L-function (if there is another occurence of suffix)
    int j = 0;
    for (int i = 0; i < m - 1; ++i) {
        j = m - N[i];
        goodSuff[j] = i;
    }

    // l-function (if there is no another occurence of suffix)
    std::vector<int> l(m + 1, m);
    for (int i = m - 1; i >= 0; i--) { // moving from right to left
        j = m - i; // calculate length of suffix
        if (N[j - 1] == j) { // last char of prefix equals first char of suffix
            l[i] = (j - 1); // sync
        } else {
            l[i] = l[i + 1]; // sync previous biggest value
        }
    }

    // use l-function in case we don't have another occurence of suffix
    for (int i = 0; i < m + 1; ++i) {
        if (goodSuff[i] == m){
            goodSuff[i] = l[i];
        }
    }

    // correct value for the shift
    for (int i = 0; i < goodSuff.size(); ++i) {
        if (goodSuff[i] != m){
            goodSuff[i] = m - 1 - goodSuff[i];
        }
    }
}


#endif //PREPROCESSING_HPP