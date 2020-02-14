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
    coppia p2{15, 2};
    coppia p3{11, 16};
    albero a{23, 15};


    // n1 is a pointer to head
    nodo *n1 = a.get_head().get_pointer();

    // insert a left child with const &. n2 pointer to left child
    auto result1 = a.insert(p1);
    nodo *n2 = n1->left.get();
    //insert a right child with &&. n3 pointer to right child
    auto result2 = a.insert(std::pair<const int, int>{15, 16});
    nodo *n3 = n2->left.get();

    // insert a left child of the right child. n4 points to it
    auto result3 = a.emplace(11, 13);
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

    /*
    //const_iteratore it1 = a.find(23);
    iteratore it2 = a.find(23);
    int g{21};
    std::cout << a[g] << std::endl;
    std::cout << a[23] << std::endl;
    std::cout << a[12] << std::endl;
    
    std::cout << a << std::endl;
    //a.dummy();
    */

    ////    CHECK IF BALANCE WORKS  ///////
    /*
    //a.balance();
    
    nodo* n5 = a.get_head().get_pointer();
    nodo* n6 = n5->left.get();
    nodo* n7 = n5->right.get();
    nodo* n8 = n7->right.get();
    //head
    std::cout << *n5 << std::endl;
    std::cout << *n6 << std::endl;
    std::cout << *n7 << std::endl;
    std::cout << *n8 << std::endl;
    */
    
    //////      CHECK IF ERASE WORKS        //////
    //// REMOVE LEAF NODE
    
    //a.erase(11);
    //a.erase(23);
    

    //// REMOVE ONE-CHILD NODE
    //HAS LEFT- IS LEFT
    /*
    a.erase(21);    
    std::cout << a << std::endl;

    n1 = a.get_head().get_pointer();
    n2 = n1->left.get();
    n3 = n2->left.get();
    std::cout << *n1 << std::endl;
    std::cout << *n2 << std::endl;
    std::cout << *n3 << std::endl;
    */

   // HAS LEFT - IS RIGHT
   /*
   albero a2{15,12};
   a2.emplace(20,1);
   a2.emplace(17,54);
   
   n1 = a2.get_head().get_pointer();
   n2 = n1->right.get();
   n3 = n2->left.get();
   std::cout << *n1 << std::endl;
   std::cout << *n2 << std::endl;
   std::cout << *n3 << std::endl;

   a2.erase(20);
   std::cout << a2 << std::endl;
   auto it2=a2.get_head();
   std::cout << it2 << std::endl;
   it2.go_right();
   std::cout << it2 << std::endl;
   */

   // HAS RIGHT - IS RIGHT
   /*
   albero a3{15,12};
   a3.emplace(20,1);
   a3.emplace(27,54);
   
   n1 = a3.get_head().get_pointer();
   n2 = n1->right.get();
   n3 = n2->right.get();
   std::cout << *n1 << std::endl;
   std::cout << *n2 << std::endl;
   std::cout << *n3 << std::endl;

   a3.erase(20);
   std::cout << a3 << std::endl;
   auto it2=a3.get_head();
   std::cout << it2 << std::endl;
   it2.go_right();
   std::cout << it2 << std::endl;
   */
   //HAS RIGHT - IS LEFT
   albero a4{15,12};
   a4.emplace(10,1);
   a4.emplace(13,54);
   
   n1 = a4.get_head().get_pointer();
   n2 = n1->left.get();
   n3 = n2->right.get();
   std::cout << *n1 << std::endl;
   std::cout << *n2 << std::endl;
   std::cout << *n3 << std::endl;
    
   a4.erase(10);
   
   std::cout << a4 << std::endl;
   auto it2=a4.get_head();
   std::cout << it2 << std::endl;
   it2.go_left();
   std::cout << it2 << std::endl;
 

}