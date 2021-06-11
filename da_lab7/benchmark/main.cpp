#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using TDuration = chrono::microseconds;

const int MAX = 1e7;

int Min(int a, int b, int c) {
    return (min(a, b) < min(b, c)) ? min(a, b) : min(b,c);
}

int NaiveAlgorithm(int n) {
    int first, second, third;
    if (n == 1) { // end of search condition
        return 0;
    }

    if (n % 2 == 0){
        second = NaiveAlgorithm(n / 2);
    } else {
        second = MAX + 1; // +infinity
    }

    if (n % 3 == 0){
        third = NaiveAlgorithm(n / 3);
    } else {
        third = MAX + 1; // +infinity
    }
    
    first = NaiveAlgorithm(n - 1);

    return Min(first, second, third) + n;
}

int main() {
    int n;
    cin >> n;

    chrono::time_point<chrono::system_clock> start, end;
    int64_t dynamicProgrammingTS = 0, naiveAlgorithmTS = 0;
    start = chrono::system_clock::now();

    int * memento = new int [n + 1];

    // go from 0 to n and find shortest path to every number
    memento[0] = 0;
    memento[1] = 0;
    for (int i = 2; i <= n; i++) {
        // if current number can be divided by 2 and 3 
        if (i % 2 == 0 && i % 3 == 0) {
            // then we choose best option by value from 3 previous points 
            memento[i] = i + Min(memento[i / 2], memento[i / 3], memento[i - 1]);
            continue;
        }
        // if current number can be divided only by 3 
        if (i % 3 == 0) {
            // then choose best option from 2 previous points
            if (memento[i / 3] < memento[i - 1]) {
                memento[i] = i + memento[i / 3];
            } else {
                memento[i] = i + memento[i - 1];
            }
            continue;
        }
        // if current number can be divided only by 2 
        if (i % 2 == 0) {
            // then choose best option from 2 previous points
            if (memento[i / 2] < memento[i - 1]) {
                memento[i] = i + memento[i / 2];
            } else {
                memento[i] = i + memento[i - 1];
            }
            continue;
        }
        // we get here if current number can't be divided by 2 or 3, so there is only one previous point to choose
        memento[i] = i + memento[i - 1];
    }

    // displays value of the shortest path from 1 to n
    cout << memento[n] << endl;

    delete[] memento;

    end = chrono::system_clock::now();
    dynamicProgrammingTS += chrono::duration_cast<TDuration>(end - start).count();
    cout << "Time of Dynamic Programming method: " << dynamicProgrammingTS << " ms" << endl;

    start = chrono::system_clock::now();

    int naiveAnswer = NaiveAlgorithm(n);
    cout << naiveAnswer << endl;

    end = chrono::system_clock::now();
    naiveAlgorithmTS += chrono::duration_cast<TDuration>(end - start).count();
    cout << "Time of Naive Algorithm: " << naiveAlgorithmTS << " ms" << endl;
        
    return 0;
}