#ifndef DISJ_SETS_H
#define DISJ_SETS_H

// DisjSets class
//
// CONSTRUCTION: with int representing initial number of sets
//
// ******************PUBLIC OPERATIONS*********************
// void union( root1, root2 ) --> Merge two sets
// int find( x )              --> Return set containing x
// ******************ERRORS********************************
// No error checking is performed

#include <vector>
using namespace std;

/**
 * Disjoint set class.
 * Use union by rank and path compression.
 * Elements in the set are numbered starting at 0.
 */
class DisjSets {
  public:
	DisjSets(int numElements);

	int find(int x) const;
	int fast_find(int x); 	// Previous optimized recursive find function with path compression
	int find(int x); 		// Version without path compression needed for maze construction
	int find_iter(int x); 	// Iterative version of find with pathcompression
	void fast_unionSets(int root1, int root2);	// Previous fast union sets function
	void unionSets(int child, int parent);		// Simple unionSets needed for maze construction
	void print(int x);	// Exercise 2 find method to print all nodes in same set
	void print_all();	// Print function showing the entries to s, to visualise the set structure

  private:
  	friend class Maze;
	vector<int> s;
	vector<int> n;	// Vector n "next" for the optimised print function, printing in linear time in the amount of elements in the set
};

#include "fast_disjoint_sets.cpp"

#endif
