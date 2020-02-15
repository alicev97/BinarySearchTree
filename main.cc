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

    ////////////////////////
    /////     NODE     /////
    ///////////////////////

    using coppia = std::pair<const int, int>;
    //using nodo = Node<coppia>;
    /*
    // ctor
    nodo n1{}; // default
    std::cout << n1 << std::endl;
    nodo n2{coppia (20,4)}; // custom 1
    std::cout << n2 << std::endl;
    nodo n3{coppia (20,4), &n2}; // custom 2
    std::cout << n3 << std::endl;

    nodo n4{n3}; // copy ctor
    std::cout << n4 << std::endl;
    nodo n5 {};
    n5 = n4; // copy assignment ??? NON VAA
    std::cout << n5 << std::endl;

    nodo n6{nodo{}}; // move ctor
    std::cout << n6 << std::endl;
    nodo n7 = nodo{coppia (20,4), &n5}; // move assignment ???
    std::cout << n7 << std::endl;

    // add_child()
    nodo* p1{new nodo{coppia(10,5)}};
    nodo* p2{new nodo{coppia(18,4)}};
    nodo* p3{new nodo{coppia(7,9)}};
    p1->add_child(p2);
    p1->add_child(p3);
    std::cout << *p1 << std::endl;
    std::cout << *p2 << std::endl;
    std::cout << *p3 << std::endl;
    delete p1; // ???
    */  

    ////////////////////////
    /////     BST      /////
    ///////////////////////
    using albero = bst<int, int>;

    /*
    // ctors
    albero a {}; // default ctor
    std::cout << a << std::endl;
    albero b{9,4}; // custom ctor 1
    std::cout << b << std::endl;
    //albero c{1,4, std::greater<int>}; ??? come si faaa
    //std::cout << c << std::endl;

    b.insert(coppia(6,10));
    b.emplace(coppia(78, 9));
    albero d{b}; //copy ctor
    std::cout << b << std::endl;
    std::cout << d << std::endl;
    albero e{};
    e=d; // copy assignment
    std::cout<< e << std::endl;

    albero f{albero {3,7}}; // move ctor
    std::cout << f << std::endl;
    albero g = albero{6,7}; // move assignemnt ???
    std::cout << g << std::endl;

    // instet()
    albero a{};
    a.insert(coppia(4,6)); // head nullptr
    std::cout << a << std::endl;
    a.insert(coppia(7,9)); // add a right child
    std::cout << a << std::endl;
    a.insert(coppia(1,8)); // add a left child;
    std::cout << a << std::endl;
    a.insert(coppia(4,9)); // add an existing key
    std::cout << a.get_head() << std::endl;

    // emplace()
    albero a{};
    a.emplace(4,7); // head nullptr
    //std::cout << a << std::endl;
    a.emplace(coppia(7,9)); // add a right child
    //std::cout << a << std::endl;
    a.emplace(coppia(1,8)); // add a left child;
    //std::cout << a << std::endl;
    a.emplace(coppia(4,9)); // add an existing key
    //std::cout << a.get_head() << std::endl;

    // clear()
    a.clear();
    std::cout << a << std::endl;
    albero b{};
    b.clear();

    // begin(), cbegin()
    using iteratore = albero::iterator;
    using const_iteratore = albero::const_iterator;

    iteratore it = a.begin();
    std::cout << it << std::endl;
    albero b{};
    iteratore it2 = b.begin(); // begin on nullptr bst
    std::cout << it2.get_pointer() << std::endl; // non si può stampare direttamente it! ???
    const_iteratore it3 = a.cbegin();
    std::cout << it3 << std::endl;
    const_iteratore it4 = b.cbegin(); // cbegin on nullptr bst
    std::cout << it2.get_pointer() << std::endl; // non si può stampare direttamente it! ???
    // end()
    iteratore it = a.end();
    std::cout << it.get_pointer() << std::endl; // non si può stampare direttamente it! ???
    const_iteratore it2 = a.cend();
    std::cout << it2.get_pointer() << std::endl; // non si può stampare direttamente it! ???

    // find()
    std::cout << a.find(4) << std::endl; // present key
    std::cout << a.find(6).get_pointer() << std::endl; // not present key
    albero b{};
    std::cout << b.find(5).get_pointer() << std::endl; // null bst
    
    // get_new_parent()
    std::cout << a.get_new_parent(coppia(6,9)) << std::endl; // new key
    std::cout << a.get_new_parent(coppia(4,9)) << std::endl; // already present key ???
    albero b{};
    //std::cout << b.get_new_parent(coppia(7,9)).get_pointer() << std::endl; // segmentation fault ???

    // []
    std::cout << a[7] << std::endl; // return the value
    std::cout << a[11] << std::endl; // insert the key w/ value = 0 and retrun the value
    albero b{};
    std::cout << b[9] << std::endl; // empty bst

    // balance() 
    albero a{1,6};
    auto res2 = a.insert(coppia(2,7));
    auto res3 = a.insert(coppia(3,8));
    auto res4 = a.insert(coppia(4,9));
    std::cout << *(a.get_head().get_pointer()) << std::endl;
    std::cout << *(res2.first.get_pointer()) << std::endl;
    std::cout << *(res3.first.get_pointer()) << std::endl;
    std::cout << *(res4.first.get_pointer()) << std::endl;
    
    a.balance();
    std::cout << "BALANCED" << std::endl;
    std::cout << *(a.get_head().get_pointer()) << std::endl;
    std::cout << *(a.get_head().get_pointer()->right) << std::endl;
    std::cout << *(a.get_head().get_pointer()->right->right) << std::endl;
    std::cout << *(a.get_head().get_pointer()->left) << std::endl;
    albero b{};
    b.balance();
    std::cout << b << std::endl;

    // copy_sub_bst()
    std::cout << a << std::endl;
    albero b{};
    b.copy_sub_bst(res2.first.get_pointer());
    std::cout << b << std::endl;
    albero c{};
    b.copy_sub_bst(c.get_head().get_pointer());
    std::cout << b << std::endl; // b resta uguale a prima -> ok ???

    // erase()
    std::cout << a << std::endl;
    //a.erase(2);
    //a.erase(4);
    a.balance();
    a.erase(2);
    std::cout<< a << std::endl;
  
    albero b{10,9};
    b.emplace(9,8);
    b.emplace(8,7);
    b.emplace(7,6);
    std::cout << b << std::endl;
    //b.erase(7);
    b.erase(9);
    std::cout <<b <<std::endl;
    
    albero c {};
    c.erase(5);
    */

    /////////////////////////
    /////   ITERATOR   /////
    ////////////////////////

    using iteratore = albero::iterator;

    // ctors
    iteratore it{}; // default ctor
    std::cout << it.get_pointer() << std::endl;
    albero a{23,9};
    a.insert(coppia(21, 8));
    a.insert(coppia(26, 7));
    a.insert(coppia(24, 6));
    a.insert(coppia(25,9));
    iteratore it2{a.get_head().get_pointer()}; // custom ctor
/*
    // *, ->
    //std::cout << (*it).first << ";" << (*it).second << std::endl; // segmentation fault ???
    //std::cout << it->first << ";" << it->second << std::endl; // segmentation fault ???
    std::cout << (*it2).first << ";" << (*it2).second << std::endl;
    std::cout << it2->first << ";" << it2->second << std::endl;

    // ++
    ++it; // nullptr
    it++; // nullptr
    std::cout << it2 << std::endl;
    ++it2;
    std::cout << it2 << std::endl;
    it2++;
    std::cout << it2 << std::endl;
*/
    it.go_left();
    it.go_right();
    it.go_up();
    it2.go_left();
    it2.go_right();
    it2.go_up();


}
