#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using TDuration = chrono::microseconds;

struct TClosedInterval {          
    pair<int, int> endpoints;  
    int index;       
};

bool decreasingSecondEndpoint(const TClosedInterval &a, const TClosedInterval &b) {
    return a.endpoints.second > b.endpoints.second;
}

bool compareByOriginalIndex(const TClosedInterval &a, const TClosedInterval &b) {
    return a.index < b.index;
}

int main() {
    chrono::time_point<chrono::high_resolution_clock> start, end;
    int64_t timeStamp = 0;
    start = chrono::high_resolution_clock::now();

    int n; // number of closed intervals
    cin >> n;

    TClosedInterval closedInterval;
    vector<TClosedInterval> closedIntervals; // container for closed intervals

    for (int i = 0; i < n; ++i) { // read N intervals and put them into container
        cin >> closedInterval.endpoints.first >> closedInterval.endpoints.second;
        closedInterval.index = i; // we are also saving original index of interval
        closedIntervals.push_back(closedInterval);
    }

    int m; // right endpoint of [0; M] interval
    cin >> m;

    sort(closedIntervals.begin(), closedIntervals.end(), decreasingSecondEndpoint);
        
    int k = 0; // amount of taken intervals
    vector<TClosedInterval> answer; // container for taken intervals

    bool noAnswer = false;
    int cur = 0; // current rightmost endpoint of covered part of interval
    while (cur < m) { // while we haven't covered whole interval
        auto it = closedIntervals.begin();
        for (; it < closedIntervals.end(); ++it) {
            // if interval starts at current rightmost endpoint of covered part or earlier
            // and ends after it
            if (((*it).endpoints.first  <= cur) && ((*it).endpoints.second > cur)) {
                    answer.push_back(*it); // add interval
                    k++; // increment counter
                    cur = (*it).endpoints.second; // update rightmost endpoint of covered part
                    break; // stop and start looking for the next one
            }
        }
        // iterator will be equal to closedIntervals.end()
        // if only we iterated through all intrevlas and didn't add anything
        if (it == closedIntervals.end()) {
            noAnswer = true; // that means there is no answer
            break;
        } 
    }

    if (noAnswer) {
        cout << 0 << endl;
        
        end = chrono::high_resolution_clock::now();
        timeStamp += chrono::duration_cast<TDuration>(end - start).count();
        cout << "Time: " << timeStamp << " ms" << endl;
        return 0;
    }

    // print minimum amount of intervals necessary to cover interval [0; M]
    cout << k << endl;

    sort(answer.begin(), answer.end(), compareByOriginalIndex);
    
    for (int j = 0; j < k; ++j) { // print taken intervals in their original order
        cout << answer[j].endpoints.first << " " <<  answer[j].endpoints.second << endl;
    }

    end = chrono::high_resolution_clock::now();
    timeStamp += chrono::duration_cast<TDuration>(end - start).count();
    cout << "Time: " << timeStamp << " ms" << endl;
    
    return 0;
}