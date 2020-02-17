#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "bst.hpp"
#include "node.hpp"
#include "iterator.hpp"

int main(){

    try {

    using coppia = std::pair<const int, int>;
    using nodo = Node<coppia>;
    using albero = bst<int, int>;

    ////////////////////////////////
    ///////// BUILD A TREE /////////
    ////////////////////////////////

    // default ctor
    albero a1{};
    nodo* n1 = a1.get_head().get_pointer();
    std::cout << "default ctor: head is nullptr:\n" <<  n1 << std::endl; 

    // custom ctor given k and v
    albero a2{12,25};
    n1 = a2.get_head().get_pointer();
    std::cout << "\ncuston ctor given k and v:\n" << *n1 << std::endl;

    // custom ctor given k, v and op
    bst<int, int, std::greater<int>> reverse_tree{34,15,std::greater<int>()};
    // this should be a right child and not a left child!
    reverse_tree.insert(coppia(23,45));
    std::cout << *(reverse_tree.get_head().get_pointer()) << *(reverse_tree.get_head().get_pointer()->right.get()) << std::endl;

    // let's build a bigger tree inserting new nodes:
    // left reference pair
    coppia c1(7,18);
    a2.insert(c1);
    std::cout << a2 << std::endl;
    n1 = a2.get_head().get_pointer();
    nodo* n2 = n1->left.get();
    //std::cout << "head = n1:\n" << *n1 << "\nn1 left = n2:\n" << *n2 << std::endl; 

    // right reference pair
    a2.insert(coppia(25,3));
    std::cout << a2 << std::endl;
    nodo* n3 = n1->right.get();
    //std::cout << "head = n1:\n" << *n1 << "\nn1 left = n2:\n" << *n2 << "\nn1 right = n3\n" << *n3 << std::endl; 

    //emplace
    a2.emplace(23,15);
    std::cout << a2 << std::endl;
    nodo* n4 = n3->left.get();
    std::cout << "head = n1:\n" << *n1 << "\nn1 left = n2:\n" << *n2 << "\nn1 right = n3\n" << *n3 << "\nn3 left = n4\n"<< *n4 << std::endl; 

    a2.emplace(std::make_pair(18,9));
    std::cout << a2 << std::endl;
    
    // copy ctor
    albero a3{a2};
    std::cout << "copy ctor:\na2 = "<< a2 << "a3 = " << a3 << std::endl;

    // if I modify a2, a3 doesn't change
    a2.insert(coppia(29,2));
    std::cout << "a2: " << a2 << "a3: " << a3 << std::endl;

    // move ctor
    albero a4{albero{7,23}};
    std::cout << a4 << "\n" << *(a4.get_head().get_pointer()) << std::endl;

    // move assignment
    a3 = albero{9,12};
    std::cout << *(a3.get_head().get_pointer()) << std::endl;

    // copy assignment 
    albero a5{34,67};
    std::cout << "a2: " << a2 << "\na5: " << a5;
    a5 = a2;
    std::cout << "a2: " << a2 << "\na5: " << a5 << std::endl;

    //////////////////////////
    ////// ERASE A NODE //////
    //////////////////////////

    //// REMOVE LEAF NODE and THE ROOT
    albero a{17,12};
    a.insert(std::make_pair(13,98));
    a.insert(std::make_pair(25,8));
    a.insert(std::make_pair(23,4));
    a.insert(std::make_pair(45,90));
    std::cout << "\n" << a << std::endl;
    /*          17
               /  \
             13    25
                  /  \
                 23   45
    */
    a.erase(23);
    std::cout << "remove a left leaf node\n" << a << std::endl;
    a.erase(45);
    std::cout << "remove a right leaf node\n" << a << std::endl;
    a.erase(17);
    std::cout << "remove the root with 2 children\n" << a << std::endl;

    //// REMOVE ONE-CHILD NODE
    // has left-is left
    // the root if it has just a left child
    // has right-is left
    a = albero(28,22);
    a.insert(std::make_pair(27,62));
    a.insert(std::make_pair(19,1));
    a.insert(std::make_pair(23,3));
    std::cout << "\n" << a << std::endl;
    /*          28
               /  
             27    
            /     
          19 
            \
             23   
    */
    a.erase(27);
    std::cout << "remove a left child which has a left child\n" << a << std::endl;
    a.erase(28);
    std::cout << "remove the root with just a left child\n" << a << std::endl;
    a.erase(19);
    std::cout << "remove a left child which has a right child\n" << a << std::endl;

    // has right-is right
    // the root if it has just a right child
    // has left-is right
    a = albero(21,22);
    a.insert(std::make_pair(27,62));
    a.insert(std::make_pair(37,1));
    a.insert(std::make_pair(31,3));
    std::cout << "\n" << a << std::endl;
    /*          21
                  \
                   27
                     \
                      37
                     /
                   31
    */
    a.erase(27);
    std::cout << "remove a right child which has a right child\n" << a << std::endl;
    a.erase(21);
    std::cout << "remove the root with just a right child\n" << a << std::endl;
    a.erase(37);
    std::cout << "remove a right child which has a left child\n" << a << std::endl;

    //// REMOVE TWO-CHILDREN NODE
    a = albero{13,7};
    a.insert(std::make_pair(24,1));
    a.insert(std::make_pair(20,56));
    a.insert(std::make_pair(30,6));
    a.insert(std::make_pair(16,44));
    a.insert(std::make_pair(22,0));
    std::cout << "\n" << a << std::endl;
    /*          21
                  \
                   24
                  /  \
                20    30
               /  \
             16    22  
    */
    a.erase(24);
    std::cout << "remove a right child which both children\n" << a << std::endl;
    a.erase(20);
    std::cout << "remove a left child which both children\n" << a << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Unknown exception" << std::endl;
        return 2;
    }

}