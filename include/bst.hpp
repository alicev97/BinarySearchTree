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
    std::unique_ptr<node_type> head= nullptr;
    cmp op;

public:
    //ctors and dtor
    bst() = default; // default ctor
    ~bst() noexcept = default; // default dtor
    explicit bst(kT a,vT b): head{std::make_unique<node_type>(pair_type(a,b))}{} //ctom ctor (key, value) -> calls the node ctor
    explicit bst(kT a, vT b, const cmp& o): head{std::make_unique<node_type>(pair_type(a,b))}, op{o} {
        std::cout << "with operator" << std::endl;
    } //ctom ctor (key, value, op)

    bst(const bst &b) {head = std::make_unique<node_type>(b.head);}

    bst& operator=(const bst& b){
        head.reset();
        auto tmp = b; // copy ctor
        (*this) = std::move(tmp); // move assignment
        return *this;
    }
    
    // move semantic
    bst(bst&& b) noexcept = default;
    bst& operator=(bst&& b) noexcept = default;

    //iterators
    using iterator = _iterator<node_type,pair_type>;
    using const_iterator = _iterator<node_type, const pair_type>;
    
    // functions

    // insert
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

        if(tmp == end()){ // nullptr
            return tmp;
        }

        while(tmp.get_pointer()->left.get() != nullptr){
            tmp.go_left();
        }
        return tmp;
    }

    const_iterator begin() const{
        const_iterator tmp{head.get()};

       if(tmp == end()){ // nullptr
            return tmp;
        }

        while(tmp.get_pointer()->left.get() != nullptr){
            tmp.go_left();
        }
        return tmp;
    }

    const_iterator cbegin() const{
        const_iterator tmp{head.get()};

        if(tmp == end()){ // nullptr
            return tmp;
        }

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
    void copy_sub_bst(const node_type* b);

};

#endif
#include "bits_bst.hpp"