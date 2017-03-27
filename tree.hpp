#ifndef __TREE_H__
#define __TREE_H__

namespace tree {

    template <typename T>
    struct Node {
        T data;
        Node<T>* lhv;
        Node<T>* rhv;
        Node(T value): data{value}, lhv{nullptr}, rhv{nullptr} {}
    };

    template <typename T>
    struct Tree {
        Node<T>* root;

        Tree(): root{nullptr} {
        }

        ~Tree() { 
            visit_postfix(root, [](Node<T>* node){delete node;});
        }

        void insert(const T &value) {
            insert(root, new Node<T>(value));
        }

        void insert(Node<T>* &root, Node<T>* node) {
            if (!root) {
                root = node;
            } else if (root->data > node->data) {
                insert(root->lhv, node);
            } else {
                insert(root->rhv, node);
            }
        }
    };

    template<typename T>
    void balance(Node<T>* &root) {
        if (root->lhv && root->lhv->rhv && root->lhv->rhv->data > root->lhv->data) {
            Node<T>* top = root->lhv->rhv;
            Node<T>* left = root->lhv;
            Node<T>* right = root;
            root = top;
            root->lhv = left;
            root->rhv = right;
            left->rhv = nullptr;
            right->lhv = nullptr;
        }
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
}


#endif