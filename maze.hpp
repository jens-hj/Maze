#pragma once

#include <iostream>
#include <ctime>
#include "disjoint_sets.hpp"
using namespace std;

// EXERCISE 3

// Enumeration to indicate possible directions to create in maze
enum direction {NONE=-1, UP, RIGHT, DOWN, LEFT, BACK};

class Maze {
    private:
        DisjSets* ds;           // DisjSets tree structure of maze
        int rows;
        int cols;

        bool show_num;          // Determines whether to show numbers in maze
        bool solved;            // Records whether the maze is solved
        vector<int> solution;   // Vector path of the solution - filled by solve()
        
        // Internal print methods called by external print method
        void _print();
        void print_horizontal(int &curr, int &cell_width);
        void print_vertical(int &curr, int &cell_width);
        void _print_vertical(int &curr, int &cell_width, bool show_character);
        bool is_in_solution(int curr);
        int cell_width();
        bool is_related(int a, int b);

    public:
        Maze();                             // Instantiates maze of size 1*1
        Maze(int rows, int cols);           // Instantiates maze of size rows*cols

        void generate(int rows, int cols);  // Generates a maze with dimensions rows*cols
        void print();                       // Prints the DisjSets as a maze
        void show();                        // Shows the maze visually without numbers
        void solve();                       // Solves the maze, printing the path and its length
};

#include "maze.cpp"