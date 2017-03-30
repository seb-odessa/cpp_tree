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

int main() {

    auto tree = std::make_shared<tree::Tree<std::string>>();
   
    for(auto value: {"a","b","c","d","e","f","gg","hh","i","j","k","l","m","n","o"}) {        
        tree->insert(value);
    }

    tree::visit_infix(tree->root, [](decltype(tree->root) node) { std::cout<<node; } );
    std::cout<<"\n";

    std::cout<<tree<<"\n";

    return 0;
}