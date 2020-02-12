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
    using iteratore = _iterator<nodo, coppia>;

    coppia p1{21, 2};
    coppia p2{26, 2};
    coppia p3{25, 16};
    bst<const int, int> a{23, 15};

    // n1 is a pointer to head
    nodo *n1 = a.get_head().get_pointer();

    // insert a left child with const &. n2 pointer to left child
    auto result1 = a.insert(p1);
    nodo *n2 = n1->left.get();
    //insert a right child with &&. n3 pointer to right child
    auto result2 = a.insert(std::pair<const int, int>{25, 16});
    nodo *n3 = n1->right.get();

    // insert a left child of the right child. n4 points to it
    auto result3 = a.emplace(24, 13);
    nodo *n4 = n3->left.get();

    //try std::forward
    //nodo* prova = a.dummy(2,1);

    // print head, left, right
    std::cout << *n1 << std::endl;
    std::cout << *n2 << std::endl;
    std::cout << *n3 << std::endl;
    std::cout << *n4 << std::endl;
}