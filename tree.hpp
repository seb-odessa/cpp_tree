#ifndef __TREE_H__
#define __TREE_H__

#include <cmath>
#include <iomanip>
#include <map>
#include <list>
#include <sstream>
#include <algorithm>
#include <ostream>

#include "node.hpp"

namespace tree {
    using namespace node;

    template <typename T>
    struct Tree {
        Node<T>* root;

        Tree(): root{nullptr} {
        }

        ~Tree() { 
            visit_postfix(root, [](Node<T>* node){delete node;});
        }

        void insert(const T &value) {
            //std::cout<<"Tree insert("<<value<<")\n";
            insert(root, new Node<T>(value));
        }

        void insert(Node<T>* &root, Node<T>* node) {                        
            if (!root) {
                root = node;
            } else if (root->data > node->data) {
                node->parent = root;
                insert(root->lhv, node);
                Node<T>* a = root;
                Node<T>* b = root->lhv;
                Node<T>* c = b ? b->rhv : nullptr;               
                Node<T>* m = (c && c->lhv) ? c->lhv : nullptr;
                Node<T>* n = (c && c->rhv) ? c->rhv : nullptr;

                const size_t L = height(b->lhv);    
                const size_t C = height(b->rhv);
                const size_t R = height(a->rhv);
                const size_t B = 1 + std::max(L, C);

                if (2 == (B - R)) {
                    if (C <= L) {
                        //std::cout<<"small_right_rotate("<<a->data<<", "<<b->data<<")\n";
                        a->lhv = b->rhv;
                        b->rhv = a;

                        b->parent = a->parent;
                        a->parent = b;
                        if (c) c->parent = a;
                        root = b;
                    } else {
                        //std::cout<<"big_right_rotate("<<a->data<<", "<<b->data<<", "<<c->data<<")\n";
                        const size_t M = height(c->lhv);
                        const size_t N = height(c->rhv);
                        const size_t C = 1 + std::max(M, N);

                        a->lhv = c->rhv;
                        b->rhv = c->lhv;
                        c->rhv = a;
                        c->lhv = b;

                        c->parent = a->parent;
                        a->parent = c;
                        b->parent = c;
                        if (m) m->parent = b;
                        if (n) n->parent = a;
                        root = c;
                    }
                }
            } else if (root->data < node->data) {
                node->parent = root;
                insert(root->rhv, node);
                Node<T>* a = root;
                Node<T>* b = root->rhv;
                Node<T>* c = b ? b->lhv : nullptr;
                Node<T>* m = (c && c->lhv) ? c->lhv : nullptr;
                Node<T>* n = (c && c->rhv) ? c->rhv : nullptr;

                const size_t L = height(a->lhv);    
                const size_t C = height(b->lhv);
                const size_t R = height(b->rhv);
                const size_t B = 1 + std::max(C, R);

                if (2 == (B - L)) {
                    if (C <= R) {
                        //std::cout<<"small_left_rotate("<<a->data<<", "<<b->data<<")\n";
                        a->rhv = b->lhv;
                        b->lhv = a;

                        b->parent = a->parent;
                        a->parent = b;
                        if (c) c->parent = a;

                        root = b;
                    } else {
                        //std::cout<<"big_left_rotate("<<a->data<<", "<<b->data<<", "<<c->data<<")\n";                        
                        const size_t M = height(c->lhv);
                        const size_t N = height(c->rhv);
                        const size_t C = 1 + std::max(M, N);

                        a->rhv = c->lhv;
                        b->lhv = c->rhv;
                        c->lhv = a;
                        c->rhv = b;

                        c->parent = a->parent;
                        a->parent = c;
                        b->parent = c;
                        if (m) m->parent = a;
                        if (n) n->parent = b;
                        root = c;
                    }
                }
            }            
        }
    };

    template <typename T>
    std::ostream& operator<< (std::ostream& os, Tree<T>* tree) {
        std::map<size_t, std::list<Node<T>*>> levels;
        if (!tree || !tree->root)
            return os;
    
        size_t length = 0;
        visit_prefix(tree->root, [&](decltype(tree->root) node) { 
            const size_t d = node::deep(node);
            length = std::max(length, get_length(node->data));
            levels.emplace(d, std::list<Node<T>*>());
            levels[d].push_back(node);
        });

        const size_t height = tree::height(tree->root);
        for (auto& pair: levels) {
            size_t level = pair.first;
            std::list<Node<T>*> nodes = pair.second;
            const size_t pos_width = length + 2;
            const size_t points = std::pow(2, height - level) * pos_width;
            const std::string left_tab(points, ' ');
            const std::string right_tab(points - pos_width, ' ');
            for(auto &node: nodes) {
                os<<left_tab<<"["<<std::setw(length)<<node->data<<"]"<<right_tab;
            }
            os<<"\n";
        }
        return os;
    }

}


#endif