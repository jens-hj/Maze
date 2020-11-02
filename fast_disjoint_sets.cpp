// #include <iostream>
// #include "disjoint_sets.h"


/**
 * Construct the disjoint sets object.
 * numElements is the initial number of disjoint sets.
 */
DisjSets::DisjSets(int numElements):s(numElements, -1) {
	// Added this to initialise the next vector used in the optimised print function
	for (int i = 0; i < numElements; i++) {
		n.push_back(i);	// All elements start by pointing to themselves
	}
}

/**
 * Union two disjoint sets.
 * For simplicity, we assume root1 and root2 are distinct
 * and represent set names.
 * root1 is the root of set 1.
 * root2 is the root of set 2.
 */
void DisjSets::fast_unionSets(int root1, int root2) {
	if (s[root2] < s[root1])	// root2 is deeper
		s[root1] = root2;		// Make root2 new root
	else {
		if (s[root1] == s[root2])
			--s[root1];			// Update height if same
		s[root2] = root1;		// Make root1 new root
	}

	// Logic for n-vector
	// Swaps what elements the child and parent
	// elements are pointing to in the n-vectore
	// This makes it so that every element in the same set
	// points to each other in an arbitrary ring without any
	// defined order to it.
	int tmp = n[root1];
	n[root1] = n[root2];
	n[root2] = tmp;
}

/**
 * Perform a find.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSets::find(int x) const {
	if (s[x] < 0)
		return x;
	else
		return find(s[x]);
}

/**
 * Perform a find with path compression.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSets::fast_find(int x) {
	if (s[x] < 0)
		return x;
	else
		return s[x] = fast_find(s[x]);
}

// EXERCISE 1
// Iterative find algorithm with path compression
// COMPLEXITY: The worst case time complexity of this algorithm becomes linear
// O(N), since worst case is that all elements are in a long string pointing
// towards one root.
int DisjSets::find_iter(int x) {
	int root = x;		// starting at x
	vector<int> path;	// Records the pth to x's root node
	while(this->s[root] >= 0){	// While a root node isn't reached
		path.push_back(root);	// Append the current node to path
		root = this->s[root];	// Go to the next node
	}
	if (root != x){	// If x isn't a root node
		for (int i = 0; i < path.size(); i++) {	// Make every node in path
			this->s[path[i]] = root;			// Have the same root as x
		}
	}
	return root;
}

// Simple find function without path compression, as that would
// not work when using the DisjSets class to construct a maze.
int DisjSets::find(int x) {
	if (s[x] < 0)
		return x;
	else
		return find(s[x]);
}

// EXERCISE 2
// Optimised print function printing
// each element in the same set as x
// *NOTE see unionSets implementations for the logic of the n-vector
// COMPLEXITY: The time complexity for this method is linear in the number
// of elements in the same set as x. This is implemented by an extra attribute
// to each element - See NOTE for logic explanation
void DisjSets::print(int x) {
	int curr = x;	// Starting at x
	do {
		cout << curr << " ";	// print the current element
		curr = n[curr];			// Advance to the next element in the same set
	} while (curr != x);		// While we haven't arrived back at x
	cout << endl;
}

/**
 * Function to print all elements of vector s
 * Function implemented for convenience, making
 * visualisation of the disjoint sets simpler
 */
void DisjSets::print_all() {
	for (int i = 0; i < s.size(); i++) {
		cout << i << ": " << s[i] << endl;
	}
	cout << endl;
}

// Simple unionSets used for maze construction
void DisjSets::unionSets(int child, int parent) {
	s[child] = parent;

	// Logic for n-vector
	// Swaps what elements the child and parent
	// elements are pointing to in the n-vectore
	// This makes it so that every element in the same set
	// points to each other in an arbitrary ring without any
	// defined order to it.
	int tmp = n[child];
	n[child] = n[parent];
	n[parent] = tmp;
}