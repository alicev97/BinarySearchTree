#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "bst.hpp"
#include "node.hpp"
#include "iterator.hpp"

int main(){

    try{

    using albero = bst<int, int>;

    albero a{10, 7};
    a.insert(std::pair<const int, int>(7,9));
    a.insert(std::pair<const int, int>(8,8));
    a.insert(std::pair<const int, int>(4,2));
    a.insert(std::pair<const int, int>(67,9));
    a.insert(std::pair<const int, int>(20,6));
    a.insert(std::pair<const int, int>(57,66));
    a.insert(std::pair<const int, int>(13,5));

    //<<
    std::cout << "Tree: " << a ;

    // clear()
    a.clear();
    std::cout << "Tree after clear:" << a << std::endl;

    a.insert(std::pair<const int, int>(10,7));
    a.insert(std::pair<const int, int>(7,9));
    a.insert(std::pair<const int, int>(8,8));
    a.insert(std::pair<const int, int>(4,2));
    a.insert(std::pair<const int, int>(67,9));
    a.insert(std::pair<const int, int>(20,6));
    a.insert(std::pair<const int, int>(57,66));
    a.insert(std::pair<const int, int>(13,5));

    // find()
    std::cout<< "Try to find 57: " << a.find(57) << std::endl;
    std::cout<< "Try to find 5: " << a.find(5).get_pointer() << std::endl; // ???
    const albero b{11,8}; 
    std::cout<< "Try to find 11: " << b.find(11) << std::endl; // calls the implementation that returns a const it

    // []
    std::cout << "\nLooking for an existing value: a[8] = " << a[8] << std::endl;
    std::cout << "Modify an existing value: a[13] = " << a[13] << " --> ";
    a[13] = 26;
    std::cout << " a[13] = " << a[13] << std::endl;
    std::cout << "Looking for a non existing value: a[99] = " << a[99] << std::endl;

    // balance()

    albero c{99,2};
    c.emplace(85,0);
    c.emplace(76,20);
    c.emplace(66,50);
    c.emplace(45,6);
    // print the unbalanced tree
    /*
             99
            /
           85
          /
         76
        /
       66
      /
    45

    */
   
    std::cout << "\n\nUnbalanced tree:\n" << std::endl;
    using iteratore = albero::iterator; 
    iteratore it = c.get_head();
    std::cout << *(it.get_pointer()) << std::endl;
    it.go_left();
    std::cout << *(it.get_pointer()) << std::endl;
    it.go_left();
    std::cout << *(it.get_pointer()) << std::endl;
    it.go_left();
    std::cout << *(it.get_pointer()) << std::endl;
    it.go_left();
    std::cout << *(it.get_pointer()) << std::endl;  
    // balance the tree  
    c.balance();
    // print the balanced tree 
    /*
          76
        /   \
       45    85
        \      \
        66      99

    */
   
    std::cout << "\nBalanced tree:\n" << std::endl;
    iteratore it2 = c.get_head();
    std::cout << *(it2.get_pointer()) << std::endl;
    it2.go_left();
    std::cout << *(it2.get_pointer()) << std::endl;
    it2.go_right();
    std::cout << *(it2.get_pointer()) << std::endl;
    it2.go_up();
    it2.go_up();
    it2.go_right();
    std::cout << *(it2.get_pointer()) << std::endl;
    it2.go_right();
    std::cout << *(it2.get_pointer()) << std::endl;

    ////// STRING
    using albero2 = bst<std::string, std::string>;

    albero2 d{"Claudia", "rosso"};
    d.insert(std::make_pair("Alice", "grigio"));
    d.emplace("Nicolas", "verde");
    d["Francesco"];
    std::cout << "Tree" << d << std::endl;
    std::cout << "Try to find Claudia : " << d.find("Claudia") << std::endl;


    } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
    } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
    return 2;
    }
    

}