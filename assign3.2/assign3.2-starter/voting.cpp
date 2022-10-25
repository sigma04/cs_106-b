// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "voting.h"
#include "testing/SimpleTest.h"
#include "map.h" // for map
using namespace std;

// calculate the sum of vector
int calVecSum(Vector<int>& vec){
    int result = 0;
    for (auto elem : vec){
        result += elem;
    }
    return result;
}

#define dfs

#ifdef btr
// solve problem using deep first seraching method
void criticalVotes(Vector<int>& blocks, int blockIndex, int index,
                  int& subsetSum, int blockSum, int& votes){
    // if blocks[blockIndex] is smaller than the sum of subset, stop recursion for saving time
    if (subsetSum > blockSum / 2 ){
        return ;
    }
    for (int i = index; i < blocks.size(); i++){
        // skip the element of blocks
        if (i == blockIndex){
            continue;
        }
        subsetSum += blocks[i];
        votes += int( (blocks[blockIndex] + subsetSum > blockSum / 2) && (subsetSum <= blockSum / 2) );
        criticalVotes(blocks, blockIndex, i + 1, subsetSum, blockSum, votes);
        subsetSum -= blocks[i];
    }
}

// return powerindex of each vote in the blocks
Vector<int> computePowerIndexes(Vector<int>& blocks)
{
    Vector<int> result;
    Map<int, int> resultTable;
    int blockSum = calVecSum(blocks);
    for (int i = 0; i < blocks.size(); i++){
        if (resultTable.containsKey(blocks[i])){
            result.add(resultTable[blocks[i]]);
        }
        else {
            int votes = 0;
            int subsetSum = 0;
            criticalVotes(blocks, i, 0, subsetSum, blockSum, votes);
            result.add(votes);
            resultTable.put(blocks[i], votes);
        }
    }
    int sum = calVecSum(result);
    for (int i = 0; i < blocks.size(); i++){
        result[i] = int(float(result[i]) / sum * 100);
    }
    return result;
}
#endif

#ifdef dfs
// solve problem using deep first seraching method
int criticalVotes(Vector<int>& blocks, int blockIndex, int index, int subsetSum, int blockSum){
    // if blocks[blockIndex] is smaller than the sum of subset, stop recursion for saving time
    if (subsetSum > blockSum / 2 ){
        return 0;
    }
    // base case, return the result if it is critical vote
    if (index == blocks.size()){
        return ( (blocks[blockIndex] + subsetSum > blockSum / 2) && (subsetSum <= blockSum / 2) );
    }
    // recursive case 1 : skip element of blocks if index == blockIndex
    else if (index == blockIndex){
        return  criticalVotes(blocks, blockIndex, index + 1, subsetSum, blockSum);
    }
    // recursive case 2 : include / exclude for calculating the sum of subset
    else {
        return criticalVotes(blocks, blockIndex, index + 1, subsetSum + blocks[index], blockSum) +
                criticalVotes(blocks, blockIndex, index + 1, subsetSum, blockSum);
    }
}

// return powerindex of each vote in the blocks
Vector<int> computePowerIndexes(Vector<int>& blocks)
{
    Vector<int> result;
    Map<int, int> resultTable;  // store result calculate to avoid repeat element
    int blockSum = calVecSum(blocks);
    for (int i = 0; i < blocks.size(); i++){
        if (resultTable.containsKey(blocks[i])){
            result.add(resultTable[blocks[i]]);
        }
        else {
            int votes = criticalVotes(blocks, i, 0, 0, blockSum);
            result.add(votes);
            resultTable.put(blocks[i], votes);
        }
    }
    int sum = calVecSum(result);
    for (int i = 0; i < blocks.size(); i++){ // calculate percent of each element
        result[i] = int(float(result[i]) / sum * 100);
    }
    return result;
}

#endif
/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Test power index, blocks 50-49-1") {
    Vector<int> blocks = {50, 49, 1};
    cout << endl <<  "block sum: " << calVecSum(blocks) << endl;
    Vector<int> expected = {60, 20, 20};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Test power index, blocks Hempshead 1-1-3-7-9-9") {
    Vector<int> blocks = {1, 1, 3, 7, 9, 9};
    cout << endl <<  "block sum: " << calVecSum(blocks) << endl;
    Vector<int> expected = {0, 0, 0, 33, 33, 33};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Test power index, blocks CA-TX-NY 55-38-39") {
    Vector<int> blocks = {55, 38, 29};
    Vector<int> expected = {33, 33, 33};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Test power index, blocks CA-TX-GA 55-38-16") {
    Vector<int> blocks = {55, 38, 16};
    Vector<int> expected = {100, 0, 0};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Test power index, blocks EU post-Nice") {
    // Estonia is one of those 4s!!
    Vector<int> blocks = {29,29,29,29,27,27,14,13,12,12,12,12,12,10,10,10,7,7,7,7,7,4,4,4,4,4,3};
    Vector<int> expected = {8, 8, 8, 8, 7, 7, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Time power index operation") {
    Vector<int> blocks;
    for (int i = 0; i < 15; i++) {
        blocks.add(randomInteger(1, 10));
    }
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
}


