/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "backtracking.h"
#include "gridlocation.h"
#include "grid.h"
#include "set.h"
#include "lexicon.h"
#include "testing/SimpleTest.h"
using namespace std;

/* Calculate the score of word.
 */
int points(string str) {
    // score of str which has less than 4 chracters equals 0
    if (str.length() < 4){
        return 0;
    }
    // score of str which has more than 4 chracters
    else {
        return str.length() - 3;
    }
}

#define compress
#ifdef compress
/* Find word and get score from the current location given.
 */
void findWord(Grid<char>& board, Lexicon& lex,
              GridLocation curLoc, Set<GridLocation>& visitedLoc,
              string& curWord, Set<string>& visitedWord, int& score){
    // basecase : the visited path conatins the current location OR current locations is not bounded in the board
    if (visitedLoc.contains(curLoc) || !board.inBounds(curLoc) ){
        return;
    }
    // recursive case
    else {
        visitedLoc.add(curLoc);
        curWord += board[curLoc];
        // for saving time, only if lex contains word with the prefix
        if (lex.containsPrefix(curWord)){
            // curWord.length() > 3 : avoid scoreing unless the length of word is larger than 3 for saveing time;
            // lex.contains(curWord) : if lex contains curword, add the points(curword) to the score;
            // !visitedWord.contains(curWord) :  add score only new word is finded
            if (curWord.length() > 3 && lex.contains(curWord) && !visitedWord.contains(curWord)){
                score += points(curWord);
                visitedWord.add(curWord);
            }
            for (int i = -1; i < 2; i++){
                for (int j = -1; j < 2; j++){
                    findWord(board, lex, {curLoc.row + i, curLoc.col + j}, visitedLoc, curWord, visitedWord, score);
                }
            }
        }
        // undo the modification for using reference parameter
        visitedLoc.remove(curLoc);
        curWord.pop_back();
        return;
    }
}
#endif

#ifdef origin
void findWord(Grid<char>& board, Lexicon& lex,
              GridLocation curLoc, Set<GridLocation>& visitedLoc,
              string& curWord, Set<string>& visitedWord, int& score){
    // basecase 1 : the visited path conatins the current location
    if (visitedLoc.contains(curLoc)){
        return;
    }
    // basecase 2 : current locations is not bounded in the board
    else if (!board.inBounds(curLoc)){
        return;
    }
    // recursive case
    else {
        visitedLoc.add(curLoc);
        curWord += board[curLoc];
//        cout << endl << "curWord : " << curWord;
        // for saving time if lex has no word with the prefix
        if (curWord.length() > 0 && !lex.containsPrefix(curWord)){
            // undo the modification
            visitedLoc.remove(curLoc);
            curWord.pop_back();
            return;
        }
        else {
            // curWord.length() > 3 : avoid scoreing unless the length of word is larger than 3;
            // lex.contains(curWord) : if lex contains curword, add the points(curword) to the score;
            // !visitedWord.contains(curWord) :  add score only new word is finded
            if (curWord.length() > 3 && lex.contains(curWord) && !visitedWord.contains(curWord)){
                score += points(curWord);
                visitedWord.add(curWord);
//                cout << endl << "scored curWord: " << curWord;
            }
            for (int i = -1; i < 2; i++){
                for (int j = -1; j < 2; j++){
                    if (i == 0 && j == 0){   // skip center location itself
                        continue;
                    }
                    findWord(board, lex, {curLoc.row + i, curLoc.col + j}, visitedLoc, curWord, visitedWord, score);
                }
            }
            // undo the modification
            visitedLoc.remove(curLoc);
            curWord.pop_back();
            return;
        }
    }
}
#endif

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
int scoreBoard(Grid<char>& board, Lexicon& lex) {
    Set<GridLocation> visitedLoc; // store locations has been visited in the grid
    string curWord = "";  // store the current word make up of the characters in each grid location
    Set<string> visitedWord;  // store the word finded, to avoid scoring by the same word many times
    int score = 0;  // store score by far
    for (GridLocation curLoc: board.locations()){
        findWord(board, lex, curLoc, visitedLoc, curWord, visitedWord, score);
    }
    return score;
}

/* * * * * * Test Cases * * * * * */

/* Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */
static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

PROVIDED_TEST("Load shared Lexicon, confirm number of words") {
    Lexicon lex = sharedLexicon();
    EXPECT_EQUAL(lex.size(), 127145);
}

PROVIDED_TEST("Test point scoring") {
    EXPECT_EQUAL(points("and"), 0);
    EXPECT_EQUAL(points("quad"), 1);
    EXPECT_EQUAL(points("quint"), 2);
    EXPECT_EQUAL(points("sextet"), 3);
    EXPECT_EQUAL(points("seventh"), 4);
    EXPECT_EQUAL(points("supercomputer"), 10);
}

PROVIDED_TEST("Test scoreBoard, board contains no words, score of zero") {
    Grid<char> board = {{'B','C','D','F'}, //no vowels, no words
                        {'G','H','J','K'},
                        {'L','M','N','P'},
                        {'Q','R','S','T'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 0);
}

PROVIDED_TEST("Test scoreBoard, board contains one word, score of 1") {
    Grid<char> board = {{'C','_','_','_'},
                        {'Z','_','_','_'},
                        {'_','A','_','_'},
                        {'_','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, alternate paths for same word, still score of 1") {
    Grid<char> board = {{'C','C','_','_'},
                        {'C','Z','C','_'},
                        {'_','A','_','_'},
                        {'R','_','R','_'}};
    int result = scoreBoard(board, sharedLexicon());
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, small number of words in corner of board") {
    Grid<char> board = {{'L','I','_','_'},
                        {'M','E','_','_'},
                        {'_','S','_','_'},
                        {'_','_','_','_'}};
    Set<string> words = {"SMILE", "LIMES", "MILES", "MILE", "MIES", "LIME", "LIES", "ELMS", "SEMI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()),  2 + 2 + 2 + 1 + 1 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, small number of words") {
    Grid<char> board = {{'E','Z','R','R'},
                        {'O','H','I','O'},
                        {'N','J','I','H'},
                        {'Y','A','H','O'}};
    Set<string> words = { "HORIZON", "OHIA", "ORZO", "JOHN", "HAJI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 4 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, medium number of words") {
    Grid<char> board = {{'O','T','H','X'},
                        {'T','H','T','P'},
                        {'S','S','F','E'},
                        {'N','A','L','T'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 76);
}

PROVIDED_TEST("Test scoreBoard, full board, large number of words") {
    Grid<char> board = {{'E','A','A','R'},
                        {'L','V','T','S'},
                        {'R','A','A','N'},
                        {'O','I','S','E'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 234);
}
