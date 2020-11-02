#include <cassert>
#include <iostream>
#include "disjoint_sets.hpp"
#include "maze.hpp"

int main() {
    { // TEST 1.A: seeing if the find algorithm works correctly 
          cout << "__________________________" << endl
               << "|"                          << endl
               << "| TEST 1.A START"           << endl;
          int amount = 10;
          DisjSets ds(amount);
          
          int expected = 1;
          ds.fast_unionSets(expected,2);
          ds.fast_unionSets(2,3);

          int ret = ds.find_iter(3);
          assert(ret = expected);

          cout << "| SUCCESS"                  << endl;
          cout << "| TEST 1.A END"             << endl
               << "|_________________________" << endl;
    }
    { // TEST 1.B: seeing if path compression works correctly
          cout << "__________________________" << endl
               << "|"                          << endl
               << "| TEST 1.B START"           << endl;
          int numInSameSet = 8;
          int numElements = numInSameSet;

          DisjSets ds(numElements);
          int set1, set2;

          for (int k = 1; k < numInSameSet; k *= 2) {
               for (int j = 0; j + k < numElements; j += 2 * k) {
                    set1 = ds.find(j);
                    set2 = ds.find(j + k);
                    ds.fast_unionSets(set1, set2);
               }
          }
          cout << "The disjoint sets vector looks like this" << endl;
          ds.print_all();
          cout << "Using the iterative find algorithm with path compression on node 7" << endl;
          ds.find_iter(7);
          ds.print_all();

          cout << "| TEST 1.B END"             << endl
               << "|_________________________" << endl;
    }
    { // TEST 2.A: seeing if the find algorithm correctly 
          cout << "__________________________" << endl
               << "|"                          << endl
               << "| TEST 2.A START"           << endl;
          int numInSameSet = 4;
          int numElements = numInSameSet*2;

          DisjSets ds(numElements);
          int set1, set2;

          for (int k = 1; k < numInSameSet; k *= 2) {
               for (int j = 0; j + k < numElements; j += 2 * k) {
                    set1 = ds.find_iter(j);
                    set2 = ds.find_iter(j + k);
                    ds.fast_unionSets(set1, set2);
               }
          }
          cout << "The disjoint sets vector looks like this" << endl;
          ds.print_all();
          cout << "Calling the print function on node 5, print(5)" << endl;
          ds.print(5);

          cout << "| TEST 2.A END"             << endl
               << "|_________________________" << endl;
    }
    { // TEST 3.A: Maze
          cout << "_________________________"  << endl
               << "|"                          << endl
               << "| TEST 3.A START"           << endl;

          int rows = 16;
          int cols = 34;
          //Maze* maze1 = new Maze(rows, cols);

          Maze maze(rows, cols);

          maze.print();
          maze.show();
          maze.solve();
          maze.show();

          // maze.generate(110, 235);
          // maze.solve();
          // maze.show();

          cout << "| TEST 3.A END"             << endl
               << "|_________________________" << endl;
    }
    
    return 0;
}