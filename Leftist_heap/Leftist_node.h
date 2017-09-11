/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  z363liu@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
    
    //return if the current reference is a null pointer
	return ( this == nullptr );
}

// You must implement everything

template <typename Type>
Type Leftist_node<Type>::retrieve() const {
    //return the element inside the node
    return element;
}


template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const {
    //return the left subtree
    return left_tree;
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const {
    //return the right subtree
    return right_tree;
}

template <typename Type>
int Leftist_node<Type>::null_path_length() const {
    //return the null path length of the current node
    if(this == nullptr)
        return -1;
    return heap_null_path_length;
}

template <typename Type>
int Leftist_node<Type>::count( Type const &obj ) const{
    //use recursion to count the # of targets in right and left subtree
    if(empty())
        return 0;
    
    if(element == obj)
        return 1+left_tree->count(obj)+right_tree->count(obj);
    else
        return left_tree->count(obj)+right_tree->count(obj);
        
}


template <typename Type>
void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this){
    //if the new heap is a null pointer, there is nothing to push
    //if current heap is a null pointet, the new heap becomes the current heap
    //if the value of current heap root node is less than the one of new heap
    //push the new heap to the right tree of current heap
    //update the root null path length
    //if the value of current heap root node is greater than or equal to the one of new heap
    //change the current pointer to new heap
    //push new heap onto this
    if(new_heap == nullptr){
        return;
    }else{
        if(ptr_to_this == nullptr){
            ptr_to_this = new_heap;
            return;
        }else if(ptr_to_this->retrieve() <= new_heap->retrieve()){
            ptr_to_this->right()->push(new_heap,right_tree);
            
            int leftNPL = left_tree->null_path_length();
            int rightNPL = right_tree->null_path_length();
            
            ptr_to_this->heap_null_path_length = 1 + std::min(leftNPL, rightNPL);
            
            if(leftNPL < rightNPL){
                std::swap(left_tree,right_tree);
            }
        }else{
            ptr_to_this = new_heap;
            ptr_to_this->push(this,new_heap);
        }
    
    }
            
}



template <typename Type>
void Leftist_node<Type>::clear(){
    //clear the heap
    if(this == nullptr)
        return;
    left_tree->clear();
    right_tree->clear();
    delete this;
}
#endif
