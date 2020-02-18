#ifndef __iterator_hpp__
#define __iterator_hpp__

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "node.hpp"

template<typename node_type,typename O>
class _iterator{

    node_type* current;

public:
    //ctors
    _iterator() noexcept : current(nullptr) {}
    explicit _iterator(node_type* x) noexcept : current{x} {}

    //destructor
    ~_iterator() noexcept = default;

    using value_type = O;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    // OVERLOADING OPERATORS
    reference operator*() const noexcept { return current->value;}
    pointer operator->() const noexcept { return &(*(*this)); } 

    _iterator& operator++() noexcept {
        if (current == nullptr) // check nullptr
            return *this;

        if (current->right != nullptr){
            (*this).go_right();
            while(current->left != nullptr){
                (*this).go_left();
            }
        }
        else {
            if(current->parent == nullptr){
                current = nullptr;
                }
            else{
            while(current->value.first > current->parent->value.first){
                (*this).go_up();
                if(current->parent == nullptr){
                current = nullptr;
                return *this;
                }
            }
            (*this).go_up();
            }
        }

    return *this;
    }
    
    _iterator operator++(int) noexcept {
        _iterator tmp{current};
        ++(*this);
        return tmp;
    }

    friend bool operator==(const _iterator& a, const _iterator& b) {
    return a.current == b.current;
    }
    
    friend bool operator!=(const _iterator& a, const _iterator& b) {
    return !(a == b);
    }

    void go_left() noexcept {if(current != nullptr){current=current->left.get();}}
    void go_right() noexcept {if(current != nullptr){current=current->right.get();}}
    void go_up() noexcept {if(current != nullptr){current = current->parent;}}

    bool is_leaf() const noexcept {
        if(current != nullptr){
        if (current->left.get()==nullptr && current->right.get()==nullptr){
            return true;
        } else {
            return false;
        }
        } else {return false;}
    }

    bool has_left() const noexcept {
        if(current != nullptr){
        if (current->left.get() != nullptr){
            return true;
        } else{
            return false;
        }
        } else {return false;}
    }

    bool has_right() const noexcept {
        if(current != nullptr){
        if (current->right.get() != nullptr){
            return true;
        } else {
            return false;
        }
        } else {return false;}
    }
   
   node_type* get_pointer() noexcept {return current;}

   bool is_left() const noexcept {
       _iterator it2 = *this;
       it2.go_up();
       it2.go_left();
       if (it2==*this){ return true; } else { return false; }
   }

   bool is_right() const noexcept {
       _iterator it2 = *this;
       it2.go_up();
       it2.go_right();
       if (it2==*this){ return true; } else {return false;}
   }

    friend
    std::ostream& operator<<(std::ostream& os, const _iterator& it){
        os << it->first << ";" << it->second;
        return os;
    }
};

#endif