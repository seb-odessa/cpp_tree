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
            std::cout<<"Tree insert("<<value<<")\n";
            insert(root, new Node<T>(value));
        }

        void insert(Node<T>* &root, Node<T>* node) {            
            if (!root) {
                root = node;
            } else if (root->data > node->data) {
                insert(root->lhv, node);
                Node<T>* a = root;
                Node<T>* b = root->lhv;
                Node<T>* c = root->lhv ? root->lhv->rhv : 0;               
                const size_t L = height(b->lhv);    
                const size_t C = height(b->rhv);
                const size_t R = height(a->rhv);
                const size_t B = 1 + std::max(L, C);

                if (2 == (B - R)) {
                    if (C <= L) {
                        std::cout<<"small_right_rotate("<<a->data<<", "<<b->data<<")\n";
                        a->lhv = b->rhv;
                        b->rhv = a;
                        root = b;
                    } else if (c) {
                        std::cout<<"big_right_rotate("<<a->data<<", "<<b->data<<", "<<c->data<<")\n";
                        const size_t M = height(c->lhv);
                        const size_t N = height(c->rhv);
                        const size_t C = 1 + std::max(M, N);

                        a->lhv = c->rhv;
                        b->rhv = c->lhv;
                        c->rhv = a;
                        c->lhv = b;
                        root = c;
                    }
                }
            } else if (root->data < node->data) {
                insert(root->rhv, node);
                Node<T>* a = root;
                Node<T>* b = root->rhv;
                Node<T>* c = root->rhv ? root->rhv->lhv : 0;               
                const size_t L = height(a->lhv);    
                const size_t C = height(b->lhv);
                const size_t R = height(b->rhv);
                const size_t B = 1 + std::max(C, R);

                if (2 == (B - L)) {
                    if (C <= R) {
                        std::cout<<"small_left_rotate("<<a->data<<", "<<b->data<<")\n";
                        a->rhv = b->lhv;
                        b->lhv = a;
                        root = b;
                    } else if (c) {
                        std::cout<<"big_left_rotate("<<a->data<<", "<<b->data<<", "<<c->data<<")\n";
                        const size_t M = height(c->lhv);
                        const size_t N = height(c->rhv);
                        const size_t C = 1 + std::max(M, N);

                        a->rhv = c->lhv;
                        b->lhv = c->rhv;
                        c->lhv = a;
                        c->rhv = b;
                        root = c;
                    }
                }

            }            
        }
    };



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