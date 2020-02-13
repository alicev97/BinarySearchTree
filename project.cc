#include "ap_error.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "bst.hpp"
#include "node.hpp"
#include "iterator.hpp"

int main()
{
    using coppia = std::pair<const int, int>;
    using nodo = Node<coppia>;
    using albero = bst<int, int>;
    using iteratore = albero::iterator;
    using const_iteratore = albero::const_iterator;

    coppia p1{21, 2};
    coppia p2{26, 2};
    coppia p3{25, 16};
    albero a{23, 15};


    // n1 is a pointer to head
    nodo *n1 = a.get_head().get_pointer();

    // insert a left child with const &. n2 pointer to left child
    auto result1 = a.insert(p1);
    nodo *n2 = n1->left.get();
    //insert a right child with &&. n3 pointer to right child
    auto result2 = a.insert(std::pair<const int, int>{26, 16});
    nodo *n3 = n1->right.get();

    // insert a left child of the right child. n4 points to it
    auto result3 = a.emplace(25, 13);
    nodo *n4 = n3->left.get();


    //try std::forward
    //nodo* prova = a.dummy(2,1);

    // print head, left, right
    std::cout << *n1 << std::endl;
    std::cout << *n2;
    std::cout << "is this a new node? " << result1.second << std::endl;
    std::cout << std::endl << *n3;
    std::cout << "is this a new node? " << result2.second << std::endl;
    std::cout << std::endl << *n4;
    std::cout << "is this a new node? " << result3.second << "\n" << std::endl;
    // printing the full tree

    std::cout << a << std::endl;

    //const_iteratore it1 = a.find(23);
    iteratore it2 = a.find(23);
    int g{21};
    std::cout << a[g] << std::endl;
    std::cout << a[23] << std::endl;
    std::cout << a[12] << std::endl;
    
    std::cout << a << std::endl;
    //a.dummy();
    a.balance();
    
}