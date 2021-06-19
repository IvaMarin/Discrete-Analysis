#ifndef SUFFIXTREE_HPP
#define SUFFIXTREE_HPP

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include "Vertex.hpp"

using namespace std;

class TSuffixTree {
public:
    string pattern;
    string str2;
    Vertex * root, * activeNode, * link;
    int remaining; // amount of suffixies to be created at the current step
    int activeLen; // length of path from current active node
    string::iterator activeEdge; // beginning of an edge from current active node

    struct LCS { // longest common substring
        int length;
        vector <Vertex *> pathToSubs;
        Vertex * beginning;
        Vertex * ending;
    };

    int lengthOfLCS; // stores length of longest common substring 
    vector <LCS> answers;
    LCS ans;

    TSuffixTree(string pattern1, string pattern2); // Constructor that does the whole task 

    void Add(string::iterator symbol); // Ukkonen's algorithm
    void SuffixLink(Vertex *node); // Additional method that handles suffix links
    
    // Additional methods that work with finding longest common substrings and their size  
    int MarkUp(Vertex * node);
    void FindMaxHeight(Vertex * node, int walked);
    void FindLongestSubstrings(Vertex * node, int walked, Vertex * begin, vector <Vertex *> pathToSub);

    ~TSuffixTree(); // Destructor
};

TSuffixTree::TSuffixTree(string pattern1, string pattern2) : remaining(0), activeLen(0), lengthOfLCS(0) {
    this->pattern = pattern1;
    this->str2 = pattern2;
    this->activeEdge = pattern.begin();
    this->root = new Vertex(pattern.end(), pattern.end());
    this->root->suffixLink = this->root;
    this->activeNode = this->root;
    this->link = this->root;

    ans.length = 0;
    ans.beginning = nullptr;
    ans.ending = nullptr;

    // Creating suffix tree
    for (string::iterator symbol = pattern.begin(); symbol != pattern.end(); symbol++) {
        Add(symbol); // adding all the suffixies whith prefix (0, symbol)
    }

    // mark up nodes with numbers corresponding to the first/second/both string(s) 
    MarkUp(root); 

    // do the traversal through nodes that belong to both strings to find length of LCS
    FindMaxHeight(root, 0);

    // Display all the required information
    cout << lengthOfLCS << endl;
}

// Traversal through nodes that belong to both strings to find length of LCS
void TSuffixTree::FindMaxHeight(Vertex * node, int walked) {
    if (node->stringNumber.size() == 2) {
        if (node != root) {
            walked += distance(node->begin, node->end) + 1;
            if (walked > lengthOfLCS) {
                lengthOfLCS = walked;
            }
        }
        for (map<char, Vertex *>::iterator n = node->child.begin(); n != node->child.end(); n++) {
            Vertex * nextChild = n->second;
            FindMaxHeight(nextChild, walked);
        }
    }
}

// DFS traversal to mark up nodes which belong to both strings
int TSuffixTree::MarkUp(Vertex * node) {
    if (node->begin != pattern.end()) {
        if(*node->begin == '#') // if belongs to the first string
            node->stringNumber.insert(1);
        else if(*node->begin == '$') // if belongs to the second string
            node->stringNumber.insert(2);
    }

    if(distance(node->begin, node->end) > 0) {
        int sizeOfString = str2.size();
        if (distance(node->begin, node->end) > sizeOfString) {
            node->stringNumber.insert(1);
        } else if (node->end == pattern.end()) {
            node->stringNumber.insert(2);
        }
    }

    // for loop through all children of the current node
    for (map<char, Vertex *>::iterator it2 = node->child.begin(); it2 != node->child.end(); it2++) {
        Vertex * nextChild = it2->second;
        int ans = MarkUp(nextChild); // 0, 1, 2 or 3
        if (node->stringNumber.size() < 2) {
            if (ans == 3) {
                node->stringNumber.insert(1);
                node->stringNumber.insert(2);
            }
            if (ans == 1) {
                node->stringNumber.insert(1);
            }
            if (ans == 2) {
                node->stringNumber.insert(2);
            }
        }
    }

    if (node->stringNumber.size() == 2) {
        return 3;
    }
    if (node->stringNumber.size() == 1) {
        if(*node->stringNumber.begin() == 1) {
            return 1;
        }
        if(*node->stringNumber.begin() == 2) {
            return 2;
        }
    }
    return 0;
}

void TSuffixTree::Add(string::iterator symbol) {
    link = root; // default link
    remaining++; // amount of suffixes to be created

    while (remaining > 0) { // loop for the current phase (prefix)

        if (!activeLen) { //if we are starting from root
            activeEdge = symbol;
        }
        
        // set iterator to the edge from current node to the child by active edge
        map <char, Vertex *>::iterator it1 = activeNode->child.find(* activeEdge);

        if (it1 == activeNode->child.end()) { // if there is no such edge (part of Rule 2 extention)
            Vertex * newLeaf = new Vertex(symbol, pattern.end()); // create new leaf
            activeNode->child[*activeEdge] = newLeaf; // set as a child of an active node
            SuffixLink(activeNode);
        } else { // if edge was found
            Vertex * next = it1->second; // sets next to the vertex the we'll reach by this edge
            int edgeLength = next->end - next->begin + 1;

            if (activeLen >= edgeLength) { // move through internal node
                activeEdge += edgeLength;
                activeLen -= edgeLength;
                activeNode = next; // and update the active node
                continue;
            }

            // Rule 3 extention (already exists)
            if (*(next->begin + activeLen) == *symbol) {
                activeLen++;
                SuffixLink(activeNode);
                // we will go the next phase immediately and for now leave tree implicit
                break;
            }

            // Rule 2 extention (add the path and create new internal node)
            Vertex * split = new Vertex(next->begin, next->begin + activeLen - 1); // create new internal node
            Vertex * leaf = new Vertex(symbol, pattern.end()); // create new leaf node
            activeNode->child[* activeEdge] = split; // set new internal node as a child of previous interanl node (or root)
            split->child[* symbol] = leaf; // set new leaf as a child of new internal node
            next->begin += activeLen; // update beginning for the splitted part
            split->child[* next->begin] = next; // set splitted part as a child of new internal node 
            SuffixLink(split);
        }

        // at this point we created a leaf so we decrement the counter 
        remaining--;

        // we are at the root but we still have things to do
        if (activeNode == root && activeLen != 0){
            activeLen--; // see it as jump back
            activeEdge++; // and corresponding jump forth
        } else {
            if (activeNode->suffixLink) { // if inner vertex has suffix link
                activeNode = activeNode->suffixLink; // then follow the link 
            } else {
                activeNode = root;
            }
        }

    }
}

void TSuffixTree::SuffixLink(Vertex * node) {
    if (link != root)
        link->suffixLink = node; // create suffix link
    link = node; // remember the inner node
}

TSuffixTree::~TSuffixTree() {
    delete root;
}

#endif /* SUFFIXTREE_HPP */