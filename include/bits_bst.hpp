#ifndef __bits_bst_hpp__
#define __bits_bst_hpp__
#include "bst.hpp"

// insert
template<typename kT,typename vT, typename cmp>
template<typename OT>
std::pair<typename bst<kT,vT,cmp>::iterator,bool> bst<kT,vT,cmp>::insert(OT&& x){
    
    // build a new node (copy ctor or move ctor depending on OT)
    node_type* n{new node_type{x}};

    // if I'm trying to insert the first node of an empty tree reset its head
    if(head == nullptr){
        //node_type* n{new node_type{x}};
        head.reset(n);
        iterator it {head.get()};
        std::pair<iterator,bool> result(it,true);
        return result;
    }
    //find where to attach the new node
    auto p = (*this).get_new_parent(x);
    node_type* parent = p.get_pointer();

    // if a node with that key already exists return the iterator and delete new node
    if (!op(x.first, p->first) && !op(p->first,x.first)){
        std::cout << "The key already exists" << std::endl;
        std::pair<iterator,bool> result(p,false);
        delete n;
        return result;
    } else {
    // otherwise call node function add_child
        iterator it{parent->add_child(n,op)};
        std::pair<iterator,bool> result(it,true);
        return result;
    }
}

template<typename kT,typename vT,typename cmp>
template<class... Types>
std::pair<typename bst<kT,vT,cmp>::iterator,bool> bst<kT,vT,cmp>::emplace(Types&&... args){

    // create a new node with the given parameters
    node_type* new_node{new node_type{pair_type{std::forward<Types>(args)...}}};

    // if I'm trying to emplace the first node of an empty tree reset its head
    if(head == nullptr){
        head.reset(new_node);
        iterator it {head.get()};
        std::pair<iterator,bool> result(it,true);
        return result;
    }

    // find in which node I should attach the new node
    auto p = (*this).get_new_parent(new_node->value);
    node_type* parent = p.get_pointer();

    // if a node with that key already exists
    if (!op(new_node->value.first, parent->value.first) && !op(parent->value.first, new_node->value.first)){
        std::pair<iterator,bool> result(p,false);
        std::cout << "The key already exists" << std::endl;
        delete new_node;
        return result;
    } else {
    //otherwise call the node function add_child
        iterator it{parent->add_child(new_node,op)};
        std::pair<iterator,bool> result(it,true);
        return result;
    }   
}

template<typename kT, typename vT, typename cmp>
void bst<kT, vT, cmp>::clear(){
    //iterator to head
    iterator it{head.get()};

    while(head != nullptr){ //while i've not cleaned head

    while (!it.is_leaf()){ // while i'm not a leaf node

    while (it.has_left()){ // go hard left
        it.go_left();
    }
    while(it.has_right()){ // go hard right
        it.go_right();
    }

    }
    if(it.get_pointer() != head.get()){
        it.go_up();
        if (it.has_left()){ // if I was the left child
            it.get_pointer()->left.reset();
            it.get_pointer()->left.release();
        } else{ // if I was the right child
            it.get_pointer()->right.reset();
            it.get_pointer()->right.release();
        }
    } else{ // if I am the head
        head.reset();
        head.release();
    }

    }
}


template<typename kT, typename vT, typename cmp>
typename bst<kT,vT,cmp>::iterator bst<kT, vT, cmp>::find(const kT& x) {
    iterator tmp{head.get()};

    if(tmp == end()) // if head nullptr
        return tmp;

    while (op(x, tmp->first) || op(tmp->first, x) || !tmp.is_leaf()){ // while  I've find the value or I'm at a leaf
    if (op(x, tmp->first)){ // if <
        if (tmp.has_left()){ // if there is a left child (< value)
            tmp.go_left();
        } else { break;} // otherwise the value is not present
    } else if (op(tmp->first, x)){ // if >
        if (tmp.has_right()){ // if there is a right child (> value)
        tmp.go_right();
        } else {break;} // otherwise the value is not present
    } else {
        break; // if ==
    }
    }

    // check why exit form the while
    if (!op(x, tmp->first) && !op(tmp->first, x)){ // if ==
    return tmp;
    } else{return end();} // not found
}


template<typename kT, typename vT, typename cmp>
typename bst<kT, vT, cmp>::const_iterator bst<kT, vT, cmp>::find(const kT& x) const{
    const_iterator tmp{head.get()};
    
    if(tmp == end()) // if head nullptr
        return tmp;

    while (op(x, tmp->first) || op(tmp->first, x) || !tmp.is_leaf()){ // while  I've find the value or I'm at a leaf
    if (op(x, tmp->first)){ // if <
        if (tmp.has_left()){ // if there is a left child (< value)
            tmp.go_left();
        } else { break;} // otherwise the value is not present
    } else if (op(tmp->first, x)){ // if >
        if (tmp.has_right()){ // if there is a right child (> value)
        tmp.go_right();
        } else {break;} // otherwise the value is not present
    } else { // if ==
        break;
    }
    }
    
    // check why exit form the while
    if (!op(x, tmp->first) && !op(tmp->first, x)){ // if ==
    return tmp;
    } else{return end();} // not found
}

template<typename kT, typename vT, typename cmp>
typename bst<kT, vT, cmp>::iterator bst<kT, vT, cmp>::get_new_parent(typename bst<kT, vT, cmp>::pair_type x) {

    //starting from head and stopping when tmp is a leaf node
    iterator tmp{head.get()};
    
    while (tmp.is_leaf()==false){

        // if node key is smaller (greater) than the one of my pair:
        // - if I can I go left (right)
        // - otherwise i break the while and return the iterator
        if (op(x.first, tmp->first)){

            if (tmp.get_pointer()->left.get()!=NULL){
                tmp.go_left();
            } else { break;}
            
        } else if (op(tmp->first, x.first)){

            if (tmp.get_pointer()->right.get()!=NULL){
            tmp.go_right();
            } else {break;}

        } else {
            // if I've found the key
            break;
        }
    }
    
    return tmp;
}

template<typename KT,typename VT,typename CMP>
std::ostream& operator<<(std::ostream& os, const bst<KT,VT,CMP>& x) {

    auto it = x.begin();
    while (it != x.end()){
        os << it->first << " ";
        ++it;
    }
    return os;
}


template<typename kT, typename vT, typename cmp>
template<typename OT>
vT& bst<kT,vT,cmp>::operator[](OT&& x){

    auto it = find(x);
    //it is an iterator to the element or the end() iterator
    
    if (it == end()){
        // build a pair with default value and the givan key
        pair_type p{x,vT{}};
        // insert a new node and return the value
        insert(p);
        // print this to distinguish the case in which the node already exists and has the default value
        std::cout << "node already exists" << std::endl;
        return p.second;
    } else {
        // or if it already exists return the value
        return it->second;
    }

}


template<typename kT,typename vT, typename cmp>
void bst<kT,vT,cmp>::balance(){
    
    iterator it = begin();
    if (it == end()) // empty tree
        return;

    // build a vector of pairs
    std::vector<std::pair<const kT,vT>> tmp;

    // fill it with all pairs of the tree
    std::pair<kT,vT> p;
    
    while (it != end()){
        p = std::make_pair(it->first,it->second);
        tmp.push_back(p);
        ++it;
    }
    
    // clear the tree
    clear();

    //rebuld it recursively
    std::size_t size{tmp.size()};
    rebuild_from_vector(tmp,0,size-1);
}

template<typename kT, typename vT, typename cmp>    
void bst<kT,vT,cmp>::rebuild_from_vector(std::vector<bst<kT,vT,cmp>::pair_type> v, std::size_t from,std::size_t to){

    // input parameters are. -> a vector containing the pairs 
    //                       -> 2 indexes needed to manage the recursion
    if (to<from)
        return; // stop condition
    
    // insert the middle element 
    std::size_t t{(to+from)/2};
    insert(v[t]);
    // recall the function on the 2 sub-vectors
    if (!(to==from)){
        if (t!=0){
            rebuild_from_vector(v,from,t-1);
        }
        rebuild_from_vector(v,t+1,to);
    }
    
}

template<typename kT, typename vT, typename cmp>
void bst<kT, vT, cmp>::copy_sub_bst(const bst<kT,vT,cmp>::node_type* b){
    
    insert(pair_type (b->value.first, b->value.second)); // insert the node

    if(b==nullptr)// stop condition
        return;
    if (b->left.get()!=nullptr)
        copy_sub_bst(b->left.get()); // recursion
    if (b->right.get()!=nullptr)
        copy_sub_bst(b->right.get()); // recursion
}


template<typename kT, typename vT, typename cmp>
void bst<kT,vT,cmp>::erase(const kT& x){

    //find  the element with that key
    auto it = find(x);

    // if not found tell the user
    if (it==end()){ 
        std::cout << "Key not found" << std::endl;
    } else {
        /* Here I need to distinguish 3 cases: the node to be erased:
         * 1) is a leaf node
         * 2) has both right and left children
         * 3) has just one child
        */
        if (it.is_leaf()){
        // if is leaf -> remove it through the unique pointer
            if (it.is_left()){
                it.go_up();
                it.get_pointer()->left.reset();
            } else {
                it.go_up();
                it.get_pointer()->right.reset();
            }
        } else if (it.has_right() && it.has_left()) {
        /* if it has 2 children -> create a temporary tree with a copy of the subtree of all children
                                -> create vector with pairs of that tree
                                -> remove its pair 
                                -> rebuild_from_vector
                                -> link my parent with the head of the new tree
                                -> remove the old sub-tree
        */
        node_type* my_ptr = it.get_pointer();
               
        bst<kT,vT,cmp> tmp{};
        tmp.copy_sub_bst(my_ptr);
        
        std::vector<std::pair<const kT,vT>> v;
        iterator it_tmp = tmp.begin();
        std::pair<kT,vT> p;
       
        // fill the vector with all sub-nodes but me
        while (it_tmp != tmp.end()){ 
            p = {it_tmp->first,it_tmp->second};
            if (p.first != it->first) {
                v.push_back(p);  
            }
            ++it_tmp;
        }

        tmp.clear();
        tmp.rebuild_from_vector(v,0,v.size()-1);
        
        // if I'm trying to remove the root I just need to swap tree heads 
        if (it == get_head()){
            tmp.head.swap(head);
        } else {
        //otherwise I also need to change the pointers
        node_type* parent_ptr = my_ptr->parent;
        tmp.head->parent = parent_ptr;

        if (it.is_left()){
            parent_ptr->left.swap(tmp.head);
        } else {
            parent_ptr->right.swap(tmp.head);
        }

        my_ptr->parent=nullptr;
        }
        // clean again tmp that now contains the old tree
        tmp.clear();
        
        } else {
        /* if it has just one child -> its parent points its child 
                                    -> its child's parent becomes its parent
                                    -> remove the node
        */
       
        // if I'm trying to erase the root 
        if (it == get_head()){
            if (it.has_left()){
                head.swap(it.get_pointer()->left);
                head->parent->left.reset();
            } else {
                head.swap(it.get_pointer()->right);
                head->parent->right.reset();
            }
            head->parent=nullptr;

        } else {

            node_type* my_ptr = it.get_pointer();
            node_type* parent_ptr = my_ptr->parent;
                        
            if (it.has_left()) { //has left
                if (it.is_left()){ // has left - is left
                    it.go_up();
                    //change left in parent, delete the node and go to the new child
                    parent_ptr->left.swap(my_ptr->left); 
                    my_ptr->left.reset(); 
                    it.go_left();
                } else { //has left - is right
                    it.go_up();
                    //change right in parent, delete the node and go to the new child
                    parent_ptr->right.swap(my_ptr->left);
                    my_ptr->left.reset();
                    it.go_right();
                }
            } else {  // has right            
                if (it.is_right()){ // has right - is right
                    it.go_up();
                    //change right in parent, delete the node and go to the new child
                    parent_ptr->right.swap(my_ptr->right);
                    my_ptr->right.reset();
                    it.go_right();
                } else { // has right - is left
                    it.go_up();
                    //change left in parent, delete the node and go to the new child
                    parent_ptr->left.swap(my_ptr->right);
                    my_ptr->right.reset();
                    it.go_left();
                }
            }
            //in any case I'm pointing the new child so I can set parent
            it.get_pointer()->parent=parent_ptr;
        }
        }
    }
}

#endif