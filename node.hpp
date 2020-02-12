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
    Node() = default;
    Node(T pair): value{pair}, left{nullptr},right{nullptr},parent{nullptr} {}
    Node(T pair, Node* p): value{pair}, parent{p} {}
    ~Node() noexcept = default;

    // copy ctor (just create a node with the same pair?)
    Node(const Node& n); //to be implemented?
    // move ctor
    Node(Node&& n) noexcept = default;
    // move assignment
    Node& operator=(Node&&) noexcept = default;
    //copy assignment
    Node& operator=(const Node&); // to be implemented?

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

    // add child
    void add_right(T x){
        right.reset(new Node(x,this));
    }
    void add_left(T x){
        left.reset(new Node(x,this));
    }

    // check key
    bool key_equality(Node* p){
        if(p->value.first == value.first){
            return true;
        } else {
            return false;
        }
    }
};

#endif