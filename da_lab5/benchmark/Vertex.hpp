#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

class Vertex {
public:
    map<char, Vertex *> child;
    string::iterator begin, end;
    Vertex * suffixLink;
    set<int> stringNumber;
    Vertex(string::iterator begin, string::iterator end) : begin(begin), end(end), suffixLink(nullptr) {};
    ~Vertex();
};

Vertex::~Vertex() {
    for (pair<char, Vertex*> node : child) {
        delete node.second;
    }
}

#endif /* VERTEX_HPP */