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
    ~bst() noexcept { std::cout << "bst destructor" << std::endl;};
    //ctom ctor with key and value, calls the node ctor
    explicit bst(kT a,vT b): head{std::make_unique<node_type>(pair_type(a,b))}{}
    
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
    iterator begin(){
        iterator tmp{(*this).get_head()};
        while(tmp.get_pointer()->left.get() != nullptr){
            tmp.go_left();
        }
        return tmp;
    }

    const_iterator begin() const{
        const_iterator tmp{(*this).get_head()};
        while(tmp.get_pointer()->left.get() != nullptr){
            tmp.go_left();
        }
        return tmp;
    }

    const_iterator cbegin() const{
        const_iterator tmp{(*this).get_head()};
        while(tmp.get_pointer()->left.get() != nullptr){
            tmp.go_left();
        }
        return tmp;
    }

    // end
    iterator end(){return iterator{nullptr};}
    const_iterator end() const{return const_iterator{nullptr};}
    const_iterator cend() const{return const_iterator{nullptr};}

    // find
    iterator find(const kT& x);
    const_iterator find(const kT& x) const;

    // balance
    void balance();

    // operator overloading 
    vT& operator[](const kT& x);
    vT& operator[](kT&& x);

    template<typename KT,typename VT,typename CMP>
    friend std::ostream& operator<<(std::ostream& os, const bst<KT,VT,CMP>& x);

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
        if (tmp.get_pointer()->left.get()!=NULL){
            tmp.go_left();
        } else { break;}
        
    } else if (key > tmp->first){
        if (tmp.get_pointer()->right.get()!=NULL){
        tmp.go_right();
        } else {break;}
    } else {
        // if I've found the key
        break;
    }
    }
    
    return tmp;
}
/*
template<typename kT,typename vT, typename cmp>
std::pair<typename bst<kT,vT,cmp>::iterator,bool> bst<kT,vT,cmp>::insert(bst<kT,vT,cmp>::pair_type&& x){
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
            // create the node
            node_type n{x};
            //adding the node
            parent->add_right(n);
            iterator it{parent->right.get()};
            std::pair<iterator,bool> result(it,true);
            return result;
        } else {
            node_type n{x};
            parent->add_left(n);
            iterator it{parent->left.get()};
            std::pair<iterator,bool> result(it,true);
            return result;
        }
        
        
    }
}
*/

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
        node_type* n{new node_type{x}};
        node_type* parent = p.get_pointer();
        if (x.first > p->first){
            parent->add_right(n);
            iterator it{parent->right.get()};
            std::pair<iterator,bool> result(it,true);
            return result;
        } else {
            parent->add_left(n);
            iterator it{parent->left.get()};
            std::pair<iterator,bool> result(it,true);
            return result;
        }
        
        
    }
    
}

template<typename KT,typename VT,typename CMP>
std::ostream& operator<<(std::ostream& os, const bst<KT,VT,CMP>& x){

}
#endif
