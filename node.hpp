#ifndef __NODE_H__
#define __NODE_H__

#include <ostream>

namespace node {
    template <typename T>
    struct Node {
        T data;
        Node<T>* lhv;
        Node<T>* rhv;
        Node<T>* parent;
        Node(T value): data{value}, lhv{nullptr}, rhv{nullptr}, parent{nullptr} {}
    };

    template <typename T>
    std::ostream& operator<< (std::ostream& os, Node<T>* node) {
        os<<"{"<<node->data<<"}";
        return os;
    }

    template<typename T, typename F>
    void visit_postfix(Node<T> *root, F fn) {
        if (root) {
            visit_postfix(root->lhv, fn);
            visit_postfix(root->rhv, fn);
            fn(root);
        }
    }

    template<typename T, typename F>
    void visit_prefix(Node<T> *root, F fn) {
        if (root) {
            fn(root);
            visit_prefix(root->lhv, fn);
            visit_prefix(root->rhv, fn);
        }
    }

    template<typename T, typename F>
    void visit_infix(Node<T> *root, F fn) {
        if (root) {
            visit_infix(root->lhv, fn);
            fn(root);
            visit_infix(root->rhv, fn);
        }
    }

    template<typename T>
    size_t height(Node<T>* root) {
        return root ? (1 + std::max(height(root->lhv), height(root->rhv))) : 0;
    }

    template<typename T>
    size_t deep(Node<T>* node) {
        return node ? (1 + deep(node->parent)) : 0;
    }

    template<typename T>
    size_t get_length(const T& value) {
        std::stringstream ss;
        ss<<value;
        return ss.str().length();
    }
}

#endif