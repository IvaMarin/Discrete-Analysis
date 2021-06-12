#include <iostream>
#include <string>
#include "SuffixTree.hpp"

using namespace std;

int main() {
    string firstString, secondString;
    while(cin >> firstString >> secondString) {
        firstString += "#";
        secondString += "$";
        firstString += secondString;
        TSuffixTree tree(firstString, secondString);
    }
    return 0;
}