### Advanced programming 2019-2020 exam - Report

In this project we've implemented a binary search tree. We've used 3 separated classes defined in three different header files ($\textit{bst.hpp, node.hpp}$ and $\textit{iterator.hpp}$) in which we've also implemented the smallest functions of each class while the other functions of the tree have been implemented in a separated header file ($\textit{bits_bst.hpp}$):

- #### bst:

  this class represents a binary search tree. It has three templates: the key type and the value type forming the pair which will be stored in each node of the tree and the operator used to compare the keys of different nodes. Each tree has two private variables: a unique pointer pointing to the root node of the tree and the chosen comparison operator. We've implemented some functions not required but useful to implement the mandatory ones. 

- #### node: 

  templated on the type of the value stored in each node, it has a private variable value of type T, two unique pointers to the left and right child and a raw pointer to the parent node. We've chosen to use unique pointers to ease memory management: resetting the unique pointer we free the memory occupied by the pointed object. Parent must be a raw pointer because parent node is already pointed by a unique pointer (its parent or head pointer if it is the root node).

  We've implemented some constructors and some functions useful when implementing other functions.

- #### iterator:

  we want to use iterators in order to browse the tree without exposing the underneath structure. It has a private pointer to a node of the tree. It has two templates: one is the type of node pointed, the other is introduced to avoid to implement two different classes to represent iterators and constant iterators.

  We've overloaded some operators and implemented some functions used to manage the abstraction from the structure.

We've created three different scripts to test all the implemented functions (directly or indirectly). In $\textit{test_node.cc}$ we've tested all constructors, move and copy semantics and node functions. In $\textit{test_bst1.cc}$ we've tested different tree constructors, move and copy semantics and different ways to add and remove  a node of a tree. Eventually in $\textit{test_bst2}$ we've checked other functions like balance, find, clear and operators.

To compile our code we've written a Makefile so just typing make we will get all needed executables. We use the g++ compiler and we compiling with flags -Wall and -Wextra we can see that no warnings are produced. 

#### Functions  of tree:

- ##### constructors and destructor

  we've implemented the default constructor (calling the default ctor for each member) and destructor; two custom constructors: one that takes a pair and another which takes also the comparison operator.

- ##### copy and move semantics

  move semantics (the default one) build a new tree or modify an existent one by calling the default move semantic on each attribute. Copy semantics are able to create a deep copy of a tree using std::make_unique used to initialise a new tree or to modify an existent one.

- ##### insert

  this function could take as input both a left and a right reference. To avoid writing two different functions we've added a template. We use a function called $\textit{get_new_parent}$ which given the pair returns an iterator to the possible parent of the node created with that pair, or the node with the same key if it exists. If it's that the case the associated value is not changed and the required output is returned, otherwise a new node is added to the tree using the $\textit{add_child}$ node function.

- ##### emplace

  emplace works as insert but it can takes as input both a pair or two values with whom it creates a new  node in place to insert it. In emplace but also in insert we take care of what happens if we are trying to insert or emplace the root node of the tree which is slightly different from the other nodes because while for other nodes we need to set the right pointer in parent, for the root node it must points to null pointer.
  
- ##### erase

  when we have to erase a node of the tree we can have different situations: the node is a leaf node, it has just one child or it has both children.

   If it's a leaf node it's sufficient to reset to null pointer the unique pointer of it's parent which points to it (it could be right or left) in order to free the memory. 

  If it has just one child I need to swap its parent's pointer to him with it's pointer to the child. Now it's pointer points to itself so I can reset it freeing the memory, then we can the child's pointer parent to the parent of the erased node. 

  In the last case we will rebuild a tree with all nodes of the sub-tree with head the node to be erased but it and then replace the old sub-tree with the new one. This is done by calling the $\textit{rebuild_from_vector}$ function explained in balance.

- ##### operators [] and <<

- ##### balance

- ##### clear

- 