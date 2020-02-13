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
    using node_type = Node<std::pair<const kT,vT>>;
    using pair_type = std::pair<const kT, vT>;

    //variables
    std::unique_ptr<node_type> head=NULL;
    cmp op;

public:
    //ctors and destructor
    bst() = default;
    ~bst() noexcept = default;
    //ctom ctor with key and value, calls the node ctor
    explicit bst(kT a,vT b): head{std::make_unique<node_type>(pair_type(a,b))}{}
    explicit bst(kT a, vT b, const cmp& o): head{std::make_unique<node_type>(pair_type(a,b))}, op{o} {}

    // copy semantic

    // move semantic

    //iterators
    using iterator = _iterator<node_type,pair_type>;
    using const_iterator = _iterator<node_type, const pair_type>;
    
    // functions
    // insert
    //std::pair<iterator,bool> insert(const pair_type& x);
    template<typename OT>
    std::pair<iterator,bool> insert(OT&& x);

    // emplace
    template<class... Types>
    std::pair<iterator,bool> emplace(Types&&... args);

    // clear
    void clear();
    
    // begin
    iterator begin(){
        iterator tmp{head.get()};
        while(tmp.get_pointer()->left.get() != nullptr){
            tmp.go_left();
        }
        return tmp;
    }

    const_iterator begin() const{
        const_iterator tmp{head.get()};
        while(tmp.get_pointer()->left.get() != nullptr){
            tmp.go_left();
        }
        return tmp;
    }

    const_iterator cbegin() const{
        const_iterator tmp{head.get()};
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
    template<typename OT>
    vT& operator[](OT&& x);

    template<typename KT,typename VT,typename CMP>
    friend std::ostream& operator<<(std::ostream& os, const bst<KT,VT,CMP>& x);

    // erase
    void erase(const kT& x);

    // other useful functions
    //returns a reference to the pair of the head
    iterator get_head(){return iterator{head.get()};} 
    iterator get_new_parent(pair_type x);

    void rebuild_from_vector(std::vector<pair_type> v, std::size_t from,std::size_t to);

};

// insert
template<typename kT,typename vT, typename cmp>
template<typename OT>
std::pair<typename bst<kT,vT,cmp>::iterator,bool> bst<kT,vT,cmp>::insert(OT&& x){
    
    if(head == nullptr){
        head = std::make_unique<node_type>(x);
        iterator it {head.get()};
        std::pair<iterator,bool> result(it,false);
        return result;
    }
    //find my parent
    auto p = (*this).get_new_parent(x);
    node_type* parent = p.get_pointer();


    if (!op(x.first, p->first) && !op(p->first,x.first)){
        parent->value.second = x.second;

        std::pair<iterator,bool> result(p,false);
        return result;
    } else {
        node_type* n{new node_type{x}};
        iterator it{parent->add_child(n)};
        std::pair<iterator,bool> result(it,true);
        return result;
    }
}

template<typename kT,typename vT,typename cmp>
template<class... Types>
std::pair<typename bst<kT,vT,cmp>::iterator,bool> bst<kT,vT,cmp>::emplace(Types&&... args){

    node_type* new_node{new node_type{pair_type{std::forward<Types>(args)...}}};

    if(head == nullptr){
        head.reset(new_node);
        iterator it {head.get()};
        std::pair<iterator,bool> result(it,false);
        return result;
    }

    auto p = (*this).get_new_parent(new_node->value);
    node_type* parent = p.get_pointer();

    if (!op(new_node->value.first, parent->value.first) && !op(parent->value.first, new_node->value.first)){
        parent->value.second = new_node->value.second;

        std::pair<iterator,bool> result(p,false);
        std::cout << "modified an existent node" << std::endl;
        delete new_node;
        return result;
    } else {
        iterator it{parent->add_child(new_node)};
        std::pair<iterator,bool> result(it,true);
        return result;
    }   
}

template<typename kT, typename vT, typename cmp>
void bst<kT, vT, cmp>::clear(){
    iterator it{head.get()};
    while(head != nullptr){
    while (!it.is_leaf()){
    while (it.has_left()){
        it.go_left();
    }
    while(it.has_right()){
        it.go_right();
    }
    }
    if(it.get_pointer() != head.get()){
        it.go_up();
        if (it.has_left()){
            it.get_pointer()->left.release();
        } else{
            it.get_pointer()->right.reset();
        }
    } else{
        head.release();
    }

    }
}


template<typename kT, typename vT, typename cmp>
typename bst<kT,vT,cmp>::iterator bst<kT, vT, cmp>::find(const kT& x) {

    iterator tmp{head.get()};
    while (op(x, tmp->first) || op(tmp->first, x) || !tmp.is_leaf()){
    if (op(x, tmp->first)){
        if (tmp.has_left()){
            tmp.go_left();
        } else { break;}
    } else if (op(tmp->first, x)){

        if (tmp.has_right()){
        tmp.go_right();
        } else {break;}
    } else {
        break;
    }
    }

    if (!op(x, tmp->first) && !op(tmp->first, x)){
    return tmp;
    } else{return end();}
}


template<typename kT, typename vT, typename cmp>
typename bst<kT, vT, cmp>::const_iterator bst<kT, vT, cmp>::find(const kT& x) const{
    const_iterator tmp{head.get()};
    while (op(x, tmp->first) || op(tmp->first, x) || !tmp.is_leaf()){
    if (op(x, tmp->first)){
        if (tmp.has_left()){
            tmp.go_left();
        } else { break;}
    } else if (op(tmp->first, x)){

        if (tmp.has_right()){
        tmp.go_right();
        } else {break;}
    } else {
        break;
    }
    }
    if (!op(x, tmp->first) && !op(tmp->first, x)){
    return tmp;
    } else{return end();}
}

template<typename kT, typename vT, typename cmp>
typename bst<kT, vT, cmp>::iterator bst<kT, vT, cmp>::get_new_parent(typename bst<kT, vT, cmp>::pair_type x){

    iterator tmp{this->get_head()};
    
    while (tmp.is_leaf()==false){

    if (op(x.first, tmp->first)){

        if (tmp.get_pointer()->left.get()!=NULL){
            tmp.go_left();
        } else { break;}
        
    } else if (op(tmp->first, x.first)){

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

template<typename KT,typename VT,typename CMP>
std::ostream& operator<<(std::ostream& os, const bst<KT,VT,CMP>& x){

    auto it = x.begin();
    while (it != x.end()){
        os << it->first << " ";
        ++it;
    }
    os << std::endl;
    return os;
}


template<typename kT, typename vT, typename cmp>
template<typename OT>
vT& bst<kT,vT,cmp>::operator[](OT&& x){

    pair_type p{x,vT{}};
    auto it = find(x);//returns an iterator to the element or an iterator pointing end
    
    if (it == end()){
        std::pair<iterator,bool> result = insert(p);
        return result.first->second;
    } else {
        return it->second;
    }

}

/*
template<typename kT,typename vT,typename cmp>
template<typename T>
Node<T>* rebuild_tree(std::vector<T>& v,){
    
    std::size_t t{v.size()};
    //to be returned
    Node<T>* n{new Node<T>{v[t/2]}};
    bst<kT,vT,cmp> tree{n};
    
    tree.insert(v[t/2]);

    
    
    return n;
}
*/

template<typename kT,typename vT, typename cmp>
void bst<kT,vT,cmp>::balance(){
    // build a vector of pairs
    std::vector<std::pair<const kT,vT>> tmp;
    // fill it
    iterator it = begin();
    std::pair<kT,vT> p;
    while (it != end()){
        p = {it->first,it->second};
        tmp.push_back(p);
        ++it;
    }
    // clear the tree
    clear();
    //rebuld the tree recursively
    std::size_t size{tmp.size()};
    rebuild_from_vector(tmp,0,size-1);

    std::cout << head.get()->value.first << "," << head.get()->value.second << std::endl;
}

template<typename kT, typename vT, typename cmp>    
void bst<kT,vT,cmp>::rebuild_from_vector(std::vector<bst<kT,vT,cmp>::pair_type> v, std::size_t from,std::size_t to){
    
    while (to-from >= 0) {
        std::size_t t{(to+from)/2};

        insert(v[t]);
        rebuild_from_vector(v,from,t-1);
        rebuild_from_vector(v,t+1,to);
    }

}



#endif