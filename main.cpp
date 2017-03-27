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


int main() {
    using namespace std;
    using namespace tree;
    auto tree = make_shared<Tree<char>>();
    char c;
    while (cin.get(c)) {
        //if (::isalpha(c))
        if (::isdigit(c))
            tree->insert(c);
    }
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    {

        visit_infix(tree->root, [](decltype(tree->root) node) { std::cout<<node->data; } );
        std::cout<<"\n";

        visit_postfix(tree->root, [](decltype(tree->root) root) { std::cout<<root->data; });
        std::cout<<"\n";

        std::cout<<"The tree height: "<<height(tree->root)<<"\n";
    }

    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();

    cout << "\nDuration: " << duration << "\n";
    return 0;
}