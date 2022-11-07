#include "pqheap.h"
#include "error.h"
#include "random.h"
#include "strlib.h"
#include "datapoint.h"
#include "testing/SimpleTest.h"
using namespace std;

const int INITIAL_CAPACITY = 10;
const int NONE = -1; // used as sentinel index

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
PQHeap::PQHeap() {
    _numAllocated = INITIAL_CAPACITY;
    _elements = new DataPoint[_numAllocated]();
    _numFilled = 0;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
PQHeap::~PQHeap() {
    delete[] _elements;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
void PQHeap::enqueue(DataPoint elem) {
    // the allocated space has been used out
    if (_numAllocated == _numFilled){
        DataPoint* old = _elements;
        _numAllocated *= 2;
        _elements = new DataPoint[_numAllocated];
        for (int i=0; i < _numFilled; i++){
            _elements[i] = old[i];
        }
        delete[] old;
    }
    // push elem into the _elements
    _elements[_numFilled] = elem;
    _numFilled++;
    // sort _elements from the end element to the root element
    int curIndex = _numFilled - 1;
    while (true){
        int parIndex = getParentIndex(curIndex);
        // has no parent element
        if (parIndex == NONE) {
            break;
        }
        // child element has smaller priority value than parent elment
        if (_elements[curIndex].priority < _elements[parIndex].priority){
            swap(curIndex, parIndex);
            // update curIndex to continue sorting
            curIndex = parIndex;
        }
        // already sorted
        else {
            break;
        }
    }
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
DataPoint PQHeap::peek() const {
    if (isEmpty()){
        error("PQHeap is empty!");
    }
    return _elements[0];
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
DataPoint PQHeap::dequeue() {
    DataPoint front = peek();
    // substitute the root element with the last element
    _elements[0] = _elements[size()-1];
    _numFilled--;
    // sort the rest elements, start from the root element
    if (_numFilled > 0){
        int curIndex = 0;
        while (true) {
            int lChild = getLeftChildIndex(curIndex);
            int rChild = getRightChildIndex(curIndex);
            // has left child and right child
            if (lChild != NONE && rChild != NONE){
                int minChild = (_elements[lChild].priority < _elements[rChild].priority)? lChild : rChild;
                if (_elements[curIndex].priority > _elements[minChild].priority) {
                    swap(curIndex, minChild);
                    curIndex = minChild;
                }
                // already sorted
                else break;
            }
            // has left child but no right child
            else if (lChild != NONE && rChild == NONE){
                if (_elements[curIndex].priority > _elements[lChild].priority) {
                    swap(curIndex, lChild);
                    curIndex = lChild;
                }
                // already sorted
                else break;
            }
            // has no child
            else {
                break;
            }
        }
    }
    return front;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
bool PQHeap::isEmpty() const {
    return size() == 0;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
int PQHeap::size() const {
    return _numFilled;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
void PQHeap::clear() {
    _numFilled = 0;
}

/*
 * Private member function. This helper exchanges the element at
 * indexA with the element at indexB.
 */
void PQHeap::swap(int indexA, int indexB) {
    DataPoint tmp = _elements[indexA];
    _elements[indexA] = _elements[indexB];
    _elements[indexB] = tmp;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
void PQHeap::printDebugInfo(string msg) const {
    cout << msg << endl;
    for (int i = 0; i < size(); i++) {
        cout << "[" << i << "] = " << _elements[i] << endl;
    }
}

/*
 * We strongly recommend implementing this helper function, which
 * should traverse the heap array and ensure that the heap property
 * holds for all elements in the array. If elements are found that
 * violate the heap property, an error should be thrown.
 */
void PQHeap::validateInternalState() const {
    /*
     * If there are more elements than spots in the array, we have a problem.
     */
    if (_numFilled > _numAllocated) error("Too many elements in not enough space!");

    /* Loop over the elements in the array and compare priority of
     * neighboring elements. If child element has larger priority
     * than the parent element, array elements are out of order with respect
     * to our intention. Use error to report this problem.
     */
    for (int i = 0; i < size(); i++) {
        int lChild = getLeftChildIndex(i);
        if (lChild != NONE){
            if (_elements[i].priority > _elements[lChild].priority) {
                printDebugInfo("validateInternalState");
                error("PQHeap has left child elements out of order at index " + integerToString(i));
            }
        }
        int rChild = getRightChildIndex(i);
        if (rChild != NONE){
            if (_elements[i].priority > _elements[rChild].priority) {
                printDebugInfo("validateInternalState");
                error("PQHeap has right child elements out of order at index " + integerToString(i));
            }
        }
    }
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the parent of the
 * specified child index. If this child has no parent, return
 * the sentinel value NONE.
 */
int PQHeap::getParentIndex(int child) const {
    int index = (child - 1) / 2;
    return (index >= 0 && index < child)? index : NONE;
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the left child of the
 * specified parent index. If this parent has no left child, return
 * the sentinel value NONE.
 */
int PQHeap::getLeftChildIndex(int parent) const {
    int index = 2 * parent + 1;
    return (index < size())? index : NONE;
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the right child of the
 * specified parent index. If this parent has no right child, return
 * the sentinel value NONE.
 */
int PQHeap::getRightChildIndex(int parent) const {
    int index = 2 * parent + 2;
    return (index < size())? index : NONE;
}

/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Add your own custom tests here! */
PROVIDED_TEST("PQHeap example from writeup") {
    PQHeap pq;

    pq.enqueue( { "Zoe", -3 } );
    pq.enqueue( { "Elmo", 10 } );
    pq.enqueue( { "Bert", 6 } );
    EXPECT_EQUAL(pq.size(), 3);
    pq.printDebugInfo("After enqueue 3 elements");

    pq.enqueue( { "Kermit", 5 } );
    EXPECT_EQUAL(pq.size(), 4);
    pq.printDebugInfo("After enqueue one more");

    DataPoint removed = pq.dequeue();
    DataPoint expected = { "Zoe", -3 };
    EXPECT_EQUAL(removed, expected);
    pq.printDebugInfo("After dequeue one");
}

PROVIDED_TEST("PQHeap, enqueue only, validate at every step") {
    PQHeap pq;

    pq.enqueue({ "e", 2.718 });
    pq.validateInternalState();
    pq.enqueue({ "pi", 3.14 });
    pq.validateInternalState();
    pq.enqueue({ "phi", 1.618 });
    pq.validateInternalState();
    EXPECT_EQUAL(pq.size(), 3);
}

PROVIDED_TEST("PQHeap: operations size/isEmpty/clear") {
    PQHeap pq;

    EXPECT(pq.isEmpty());
    pq.clear();
    EXPECT_EQUAL(pq.isEmpty(), pq.size() == 0);
    pq.enqueue({ "", 7 });
    EXPECT_EQUAL(pq.size(), 1);
    pq.enqueue({ "", 5 });
    EXPECT_EQUAL(pq.size(), 2);
    pq.enqueue({ "", 5 });
    EXPECT_EQUAL(pq.size(), 3);
    pq.clear();
    pq.validateInternalState();
    EXPECT(pq.isEmpty());
    EXPECT_EQUAL(pq.size(), 0);
}

PROVIDED_TEST("PQHeap: dequeue or peek on empty queue raises error") {
    PQHeap pq;
    DataPoint point = { "Programming Abstractions", 106 };

    EXPECT(pq.isEmpty());
    EXPECT_ERROR(pq.dequeue());
    EXPECT_ERROR(pq.peek());

    pq.enqueue(point);
    pq.dequeue();
    EXPECT_ERROR(pq.dequeue());
    EXPECT_ERROR(pq.peek());

    pq.enqueue(point);
    pq.clear();
    EXPECT_ERROR(pq.dequeue());
    EXPECT_ERROR(pq.peek());
}

PROVIDED_TEST("PQHeap, dequeue, validate at every step") {
    PQHeap pq;

    pq.enqueue({ "e", 2.718 });
    pq.enqueue({ "pi", 3.14 });
    pq.enqueue({ "phi", 1.618 });

    for (int i = 0; i < 3; i++) {
        pq.dequeue();
        pq.validateInternalState();
    }
}

PROVIDED_TEST("PQHeap, test enlarge array memory") {
    for (int size = 5; size <= 500; size *= 5) {
        PQHeap pq;

        for (int i = 1; i <= size; i++) {
            pq.enqueue({"", double(i) });
        }
        pq.validateInternalState();

        for (int i = 1; i <= size; i++) {
            DataPoint expected = {"", double(i) };
            EXPECT_EQUAL(pq.dequeue(), expected);
        }
    }
}

PROVIDED_TEST("PQHeap, sequence of mixed operations") {
    PQHeap pq;
    int size = 30;
    double val = 0;

    for (int i = 0; i < size; i++) {
        pq.enqueue({"", --val });
    }
    val = 0;
    for (int i = 0; i < pq.size(); i++) {
        DataPoint front = pq.peek();
        EXPECT_EQUAL(pq.dequeue(), front);
        pq.enqueue( { "", ++val });
    }
    EXPECT_EQUAL(pq.size(), size);
    val = 0;
    while (!pq.isEmpty()) {
        DataPoint expected = { "", ++val };
        EXPECT_EQUAL(pq.dequeue(), expected);
    }
}

PROVIDED_TEST("PQHeap stress test, cycle many random elements in and out") {
    PQHeap pq;
    int n = 0, maxEnqueues = 1000;
    double sumEnqueued = 0, sumDequeued = 0;

    setRandomSeed(42); // make test behavior deterministic

    DataPoint mostUrgent = { "", 0 };
    pq.enqueue(mostUrgent);
    while (true) {
        if (++n < maxEnqueues && randomChance(0.9)) {
            DataPoint elem = { "", randomInteger(-10, 10) + 0.5 };
            if (elem.priority < mostUrgent.priority) {
                mostUrgent = elem;
            }
            sumEnqueued += elem.priority;
            pq.enqueue(elem);
        } else {
            DataPoint elem = pq.dequeue();
            sumDequeued += elem.priority;
            EXPECT_EQUAL(elem, mostUrgent);
            if (pq.isEmpty()) break;
            mostUrgent = pq.peek();
        }
    }
    EXPECT_EQUAL(sumEnqueued, sumDequeued);
}

void fillQueue(PQHeap& pq, int n) {
    pq.clear(); // start with empty queue
    for (int i = 0; i < n; i++) {
        pq.enqueue({ "", randomReal(0, 10) });
    }
}

void emptyQueue(PQHeap& pq, int n) {
    for (int i = 0; i < n; i++) {
        pq.dequeue();
    }
}

PROVIDED_TEST("PQHeap timing test, fillQueue and emptyQueue") {
    PQHeap pq;
    int n = 20000;

    TIME_OPERATION(n, fillQueue(pq, n));
    TIME_OPERATION(n, emptyQueue(pq, n));
}

STUDENT_TEST("PQHeap enqueue timing analysis"){
    PQHeap pq;
    int n = 10000;
    for (int k = 1; k < 8; k++){
        TIME_OPERATION(n * k, fillQueue(pq, n * k));
        TIME_OPERATION(n * k, emptyQueue(pq, n * k));
    }
}



/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("PQHeap example from writeup, validate each step") {
    PQHeap pq;
    Vector<DataPoint> input = {
        { "R", 4 }, { "A", 5 }, { "B", 3 }, { "K", 7 }, { "G", 2 },
        { "V", 9 }, { "T", 1 }, { "O", 8 }, { "S", 6 } };

    pq.validateInternalState();
    for (DataPoint dp : input) {
        pq.enqueue(dp);
        pq.validateInternalState();
    }
    while (!pq.isEmpty()) {
        pq.dequeue();
        pq.validateInternalState();
    }
}
