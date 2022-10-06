// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "grid.h"
#include "maze.h"
#include "mazegraphics.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;


/* Find valid set of neighbors of cur in the maze.
 */
Set<GridLocation> generateValidMoves(Grid<bool>& maze, GridLocation cur) {
    Set<GridLocation> neighbors;

    //locations of neighbours in four direction of cur
    GridLocation east = {cur.row + 1, cur.col};
    GridLocation south = {cur.row, cur.col - 1};
    GridLocation west = {cur.row - 1, cur.col};
    GridLocation north = {cur.row, cur.col + 1};

    //if move is valid , add location of neighbor to the set
    if (maze.inBounds(east) && maze[east] ) {
        neighbors.add(east);
    }
    if (maze.inBounds(south) && maze[south] ) {
        neighbors.add(south);
    }
    if (maze.inBounds(west) && maze[west] ) {
        neighbors.add(west);
    }
    if (maze.inBounds(north) && maze[north] ) {
        neighbors.add(north);
    }
    return neighbors;
}

/* Test if the path from the entrance to the exit of maze is valid.
 */
void validatePath(Grid<bool>& maze, Stack<GridLocation> path) {
    /* If you find a problem with the path, call error() to report it.
     * If the path is a valid solution, then this function should run to completion
     * without throwing any errors.
     */
    GridLocation mazeExit = {maze.numRows()-1,  maze.numCols()-1};
    if (path.peek() != mazeExit) {
        error("Path does not end at maze exit");
    }

    GridLocation current;
    Set<GridLocation> passed;
    while ( !path.isEmpty() ) {
        current = path.pop();

        // Test if current location has been passed for more than once.
        if (passed.contains(current)) {
            error("Path has repeated locations.");
        }
        passed.add(current);

        if (path.isEmpty()) {
            // Current is the first location of path, so test if current
            // is same as entrance of maze.
            if (current.row != 0 || current.col != 0 ) {
                error("Path does not start from the maze entrace.");
            }
        }
        else {
            // Current is not the first location of the path.
            if (!generateValidMoves(maze, current).contains(path.peek())) {
                error("Path is not valid, there exits wall or side or teleport in the path.");
            }
        }
    }
}

/* Find a path from entrace to the exit of maze.
 */
Stack<GridLocation> solveMaze(Grid<bool>& maze) {
    MazeGraphics::drawGrid(maze);
    Stack<GridLocation> path;
    Stack<GridLocation> pathToSet; // Copy of current path, used to convert stack to set.
    Stack<GridLocation> pathNew;  // Copy of current path, used to find new path to add to Queue
    Queue<Stack<GridLocation>> pathQueue;

    GridLocation start = {0, 0};  // entrance location of maze
    GridLocation exit = {maze.numRows() - 1, maze.numCols() - 1}; // exit location of maze
    Set<GridLocation> neighbours;  // store valide neighbors of last location in path
    Set<GridLocation> passedLocations; // store the visited locations in current path

    // Start to find path from the entrance of maze.
    path.push(start);
    pathQueue.enqueue(path);

    while(!pathQueue.isEmpty()) {
        path = pathQueue.dequeue();

        // draw maze and current path
//        MazeGraphics::drawGrid(maze);
//        MazeGraphics::highlightPath(path, "red", 50);

        // The path from entrance to exit of maze is finded.
        if (path.peek() == exit) {
            break;
        }

        // convert pathToSet from stack to set
        pathToSet = path;
        passedLocations = {};
        while(!pathToSet.isEmpty()) {
            passedLocations.add( pathToSet.pop() );
        }

        // find valid neighbours of current location
        neighbours = generateValidMoves(maze, path.peek());
        for (GridLocation loc : neighbours) {
            // has not been visited
            if (!passedLocations.contains(loc)) {
                pathNew = path;
                // push the new path into the Queue
                pathNew.push(loc);
                pathQueue.enqueue(pathNew);
            }
        }
    }

    return path;
}

/*
 * The given readMazeFile function correctly reads a well-formed
 * maze from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readMazeFile(string filename, Grid<bool>& maze) {
    /* The following code reads data from the file into a Vector
     * of strings representing the lines of the file.
     */
    ifstream in;

    if (!openFile(in, filename))
        error("Cannot open file named " + filename);

    Vector<string> lines;
    readEntireFile(in, lines);

    /* Now that the file data has been read into the Vector, populate
     * the maze grid.
     */
    int numRows = lines.size();        // rows is count of lines
    int numCols = lines[0].length();   // cols is length of line
    maze.resize(numRows, numCols);     // resize grid dimensions

    for (int r = 0; r < numRows; r++) {
        if (lines[r].length() != numCols) {
            error("Maze row has inconsistent number of columns");
        }
        for (int c = 0; c < numCols; c++) {
            char ch = lines[r][c];
            if (ch == '@') {        // wall
                maze[r][c] = false;
            } else if (ch == '-') { // corridor
                maze[r][c] = true;
            } else {
                error("Maze location has invalid character: '" + charToString(ch) + "'");
            }
        }
    }
}

/* The given readSolutionFile correctly reads a path from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readSolutionFile(string filename, Stack<GridLocation>& soln) {
    ifstream in;

    if (!openFile(in, filename)) {
        error("Cannot open file named " + filename);
    }

    if (!(in >> soln)) {// if not successfully read
        error("Maze solution did not have the correct format.");
    }
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("generateValidMoves on location in the center of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation center = {1, 1};
    Set<GridLocation> expected = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, center), expected);
}

PROVIDED_TEST("generateValidMoves on location on the side of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation side = {0, 1};
    Set<GridLocation> expected = {{0,0}, {0,2}, {1, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, side), expected);
}

PROVIDED_TEST("generateValidMoves on corner of 2x2 grid with walls") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    GridLocation corner = {0, 0};
    Set<GridLocation> expected = {{1, 0}};

    EXPECT_EQUAL(generateValidMoves(maze, corner), expected);
}

PROVIDED_TEST("validatePath on correct solution") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Stack<GridLocation> soln = { {0 ,0}, {1, 0}, {1, 1} };

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on correct solution loaded from file for medium maze") {
    Grid<bool> maze;
    Stack<GridLocation> soln;
    readMazeFile("res/5x7.maze", maze);
    readSolutionFile("res/5x7.soln", soln);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on correct solution loaded from file for large maze") {
    Grid<bool> maze;
    Stack<GridLocation> soln;
    readMazeFile("res/25x33.maze", maze);
    readSolutionFile("res/25x33.soln", soln);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on invalid path should raise error") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Stack<GridLocation> not_end_at_exit = { {1, 0}, {0, 0} };
    Stack<GridLocation> not_begin_at_entry = { {1, 0}, {1, 1} };
    Stack<GridLocation> go_through_wall = { {0 ,0}, {0, 1}, {1, 1} };
    Stack<GridLocation> teleport = { {0 ,0}, {1, 1} };
    Stack<GridLocation> revisit = { {0 ,0}, {1, 0}, {0, 0}, {1, 0}, {1, 1} };

    EXPECT_ERROR(validatePath(maze, not_end_at_exit));
    EXPECT_ERROR(validatePath(maze, not_begin_at_entry));
    EXPECT_ERROR(validatePath(maze, go_through_wall));
    EXPECT_ERROR(validatePath(maze, teleport));
    EXPECT_ERROR(validatePath(maze, revisit));
}

PROVIDED_TEST("solveMaze on file 5x7") {
    Grid<bool> maze;
    readMazeFile("res/5x7.maze", maze);
    Stack<GridLocation> soln = solveMaze(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("solveMaze on file 21x23") {
    Grid<bool> maze;
    readMazeFile("res/21x23.maze", maze);
    Stack<GridLocation> soln = solveMaze(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

// TODO: add your test cases here

STUDENT_TEST("generateValideMoves on location on the center of 3x3 grid full of walls"){
    Grid<bool> maze = {
        {true, false, true},
        {false, true, false},
        {true, false, true},
    };
    GridLocation center = {1, 1};
    Set<GridLocation> expected = {};
    EXPECT_EQUAL(generateValidMoves(maze, center), {});
}
