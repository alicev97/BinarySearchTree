#include "ap_error.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

// in this template i will put a pair
template <typename T>
struct Node{
    //variables
    T value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node* parent;
    
    using pair_type = T;

    //ctors
    Node() = default;
    Node(T pair): value{pair}, left{nullptr},right{nullptr},parent{nullptr} {}
    
    // copy ctor
    Node(const Node& n); //to be implemented
    // move ctor
    Node(Node&& n) noexcept = default;
    // move assignment
    Node& operator=(Node&&) noexcept = default;
    //copy assignment
    Node& operator=(const Node&); // to be implemented

    //put-to overloading
    friend
    std::ostream& operator<<(std::ostream& os, const Node& n){
        os << "key = " << n.value.first << std::endl;
        os << "value = " << n.value.second << std::endl;
        os << "my address:  " << &n << std::endl;
        os << "pointers: \nparent: " << n.parent << std::endl;
        return os;
    }

    // change pointers
    void set_parent(Node* p){
        parent=p;
    }
};

template<typename node_type,typename O>
class _iterator{
    node_type* current;

public:
    //ctor
    explicit _iterator(node_type* x) noexcept : current{x} {}

    using value_type = O;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    // OVERLOADING
    reference operator*() const noexcept { return current->value;}
    pointer operator->() const noexcept { return &(*(*this)); } //why &**?

    //returns a new iterator (class reference)
    _iterator& operator++() noexcept {
    //find the  next and put the pointer in current
    return *this;
    }
    _iterator operator++(int) noexcept {
    //find the  next and put the pointer in current
    return *this;
    }
    friend bool operator==(const _iterator& a, const _iterator& b) {
    return a.current == b.current;
    }
    friend bool operator!=(const _iterator& a, const _iterator& b) {
    return !(a == b);
    }

};

template<typename kT, typename vT, typename cmp = std::less<kT>>
class bst{
    using node_type = Node<std::pair<const kT, vT>>;
    using pair_type = std::pair<const kT, vT>;
    //variables
    std::unique_ptr<node_type> head;
public:
    //ctors and destructor
    bst() = default;
    ~bst() = default;
    //ctom ctor with key and value, calls the node ctor
    //bst(kT a,vT b): head{std::unique_ptr<node_type>(&Node<pair_type>{std::pair<kT,vT>(a,b)})}{}
    bst(kT a, vT b) {
        Node<std::pair<kT,vT>> n{std::pair<kT,vT>(a,b)};
        head = std::make_unique<Node<std::pair<kT,vT>>>(n);
    }
    // copy semantic

    // move semantic

    //iterators
    using iterator = _iterator<node_type,pair_type>;
    using const_iterator = _iterator<node_type, const pair_type>;
    
    // functions
    // insert
    std::pair<iterator,bool> insert(const pair_type& x);
    std::pair<iterator,bool> insert(pair_type&& x);

    // emplace
    template<class... Types>
    std::pair<iterator,bool> emplace(Types&&... args);

    // clear
    void clear();

    // begin
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    // end
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    // find
    iterator find(const kT& x);
    const_iterator find(const kT& x) const;

    // balance
    void balance();

    // operator overloading 
    vT& operator[](const kT& x);
    vT& operator[](kT&& x);

    //friend std::ostream& operator<<(std::ostream& os, const bst& x);

    // erase
    void erase(const kT& x);

};



int main(){
    Node<std::pair<const int,int>> node1{std::pair<const int,int>(23,15)};
    std::cout << node1;    
    std::pair<const int,int> p{1,2};
    Node<std::pair<const int,int>> node2{p};
    std::cout << node2;

    node2.set_parent(&node1);
    std::cout << node2;

    //std::shared_ptr<Node<std::pair<const int,int>>> sp{&node1};
    //std::cout << sp << std::endl;
    //std::cout << &node1 << std::endl;
    //node2.set_parent(sp);

    //Node<std::pair<const int,int>> node5{std::move(node2)};

    //bst<const int,int> tree1;
    //bst<const int, int> tree2{2,3};
    //_iterator<Node<std::pair<const int,int>>,std::pair<const int,int>> c{&node1};
    //std::unique_ptr<Node<std::pair<const int,int>>> a = std::make_unique<Node<std::pair<const int,int>>>();
    //std::unique_ptr<Node<std::pair<const int,int>>> b = std::make_unique<Node<std::pair<const int,int>>>();
    //std::cout << a->value.first << std::endl;
    //auto node = a.get();
    //std::cout << *a << std::endl;
    //std::cout << *node << std::endl;
    //std::cout << node << std::endl;

}