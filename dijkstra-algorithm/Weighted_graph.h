/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Leftist_heap.h"
#include "Exception.h"
// include whatever classes you want

class Weighted_graph {
	private:
		int edge;
		int size;
		int *degree_num;
		double **adj_table;
		
		static const double INF;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int ) const;

		void insert( int, int, double );
		class vertex{
			public:
			int num;
			double distance;
			 vertex(int number, double dist){
			 	num = number;
			 	distance = dist;
			 }
				 
		};
		
		vertex ** vertices; 

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n){

	size = std::max(1,n);
	edge=0;
	degree_num = new int[size];
    vertices = new vertex*[size];
	adj_table = new double*[size];	
	for(int row = 0; row < size; row++){
		adj_table[row] = new double[size];
		vertices[row] = new vertex(row, INF);
		for(int column =0; column<size; column++){
			if(column==row) adj_table[row][column]=0;
			else adj_table[row][column]=INF;
		}
	}
}
Weighted_graph::~Weighted_graph() {
	delete[] degree_num;
	
	for(int i = 0; i<size; i++)
	{
		delete[] adj_table[i];
		delete vertices[i];
	}
	
	delete[] vertices;
	delete[] adj_table;
    size=0;
    edge=0;
	
	}
	
	
	
int Weighted_graph::degree( int n) const {
	if(n<0 ||n>(size-1)) throw illegal_argument();
	else return degree_num[n];		
}

int Weighted_graph::edge_count() const {
	return edge;
}

double Weighted_graph::adjacent( int m, int n) const {
	if(n<0 ||n>(size-1) ||m<0 ||m>(size-1)) throw illegal_argument();
	else if(m==n) return 0;
	else return adj_table[m][n];	
}

void Weighted_graph::insert(int m, int n, double w) {
	if(w<=0) throw illegal_argument();
	else if(n<0 ||n>(size-1) ||m<0 ||m>(size-1) ||m==n) throw illegal_argument();
	else{
		if(adj_table[m][n]==INF){
			edge+=1;
			adj_table[m][n]=w;
			adj_table[n][m]=w;
			degree_num[m]+=1;
			degree_num[n]+=1;
		}
		else{
			adj_table[m][n]=w;
			adj_table[n][m]=w;
		}
	}
}

double Weighted_graph::distance(int m, int n) const{

    if(n<0 ||n>(size-1) ||m<0 ||m>(size-1)) throw illegal_argument();
	else if (m==n) return 0;
	else{
        
        double distance=INF;
        Leftist_heap<vertex> * heap = new Leftist_heap<vertex>();

			for(int i=0;i<size;i++){
                if(i==m){
					vertices[i]->distance=0;
				}
				else vertices[i]->distance=INF;
			}
        
			heap->push(*vertices[m]);
			
			while (heap->empty()==false){
				int poped_index=heap->pop().num;
                if(poped_index==n){
					distance=vertices[n]->distance;
                    break;
				}
				for (int column=0; column<size; column++){
                   
					if(adj_table[poped_index][column]!=INF &&column!=m){
						if(vertices[column]->distance > (vertices[poped_index]->distance+adj_table[poped_index][column])){
                            
							vertices[column]->distance = (vertices[poped_index]->distance+adj_table[poped_index][column]);
							heap->push(*vertices[column]);
							if(column==n) distance=vertices[column]->distance;
						}
					}
				}
            }
            delete heap;
            return distance;
            
	 	}
}



std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
