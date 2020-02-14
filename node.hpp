//node
#ifndef __node_hpp__
#define __node_hpp__

#include "ap_error.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "bst.hpp"
#include "iterator.hpp"

template <typename T>
struct Node{
    //variables
    T value;
    std::unique_ptr<Node> left=NULL;
    std::unique_ptr<Node> right=NULL;
    Node* parent;
    
    using pair_type = T;

    //ctors and destructor
    Node() noexcept = default;
    explicit Node(T pair): value{pair}, left{nullptr},right{nullptr},parent{nullptr} {}
    explicit Node(T pair, Node* p): value{pair}, parent{p} {}
    ~Node() noexcept = default;

    // copy ctor (just create a node with the same pair?)
    Node(const Node& n): value{n.value} {};
    // move ctor
    Node(Node&& n) noexcept = default;
    // move assignment
    Node& operator=(Node&& n) = default; // do not work bc of the const int, this is why it's not noexcept
    //copy assignment
    Node& operator=(const Node& n); // to be implemented (do not work bc of move assignement)

    //put-to overloading
    friend
    std::ostream& operator<<(std::ostream& os, const Node& n){
        os << "key = " << n.value.first << std::endl;
        os << "value = " << n.value.second << std::endl;
        os << "my address:  " << &n << std::endl;
        os << "pointers: \nparent: " << n.parent << std::endl;
        os << "right child: " << n.right.get() << "\nleft chid: " << n.left.get()<< std::endl;
        return os;
    }

    // change parent pointer
    void set_parent(Node* p){
        parent=p;
    }

    Node* add_child(Node* x){
        if (x->value.first > value.first){
            right.reset(x);
            x->set_parent(this);
            return right.get();
        } else {
            left.reset(x);
            (*x).set_parent(this);
            return left.get();
        }
    }

};

#endif