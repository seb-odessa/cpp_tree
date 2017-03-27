#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <cctype>
#include <condition_variable>
#include <future>
#include <functional>

#include "tree.hpp"

using namespace std;
using namespace tree;

int main() {

    auto tree = make_shared<Tree<long>>();
    
    for(auto value: {6,5,3,2,1,7,8,9,0}) {
        tree->insert(value);
    }


    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    {

        visit_prefix(tree->root, [](decltype(tree->root) node) { std::cout<<"("<<node->data<<")"; } );
        std::cout<<"\n";

        std::cout<<"The tree height: "<<height(tree->root)<<"\n";
        std::cout<<"The left subtree height: "<<height(tree->root->lhv)<<"\n";
        std::cout<<"The right subtree height: "<<height(tree->root->rhv)<<"\n";

        visit_infix(tree->root, [](decltype(tree->root) node) { std::cout<<"("<<node->data<<")"; } );
    }

    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();

    cout << "\nDuration: " << duration << "\n";
    return 0;
}