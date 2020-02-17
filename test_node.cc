#include "ap_error.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "node.hpp"

int main(){

    try{

    using coppia = std::pair<int, int>;
    using nodo = Node<coppia>;

    // ctor
    nodo n1{}; // default
    std::cout << "n1{} default ctor:\n" << n1 << std::endl;
    nodo n2{coppia (19,8)}; // custom 1
    std::cout << "n2{coppia (19,8)} custom ctor 1:\n" << n2 << std::endl;
    nodo n3{coppia (20,4), &n2}; // custom 2
    std::cout << "n3{coppia (20,4), &n2} custom ctor 2:\n" << n3 << std::endl;

    nodo n4{n3}; // copy ctor
    std::cout << "n4{n3} copy ctor:\n" << n4 << std::endl;

    // you cannot modify a const so let's try w/ int
    using coppia2 = std::pair<int, int>;
    using nodo2 = Node<coppia2>;

    nodo2 n5{coppia2(7,9)};
    nodo2 n6{coppia2(8,6)};
    n5 = n6; // copy assignment 
    std::cout << "n5 = n6 copy assignment:\n" << n5 << std::endl;
    nodo2 n7{nodo2{coppia2(7,9)}}; // move ctor
    std::cout << "n7{nodo2{coppia2(7,9)}} move ctor:\n" << n7 << std::endl;
    n7 = nodo2{coppia2(20,4)}; // move assignment
    std::cout << "n7 = nodo2{coppia2(20,4)} move assignment:\n" << n7 << std::endl;

    // add_child()
    std::cout << "\nadd_child() test\n"<< std::endl;
    nodo* p1{new nodo{coppia(10,5)}};
    nodo* p2{new nodo{coppia(18,4)}};
    nodo* p3{new nodo{coppia(7,9)}};
    p1->add_child(p2, std::less<const int>());
    p2->add_child(p3, std::greater<const int>());
    std::cout << *p1 << std::endl;
    std::cout << *p2 << std::endl;
    std::cout << *p3 << std::endl;
    delete p1;


    } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
    } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
    return 2;
    }
}