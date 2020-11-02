// EXERCISE 3.a
// Constructor taking no arguments
// Generating a maze of 1x1 in dimensions
Maze::Maze() {
    ds = new DisjSets(1);
    this->rows = this->cols = 1;
    this->solved = false;
}

// EXERCISE 3.b
// Constructor taking rows and cols
// Generating a maze with those dimensions
Maze::Maze(int rows, int cols) {
    this->generate(rows, cols);
}

// EXERCISE 3.b
// Generate maze method
// Generates a maze with dimensions rows*cols
// Worst case time complexity is theoretically infinite since our random direction
// COMPLEXITY: The time complexity of this algorithm results in going through every 
// element in the DisjSets instance once, and once more for backtrcking,
// meaning the time complexity becomes O(2*rows*cols) = O(rows*cols),
// which means it is linear in the number of elements in the DisjSets
void Maze::generate(int rows, int cols) {
    this->rows = rows;                  // Setting maze dimensions
    this->cols = cols;                  // Setting maze dimensions
    int length = rows*cols;             // DisjSets length of vector s
    this->ds = new DisjSets(length);    // Create new DisjSets of length

    this->solution.clear(); // Clear any previous solution
    this->solved = false;   // The newly generated maze will not be solved

    int curr = length-1;    // Start on the last cell of the maze
    srand(time(0));

    // This do-while loop chooses a wall to break down until all cells are in the same set
    do {
        vector<direction> dir_list; // List of direction that are allowed

        // Determine what walls can be broken down
        // We can move up
        if (!(curr < cols)) { // If we are not on the top side AND the two cells aren't already in the same set
            if (!(this->ds->find(curr) == this->ds->find(curr - cols))) {
                dir_list.push_back(UP);
            }
        }
        // We can move right
        if (!((curr+1) % cols == 0)) { // If we are not on the right side AND the two cells aren't already in the same set
            if (!(this->ds->find(curr) == this->ds->find(curr + 1))) {
                dir_list.push_back(RIGHT);
            }
        }
        // We can move down
        if (!(curr >= length-cols)) { // If we are not on the bottom side AND the two cells aren't already in the same set
             if (!(this->ds->find(curr) == this->ds->find(curr + cols))) {
                dir_list.push_back(DOWN);
            }
        }
        // We can move left
        if (!(curr % cols == 0)) { // If we are not on the left side AND the two cells aren't already in the same set
            if (!(this->ds->find(curr) == this->ds->find(curr - 1))) {
                dir_list.push_back(LEFT);
            }
        }
        // After these statements we are left with a vector
        // containing all the directions we are allowed to move

        // Direction to go starts as NONE
        // as no direction has been found yet
        direction dir = NONE;
        // IF we have no direction to go
        // make direction BACK, to backtrack
        if (dir_list.empty()) {
            dir = BACK;
        }
        // ELSE take random entry into direction vector
        // to make the direction to go
        else {
            int int_dir = rand() % dir_list.size();
            dir = dir_list[int_dir];
        }

        // Break down wall
        switch(dir) {
            case UP:
                {
                    int top = curr - cols;              // Calculate number of the cell on top
                    this->ds->unionSets(top, curr);     // Union the curr cell and the one on top
                    curr = top;                         // move curr to the top cell
                }
                break;
            case RIGHT:
                {
                    int right = curr + 1;               // Calculate number of the cell to the right
                    this->ds->unionSets(right, curr);   // Union the curr cell and the one to the right
                    curr = right;                       // move curr to the cell to the right
                }
                break;
            case DOWN:
                {
                    int bot = curr + cols;              // Calculate number of the cell on the bottom
                    this->ds->unionSets(bot, curr);     // Union the curr cell and the one on the bottom
                    curr = bot;                         // move curr to the bottom cell
                }
                break;
            case LEFT:
                {
                    int left = curr - 1;                // Calculate number of the cell to the left
                    this->ds->unionSets(left, curr);    // Union the curr cell and the one to the left
                    curr = left;                        // move curr to the cell to the left
                }
                break;
            case BACK:
                {
                    curr = this->ds->s[curr];   // Move curr to its parent to backtrack
                }
                break;
            default:
                break;
        }
    // At the end when all are in the same set,
    // the algorithm will backtrack until we are
    // back at the end, where we started
    } while (curr != length-1);
}

// Internal function
// to dynamically find the cell_width
// depending on how long the disjsets is
int Maze::cell_width() {
    int width = 0;
    for (int length = rows*cols*10; length >= 1; length /= 10) {
        width++;
    }
    return width;
}

// Internal method
// to check if two cells are related
bool Maze::is_related(int a, int b) {
    if (ds->s[a] == b || ds->s[b] == a) {
        return true;
    }
    return false;
}

void Maze::print_vertical(int &curr, int &cell_width) {
    _print_vertical(curr, cell_width, false);
    curr -= cols;
    _print_vertical(curr, cell_width, true);
}

void Maze::_print_vertical(int &curr, int &cell_width, bool print_character) {
    for (int c = 0; c < cols; c++, curr++) {
        bool in_solution = is_in_solution(curr);
        if (curr % cols == 0) {
            cout << "|";
        }

        int curr_number_width = 0;
        if (curr == 0) {            // EDGE CASE for very first cell
            curr_number_width++;
        }
        for (int w = curr; w >= 1; w /= 10) {
            curr_number_width++;
        }

        // Detmerine to print numbers or not
        if (this->show_num) {
            if (print_character) {
                for (int b = cell_width-curr_number_width; b > 0; b--) {
                    cout << " ";
                }
                cout << curr;
            }
            else {
                for (int b = 0; b < cell_width; b++) {
                    cout << " ";
                }
            }
            cout << " ";
        }
        else {  // If we don't print number, see if the maze has been solved
            if (solved) {
                // If it is in the solution vector
                // Print a character in middle of the cell to show this
                if (in_solution) {
                    if (print_character) {
                        for (int w = 0; w <= cell_width; w++){
                            // RIGHT
                            if (is_in_solution(curr+1) && is_related(curr, curr+1) && !(is_in_solution(curr-1) && is_related(curr, curr-1))) {
                                if (w >= cell_width/2) {
                                    cout << "\x1b[48;5;" << 57 << "m" << " " << "\033[0m";
                                }
                                else {
                                    cout << " ";
                                }
                            }
                            // LEFT
                            else if (is_in_solution(curr-1) && is_related(curr, curr-1) && !(is_in_solution(curr+1) && is_related(curr, curr+1))) {
                                if (w <= cell_width/2) {
                                    cout << "\x1b[48;5;" << 57 << "m" << " " << "\033[0m";
                                }
                                else {
                                    cout << " ";
                                }
                            }
                            // BOTH
                            else if (is_in_solution(curr-1) && is_in_solution(curr+1) && is_related(curr, curr-1) && is_related(curr, curr+1)) {
                                cout << "\x1b[48;5;" << 57 << "m" << " " << "\033[0m";
                            }
                            else {
                                if (w == cell_width/2) {
                                    cout << "\x1b[48;5;" << 57 << "m" << " " << "\033[0m";
                                }
                                else {
                                    cout << " ";
                                }
                            }
                        }
                    }
                    else if ((in_solution && is_in_solution(curr-cols) && is_related(curr, curr-cols)) || curr==0) {
                        for (int w = 0; w < cell_width; w++) {
                            if (w == cell_width/2) {
                                cout << "\x1b[48;5;" << 57 << "m" << " " << "\033[0m";
                            }
                            else {
                                cout << " ";
                            }
                        }
                        cout << " ";
                    }
                    else {
                        for (int w = 0; w <= cell_width; w++) {
                            cout << " ";
                        }
                    }
                }
                else {
                    for (int w = 0; w <= cell_width; w++){
                        cout << " ";
                    }
                }
            }
            else {
                for (int w = 0; w <= cell_width; w++){
                    cout << " ";
                }
            }
        }

        if ((curr+1) % cols == 0) {
            cout << "|" << endl;
        }
        else if (is_related(curr, curr+1)) {   // relation check to right
            if (!this->show_num && print_character && solved && in_solution && is_in_solution(curr+1)) {
                cout << "\x1b[48;5;" << 57 << "m" << " " << "\033[0m";
            }
            else {
                cout << " ";
            }
        }
        else {
            cout << "|";
        }
    }
}

void Maze::print_horizontal(int &curr, int &cell_width) {
   for (int c = 0; c < cols; ++c, ++curr) {
        if (curr % cols == 0) {
            cout << "|";
        }

        if (is_related(curr, curr+cols)) {
            if (this->show_num) {
                for (int w = 0; w <= cell_width; w++){
                    cout << " ";
                }
            }
            else {
                if ((solved && is_in_solution(curr) && is_in_solution(curr+cols))){
                    for (int w = 0; w < cell_width; w++) {
                        if (w == cell_width/2) {
                            cout << "\x1b[48;5;" << 57 << "m" << " " << "\033[0m";
                        }
                        else {
                            cout << " ";
                        }
                    }
                    cout << " ";
                }
                else {
                    for (int w = 0; w <= cell_width; w++) {
                        cout << " ";
                    }
                }
            }
        }
        else {
            for (int w = 0; w <= cell_width; w++){
                cout << "_";
            }
        }

        if ((curr+1) % cols == 0) {
            cout << "|" << endl;
        }
        else if (!(is_related(curr, curr+1))) {
            cout << "|";
        }
        else {
            cout << "_";
        }
    }
}

bool Maze::is_in_solution(int curr) {
    for (int i = 0; i < solution.size(); i++) {
        if (curr == solution[i]) {
            return true;
        }
    }
    return false;
}

void Maze::_print() {
    int length = rows*cols;
    int cell_width = this->cell_width();

    // Print top boundary
    cout << "_";
    for (int w = 0; w <= cell_width; w++){
        cout << " ";
    }
    for (int c = 0; c < cols-1; c++) {
        for (int w = 0; w <= cell_width; w++){
            cout << "_";
        }
        cout << "_";
    }
    cout << "_";
    cout << endl;

    // Iterate through maze
    int curr = 0;
    while (curr < length-cols) {
        // Print numbers an vertical lines
        print_vertical(curr, cell_width);
        // Horizontal lines inbetween
        if (!(curr >= length-cols)) {
            curr -= cols;
            print_horizontal(curr, cell_width);
        }
    }
    // Horizontal lines inbetween
    // *last line
    curr -= cols;
    if (!(curr >= length-cols)) {
        print_horizontal(curr, cell_width);
    }
    // Print numbers an vertical lines
    // *last line
    print_vertical(curr, cell_width);
    
    // Print bottom boundary
    curr -= cols;
    cout << "|";
    for (int c = 0; c < cols-1; c++, curr++) {
        for (int w = 0; w <= cell_width; w++){
           cout << "_";
        }
        //cout << "____";
        if (!(is_related(curr, curr+1))) {
            cout << "|";
        }
        else {
            cout << "_";
        }
    }
    for (int w = 0; w <= cell_width; w++){
        if (is_in_solution(curr)) {
            if (w == cell_width/2) {
                cout << "\x1b[48;5;" << 57 << "m" << " " << "\033[0m";
            }
            else {
                cout << " ";
            }
        }
        else {
            cout << " ";
        }
    }
    cout << "|" << endl;
}

// EXERCISE 3.c
// Method to print the maze in the terminal with the cell numbers
// Calls internal print functions
void Maze::print() {
    this->show_num = true;
    this->_print();
}

// Method to show the maze visually without cell numbers
// Shows the solution path if the maze has been solved
void Maze::show() {
    this->show_num = false;
    this->_print();
}

// EXERCISE 3.d
// Solve method
// Prints the solution to the current maze
// Does by starting at the first cell = 0,
// keeps iterating to the parent of the current cell
// ending when we have reached the last cell
// COMPLEXITY: The time complexity for this method is
// linear in the number of cells in the solution path
// meaning worst case time complexity is O(rows*cols),
// but most of the time the solution is much shorter
// and doesn't span the entire maze
void Maze::solve() {
    this->solved = true;

    cout << "The path that solves the maze is:" << endl;
    for (int curr = 0; curr >= 0; curr = this->ds->s[curr]) {
        solution.push_back(curr);
        cout << curr << " ";
    }
    cout << endl;
    cout << "Path length: " << solution.size() << endl;
}