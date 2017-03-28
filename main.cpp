#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <cctype>
#include <condition_variable>
#include <future>
#include <functional>

#include <cmath>
#include <iomanip>
#include <map>
#include <list>
#include <algorithm>


#include "tree.hpp"

using namespace std;
using namespace tree;

template <typename T>
class Printer {
    std::weak_ptr<Tree<T>> weak_tree;

public:
    Printer(std::weak_ptr<Tree<T>> tree): weak_tree{tree} { };

    void operator()() {
        std::map<size_t, std::list<Node<T>*>> leafs;
        if (auto tree = weak_tree.lock()) {
            visit_prefix(tree->root, [&](decltype(tree->root) node) { 
                size_t d = deep(node);
                leafs.emplace(d, std::list<Node<T>*>());
                leafs[d].push_back(node);
            });

            const size_t height = tree::height(tree->root);
            const std::string header = std::string(std::pow(2, height),'=');
            std::cout<<header<<"\n";
            for (auto& pair: leafs) {
                size_t level = pair.first;
                std::list<Node<T>*> nodes = pair.second;
                const size_t points = std::pow(2, height - level);
                const std::string small(points, ' ');
                const std::string big(2 * points - 1, ' ');
                bool first = true;
                for(auto &node: nodes) {
                    std::cout<<(first ? small : big);
                    if (first)
                        first = false;
                    std::cout<<node->data;
                }
                std::cout<<"\n";
            }
            std::cout<<header<<"\n";
        }
    }
};


int main() {

    auto tree = make_shared<Tree<char>>();

    Printer<char> print(tree);
    
    for(auto value: {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o'}) {        
        tree->insert(value);
        print();
    }

    visit_infix(tree->root, [](decltype(tree->root) node) { std::cout<<"("<<node->data<<")"; } );
    std::cout<<"\n";

    print();

    return 0;
}