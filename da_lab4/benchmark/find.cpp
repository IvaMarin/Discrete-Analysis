#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <chrono>

using duration_t = std::chrono::microseconds;


// basically std::tolower
void Lowercase(std::string &str) {
    for (int i = 0; i < (int)str.size(); ++i)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 'a' - 'A';
}

void ReadInput(std::vector<std::string> &pattern, std::vector<std::string> &txt, std::vector<std::pair<int, int>> &positions) {
    // reading pattern
    std::string curLine;
    getline(std::cin, curLine, '\n');

    // splitting pattern-line into words
    std::istringstream stringStream(curLine);
    std::string curWord;
    while (stringStream >> curWord) {
        Lowercase(curWord);
        pattern.push_back(curWord);
    }

    // reading and parsing text into words
    int linePos = 1;
    int columnPos = 0;
    int lineLen;
    int left;
    std::pair<int, int> pos;
    while (getline(std::cin, curLine, '\n')) {
        columnPos = 1;
        lineLen = curLine.size();
        for (int curPos = 0; curPos < lineLen;) {
            if (isalpha(curLine[curPos])) { // if current symbol is a part of alphabet
                left = curPos;
                while (isalpha(curLine[curPos]) && curPos < lineLen)
                    ++curPos;

                pos.first = linePos;
                pos.second = columnPos++;
                positions.push_back(pos);

                curWord = curLine.substr(left, curPos - left);
                Lowercase(curWord);
                txt.push_back(curWord);
            }
            ++curPos;
        }
        ++linePos;
    }
}

int main()  {
 
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t find_ts = 0;

    std::vector<std::string> pattern;
    std::vector<std::string> text;
    // positions[i].first -  i word line, positions[i].second - by which number is this word
    std::vector<std::pair<int, int>> positions;
    ReadInput(pattern, text, positions);

    start = std::chrono::system_clock::now();

    int patternPos, bound = 0, shift = 0;
    for (int textPos = 0; textPos < 1 + text.size() - (int)pattern.size();) {
        for (patternPos = (int)pattern.size() - 1; patternPos >= bound; patternPos--) { // moving from right to left through pattern
            if (pattern[patternPos] != text[textPos + patternPos]) { //character mismatch
                break;
            }
        }
        if (patternPos < bound) { // there is an occurrence
            bound = 0;
            patternPos = -1;
            shift = 1;
        }
        textPos += shift;
    }
    end = std::chrono::system_clock::now();
    find_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
    std::cout << "Naive Algorithm ms=" << find_ts << std::endl;
    return 0;
}