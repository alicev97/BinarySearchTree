// BST
#ifndef __bst_hpp__
#define __bst_hpp__

#include "ap_error.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "node.hpp"
#include "iterator.hpp"

template<typename kT, typename vT, typename cmp = std::less<kT>>
class bst{
    using node_type = Node<std::pair<const kT, vT>>;
    using pair_type = std::pair<const kT, vT>;

    //variables
    std::unique_ptr<node_type> head=NULL;
public:
    //ctors and destructor
    bst() = default;
    ~bst() = default;
    //ctom ctor with key and value, calls the node ctor
    //bst(kT a,vT b): head{std::unique_ptr<node_type>(&Node<pair_type>{std::pair<kT,vT>(a,b)})}{}
    bst(kT a, vT b) {
        head.reset(new node_type(pair_type(a,b)));
    }
    // copy semantic

    // move semantic

    //iterators
    using iterator = _iterator<node_type,pair_type>;
    using const_iterator = _iterator<node_type, const pair_type>;
    
    // functions
    // insert
    std::pair<iterator,bool> insert(const pair_type& x);
    std::pair<iterator,bool> insert(pair_type&& x);

    // emplace
    template<class... Types>
    std::pair<iterator,bool> emplace(Types&&... args);

    // clear
    void clear();

    // begin
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    // end
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    // find
    iterator find(const kT& x);
    const_iterator find(const kT& x) const;

    // balance
    void balance();

    // operator overloading 
    vT& operator[](const kT& x);
    vT& operator[](kT&& x);

    //friend std::ostream& operator<<(std::ostream& os, const bst& x);

    // erase
    void erase(const kT& x);

    // other useful functions
    //returns a reference to the pair of the head
    iterator get_head(){return iterator{head.get()};} 
    iterator get_new_parent(pair_type x);
    
};

template<typename kT, typename vT, typename cmp>
typename bst<kT, vT, cmp>::iterator bst<kT, vT, cmp>::get_new_parent(typename bst<kT, vT, cmp>::pair_type x){
    
    kT key=x.first;
    //tmp is an iterator pointing to head and then 
    iterator tmp{this->get_head()};
    
    // while tmp is not a null ptr
    while (tmp.is_leaf()==false){
    if (key < tmp->first){
        tmp.go_left();
        //std::cout << "left" << std::endl;
    } else if (key > tmp->first){
        tmp.go_right();
        //std::cout << "right" << std::endl;
    } else {
        // if I've found the key
        break;
    }
    }
    return tmp;
}

template<typename kT,typename vT, typename cmp>
std::pair<typename bst<kT,vT,cmp>::iterator,bool> bst<kT,vT,cmp>::insert(const bst<kT,vT,cmp>::pair_type& x){
    //find my parent
    auto p = (*this).get_new_parent(x);
    
    if (x.first == p->first){
        std::cout << "this key already exists:" << std::endl;
        std::cout << p->first << ";" << p->second << std::endl;
        std::cout << "but I change the value:"<< std::endl;
        p->second=x.second;
        std::cout << p->first << ";" << p->second << std::endl;
        std::pair<iterator,bool> result(p,false);
        return result;
    } else {
        node_type* parent = p.get_pointer();
        if (x.first > p->first){
            parent->add_right(x);
            iterator it{parent->right.get()};
            std::pair<iterator,bool> result(it,true);
            return result;
        } else {
            parent->add_left(x);
            iterator it{parent->left.get()};
            std::pair<iterator,bool> result(it,true);
            return result;
        }
        
        
    }
    
}

#endif
