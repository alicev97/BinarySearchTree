#ifndef __node_hpp__
#define __node_hpp__

#include "ap_error.h"
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
    explicit Node(T pair): value{pair} {} // custom ctor 1
    explicit Node(T pair, Node* p): value{pair}, parent{p} {} // custom ctor 2
    ~Node() noexcept = default; //dtor

    // move semantic
    Node(Node&& n) noexcept = default; // move ctor
    Node& operator=(Node&& n) = default; // move assignment 
    // copy semantic
    Node(const Node& n): value{n.value} {}; // copy ctor
    Node& operator=(const Node& n){ // copy assignment
        auto tmp = n;
        (*this) = std::move(tmp); // qua chiama il copy assignemnt e non il move!! ???
        return *this;
    }

    //put-to overloading
    friend
    std::ostream& operator<<(std::ostream& os, const Node& n) {
        os << "key = " << n.value.first << std::endl;
        os << "value = " << n.value.second << std::endl;
        os << "my address:  " << &n << std::endl;
        os << "pointers: \nparent: " << n.parent << std::endl;
        os << "right child: " << n.right.get() << "\nleft chid: " << n.left.get()<< std::endl;
        return os;
    }

    Node* add_child(Node* x) noexcept {
        // if x is a right child
        if (x->value.first > value.first){
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