//iterator
#ifndef __iterator_hpp__
#define __iterator_hpp__

#include "ap_error.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "bst.hpp"
#include "node.hpp"

template<typename node_type,typename O>
class _iterator{
    node_type* current;

public:
    //ctor
    explicit _iterator(node_type* x) noexcept : current{x} {}

    using value_type = O;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    // OVERLOADING
    reference operator*() const noexcept { return current->value;}
    pointer operator->() const noexcept { return &(*(*this)); } 

    //returns a new iterator (class reference)
    _iterator& operator++() noexcept {
    //find the  next and put the pointer in current
    return *this;
    }
    _iterator operator++(int) noexcept {
    //find the  next and put the pointer in current
    return *this;
    }
    friend bool operator==(const _iterator& a, const _iterator& b) {
    return a.current == b.current;
    }
    friend bool operator!=(const _iterator& a, const _iterator& b) {
    return !(a == b);
    }

    void go_left(){
        current=current->left.get();
    }    

    _iterator go_right(){
        current=current->right.get();
        return *this;
    }

    bool is_leaf(){
        if (current->left.get()==nullptr && current->right.get()==nullptr){
            return true;
        } else {
            return false;
        }
    }
   
   node_type* get_pointer(){return current;}

};

#endif