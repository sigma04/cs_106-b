/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include "queue.h"
#include "testing/SimpleTest.h"
using namespace std;

/* Merge two sorted list of numbers.
 */
Queue<int> binaryMerge(Queue<int> a, Queue<int> b) {
    Queue<int> result;
    int last; // store the last integer enqueued in the result , to judge if enqueue a or b is sorted
    // a and b are both not empty enqueue
    while(!a.isEmpty() && !b.isEmpty()){
        if (a.peek() < b.peek()){
            // if (!result.isEmpyt) is true, variable last has been given a value, and
            // if a and b are both sorted, the result  should also be sorted
            if (!result.isEmpty() && last > a.peek()){
                error("inputs is not sorted");
            }
            last = a.dequeue();
            result.enqueue(last);
        }
        else {
            if (!result.isEmpty() && last > b.peek()){
                error("inputs is not sorted");
            }
            last = b.dequeue();
            result.enqueue(last);
        }
    }
    // b is empty , or a is longer than b
    while(!a.isEmpty()){
        if (!result.isEmpty() && last > a.peek()){
            error("inputs is not sorted");
        }
        last = a.dequeue();
        result.enqueue(last);
    }
    // a is emtpy , or b is longer than a
    while(!b.isEmpty()){
        if (!result.isEmpty() && last > b.peek()){
            error("inputs is not sorted");
        }
        last = b.dequeue();
        result.enqueue(last);
    }
    return result;
}

/*
 * This function assumes correct functionality of the previously
 * defined binaryMerge function and makes use of this function to
 * iteratively merge a collection of sequences, starting off with
 * an empty sequence and progressively merging in one sequence at
 * a time. This function is provided for you fully implemented –
 * it does not need to modified at all.
 */
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = binaryMerge(q, result);
    }
    return result;
}

/* Use recursive method to merge Queue in the Vector.
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;
    // base case for empty Vector
    if (all.size() == 0){
        return result;
    }
    // base case for Vector of size 1
    else if (all.size() == 1){
        return binaryMerge(all[0], {});
    }
    // not the most base case , but to aovoiding deep recursion for decreasing time of running
    else if (all.size() == 2){
        return binaryMerge(all[0], all[1]);
    }
    else {
        Vector<Queue<int>> left = all.subList(0, all.size()/2);
        Vector<Queue<int>> right = all.subList(all.size()/2);
        return binaryMerge( recMultiMerge(left), recMultiMerge(right) );
    }
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

PROVIDED_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

PROVIDED_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

PROVIDED_TEST("recMultiMerge, compare to naiveMultiMerge") {
    int n = 20;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

PROVIDED_TEST("Time binaryMerge operation") {
    int n = 1000000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

PROVIDED_TEST("Time naiveMultiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}
PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].enqueue(input.dequeue());
    }
}

STUDENT_TEST("recMultiMerge test for empty Vector"){
    Vector<Queue<int>> a = {};
    EXPECT_EQUAL(recMultiMerge(a), {});
}

STUDENT_TEST("recMultiMerge test for Vector contains empty Queue"){
    Vector<Queue<int>> a = {{}, {}, {}};
    EXPECT_EQUAL(recMultiMerge(a), {});
}
