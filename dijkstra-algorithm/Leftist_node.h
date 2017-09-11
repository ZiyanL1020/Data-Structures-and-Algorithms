/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
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
	return ( this == nullptr );
}

template <typename Type>
Type Leftist_node<Type>::retrieve() const {
	return element;
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const {
	return left_tree;
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const {
	return right_tree;
}

template <typename Type>
int Leftist_node<Type>::null_path_length() const {
	if(this == nullptr) return -1;
	else return heap_null_path_length;
}

template <typename Type>
int Leftist_node<Type>::count(const Type &obj) const {
	int number=0;
	if(empty()) return 0;
	if(element == obj){
		number+=1;					//when find a node equal to obj, number +1
	}
	number=number + left_tree->count(obj) + right_tree->count(obj);			//find obj in left tree and right tree and add them with the node
	return number;
}

template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this ){
	if(new_heap==nullptr)return;			//if new_ heap is null, return			
	else if(ptr_to_this==nullptr){
		ptr_to_this = new_heap;
		return;								//if this is null, set the pointer to this to be the new heap, return
	}
	else if(ptr_to_this->retrieve().distance<=new_heap->retrieve().distance){				//if the current node is storing a value less-than-orequal-to the value stored in the root of the new heap
		ptr_to_this->right_tree->push(new_heap, ptr_to_this->right_tree);	//push the new node onto the right sub-tree with right_tree
		int min;
		if(left_tree->null_path_length()>=right_tree->null_path_length()){
			min=right_tree->null_path_length();
		}
		else{
			min=left_tree->null_path_length();
			std::swap(left_tree,right_tree);						// if the left-sub-tree has a smaller null-path length than the right sub-tree, swap the two sub-trees
		} 		
		ptr_to_this->heap_null_path_length=1+min;					//update the null_path_length
	}
	else{
		ptr_to_this = new_heap;
		ptr_to_this->push(this,new_heap);					//otherwise, set the pointer to this to be the new heap and push this node into the new heap
	}
}

template <typename Type>
void Leftist_node<Type>::clear(){
	if(this==nullptr) return;					//If this is nullptr, return
	else{
		left_tree->clear();						//otherwise, clear all the left sub tree
		right_tree->clear();					//clear the right
	}
	delete this;
}




// You must implement everything

#endif
