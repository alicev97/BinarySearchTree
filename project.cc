#include "ap_error.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "bst.hpp"
#include "node.hpp"
#include "iterator.hpp"

int main(){
    using coppia = std::pair<const int,int>;
    using nodo = Node<coppia>;
    using iteratore=_iterator<nodo,coppia>;

    coppia p1{21,2}; 
    coppia p2{26,2};
    coppia p3{25,16};
    bst<const int, int> a{23,15};

    nodo* n1 = a.get_head().get_pointer();
    //std::cout << *n1 << std::endl;
    //nodo* n2{new nodo{coppia{26,16}}};

    auto result1 = a.insert(p1);
    //auto result2 = a.insert(p2);
    //auto result3 = a.insert({25,16});

    //nodo* n1{new nodo{coppia{23,2}}};
    
    //a.get_head().get_pointer()->add_right(n2);

    //n1->add_left(p1);
    //nodo* n3 = n1->left.get();
    nodo* n2 = n1->left.get();
    //nodo* n4 = n2->left.get();

    std::cout << *n1 << std::endl;
    std::cout << *n2 << std::endl;
   // std::cout << *n3 << std::endl;
    //std::cout << *n4 << std::endl;
    
}