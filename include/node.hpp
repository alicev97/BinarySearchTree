#ifndef __node_hpp__
#define __node_hpp__

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

template <typename T>
struct Node{
    //variables
    T value;

    std::unique_ptr<Node> left = nullptr;
    std::unique_ptr<Node> right = nullptr;
    Node* parent = nullptr;


    //ctors and destructor
    Node() noexcept {}; // default ctor
    explicit Node(const T& pair): value{pair} {}
    explicit Node(T&& pair): value{std::move(pair)} {} // custom ctor 1
    explicit Node(T pair, Node* p): value{pair}, parent{p} {} // custom ctor 2
    explicit Node(const std::unique_ptr<Node>& n, Node* p): value{n->value} {
        this->parent=p;
        if (n->left){
            left = std::make_unique<Node>(n->left,this);
        }
        if (n->right){
            right = std::make_unique<Node>(n->right,this);
        }
    }
    ~Node() noexcept = default; //dtor

    
    // move semantic
    Node(Node&& n) noexcept = default; // move ctor
    Node& operator=(Node&& n) noexcept = default; // move assignment

    // copy semantic
    Node(const Node& n): value{n.value} {} // copy ctor
    Node& operator=(const Node& n){ // copy assignment
        auto tmp = n;
        (*this) = std::move(tmp);
        return *this;
    }
    
    //put-to overloading
    friend
    std::ostream& operator<<(std::ostream& os, const Node& n) {
        os << "my address:  " << &n << std::endl;
        os << n.value.first << ";" << n.value.second << std::endl;
        os << "parent: "  << n.parent << std::endl;
        os << "right: " << n.right.get() << "\nleft: " << n.left.get()<< std::endl;
        return os;
    }

    template<typename cmp>
    Node* add_child(Node* x, cmp op) noexcept {
        // if x is a right child
        if (!op(x->value.first,value.first)){ //>
            right.reset(x);
            x->parent=this;
            return right.get();
        } else {
        // if x is a left child
            left.reset(x);
            x->parent=this;
            return left.get();
        }
    }

};

#endif