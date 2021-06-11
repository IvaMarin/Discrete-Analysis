#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int Min(int a, int b, int c) {
    return (min(a, b) < min(b, c)) ? min(a, b) : min(b,c);
}

int main() {
    int n, tmp;

    cin >> n;

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

    // now we go through memento from n to 1 finding lowest values and displaying corresponding operation
    tmp = n;
    while (tmp > 1) {
        // if current number can be divided by 2 and 3
        if ((tmp % 3 == 0) && (tmp % 2 == 0)) {
            // then we choose best option by value from 3 previous points
            if(memento[tmp / 3] <= memento[tmp / 2] && memento[tmp / 3] <= memento[tmp - 1]) {
                cout << "/3" << ' ';
                tmp /= 3;
            }
            else if(memento[tmp / 2] <= memento[tmp / 3] && memento[tmp / 2] <= memento[tmp - 1]) {
                cout << "/2" << ' ';
                tmp /= 2;
            }
            else {
                cout << "-1";
                tmp--;
            }
            continue;
        }
        // if current number can be divided only by 3
        if (tmp % 3 == 0) {
            // then choose best option from 2 previous points
            if (memento[tmp / 3] <= memento[tmp - 1]) {
                cout << "/3" << ' ';
                tmp /= 3;
            } else {
                cout << "-1" << ' ';
                tmp--;
            }
            continue;
        }
        // if current number can be divided only by 2
        if (tmp % 2 == 0) {
            // then choose best option from 2 previous points
            if (memento[tmp / 2] <= memento[tmp - 1]) {
                cout << "/2" << ' ';
                tmp /= 2; 
            } else {
                cout << "-1" << ' ';
                tmp--;
            }
            continue;
        }
        // we get here if current number can't be divided by 2 or 3, so there is only one previous point to choose
        cout << "-1" << ' ';
        tmp--;
    }
    cout << endl;

    delete[] memento;
        
    return 0;
}