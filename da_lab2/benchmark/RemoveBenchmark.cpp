#include <iostream>
#include <map>
#include <chrono>

#include "bavl.hpp"

using duration_t = std::chrono::nanoseconds;

int main() {
    std::map<char, uint32_t> rb_tree;
    TAVLTree<int, int> avl_tree;
    char action;
    char key;
    uint32_t value;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t rb_ts = 0, avl_ts = 0;
    while( std::cin >> action ) {
        if( action == '+' ) {
            std::cin >> key >> value;
            {
                start = std::chrono::system_clock::now();
                rb_tree.erase( {key} );
                end = std::chrono::system_clock::now();
                rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();

            }
            {
                start = std::chrono::system_clock::now();
                avl_tree.Delete( key );
                end = std::chrono::system_clock::now();
                avl_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        }
    }
    std::cout << "std::map ms=" << rb_ts << "\navl ms=" << avl_ts << std::endl;
}