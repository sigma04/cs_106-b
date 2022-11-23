#include "listnode.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;

// Divide list front to 3 different list begin with pionter low,pivot,high.
// list in pivot has equal data of the first element in front,
// list in low has data lowwer than that in pivot,
// list in high has data higher than that in pivot,
void partition(ListNode*& low, ListNode*& pivot, ListNode*& high, ListNode* front){
    // initialization the pointer to store 3 partition divided
    low = pivot = high = nullptr;
    // list in front has no element
    if (front == nullptr) return;
    // at leat 1 element exist in list front
    else {
        // store the 1st node of front into pivot and set the end of pivot to nullptr
        ListNode* cur = front->next;
        pivot = front;
        pivot->next = nullptr;
        // use cur to iterate the rest node in list front
        while(cur != nullptr){
            // sotre the current node and move cur to the next node
            ListNode* temp = cur;
            cur = cur->next;
            // lower than pivot's data, add the node to the list low
            if (temp->data < pivot->data) {
                ListNode* lowTmp = low;
                low = temp;
                low->next = lowTmp;
            }
            // equal to pivot's data, add the node to the list pivot
            else if (temp->data == pivot->data){
                ListNode* pivotTmp = pivot;
                pivot = temp;
                pivot->next = pivotTmp;
            }
            // higher than pivot's data, add the node to the list high
            else {
                ListNode* highTmp = high;
                high = temp;
                high->next = highTmp;
            }
        }
    }
}

// Concatenqate 3 list in low, pivot, hight togeter, and sotre the head pointer into pointer front.
// The head node of list front has the lowest data.
// The tail node of list front has the highest data.
void concatenate(ListNode* low, ListNode* pivot, ListNode* high, ListNode*& front){
    // set pointer front to the head of list high
    front = high;
    // join tail node of list pivot to the head node of list high
    ListNode* temp = pivot;
    if (temp != nullptr){
        // move the temp to the tail node of list pivot
        while (temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = front;
        front = pivot;
    }
    // join tail node of list low to the head node of list pivot
    temp = low;
    if (temp != nullptr){
        // move the temp to the tail node of list low
        while (temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = front;
        front = low;
    }
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
void quickSort(ListNode*& front) {
    // base case
    if (front == nullptr){
        return;
    }
    // recursive case
    else {
        ListNode *low, *pivot, *high;
        low = pivot = high = nullptr;
        partition(low, pivot, high, front);
        quickSort(low);
        quickSort(high);
        concatenate(low, pivot, high, front);
    }
}


/* * * * * * Test Code Below This Point * * * * * */

/* TODO: Write your own student tests below to test your sorting helper
 * functions and overall sorting algorithm correctness. We have provided
 * the skeleton of some tests below to help you get started with this
 * process.
 */

/*
 * We have provided this utility function as a convenience. This
 * function traverses the linked list represented by the provided
 * front pointer and prints out the data stored in the list along
 * the way in a convenient format. You may find it to be helpful to
 * use this function as a debugging aid.
 */
void printList(ListNode* front) {
   cout << "{";
   for (ListNode *cur = front; cur != nullptr; cur = cur->next) {
       cout << cur->data;
       if (cur->next != nullptr){
           cout << ", ";
       }
   }
   cout << "}" << endl;
}

/*
 * This utility function deallocates the memory for all the nodes in a
 * given linked list. It can be used to recycle the memory allocated
 * during a test case and avoid memory leaks.
 */
void deallocateList(ListNode* front) {
    ListNode* cur = front;
    while(cur != nullptr){
        ListNode* temp = cur;
        cur = cur->next;
        delete temp;
    }
}

/*
 * This utility function is given a vector of values and constructs
 * an equivalent linked list containing the same values in the same order.
 * It can be used to construct a linked list to use as an input to
 * a function being tested.
 */
ListNode* createList(Vector<int> values){
    ListNode* front = nullptr;
    int len = values.size();
    for (int i = len; i > 0; i--){
        front = new ListNode(values[i-1], front);
    }
    return front;
}

/*
 * This utility function compares a linked list and a vector for
 * equivalence and returns true if both contain the same values in the
 * same order. It can be used to confirm a linked list's contents match
 * the expected.
 */
bool areEquivalent(ListNode* front, Vector<int> v){
    ListNode* cur = front;
    int i = 0;
    while (cur != nullptr && i != v.size()){
        if (cur->data != v[i]) return false;
        cur = cur->next;
        i++;
    }
    // the number of node in list cur should equal to the size of vector v
    return cur == nullptr && i == v.size();
}

STUDENT_TEST("This is a skeleton to demonstrate an end-to-end student test."){
    /* Initialize vector to sequence of values */
    Vector<int> values = {1, 2, 3, 4};
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);

    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}

PROVIDED_TEST("This tests some of the testing helper functions you are recommended to implement."){
    /* Creates a small test list containing the values 1->2->3. */
    ListNode* testList = nullptr;
    testList = new ListNode(3, testList);
    testList = new ListNode(2, testList);
    testList = new ListNode(1, testList);

    /* Test equality comparison function. */
    EXPECT(areEquivalent(testList, {1, 2, 3}));
    EXPECT(!areEquivalent(testList, {1, 2}));
    EXPECT(!areEquivalent(testList, {1, 2, 3, 4}));
    EXPECT(!areEquivalent(testList, {1, 3, 2}));

    /* Test create list function. */
    ListNode* studentList = createList({1, 2, 3, 4});
    printList(studentList);
    ListNode* cur = studentList;
    for (int i = 1; i <= 4; i++){
        EXPECT(cur != nullptr);
        EXPECT_EQUAL(cur->data, i);
        cur = cur->next;
    }

    /* Test deallocate list functions. There should be no memory leaks from this test. */
    deallocateList(studentList);
    deallocateList(testList);
}

/*
 * The provided test case demonstrates a comparsion between the same
 * algorithm (quicksort) operating on a linked list versus a vector.
 */
PROVIDED_TEST("Time linked list quicksort vs vector quicksort") {
    int startSize = 50000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v(n);
        ListNode* list = nullptr;

        /* Create linked list and vector with the same random sequence. */
        for (int i = n-1; i >= 0; i--) {
            v[i] = randomInteger(-10000, 10000);
            list = new ListNode(v[i], list);
        }

        /* NOTE: This test does not check correctness of the linked list sort
         * function. It only times the two operations to compare relative speed. */
        TIME_OPERATION(n, quickSort(list));
        TIME_OPERATION(n, v.sort());        /* Standard vector sort operation is backed
                                               with quicksort algorithm. */

        deallocateList(list);
    }
}

STUDENT_TEST("test partition: nullptr"){
    ListNode* front = nullptr;
    ListNode *low, *pivot, *high;
    low = pivot = high = nullptr;
    partition(low, pivot, high, front);
    EXPECT(low == nullptr);
    EXPECT(pivot == nullptr);
    EXPECT(high == nullptr);
}

STUDENT_TEST("test partition: 1 element"){
    ListNode* front = new ListNode(1, nullptr);
    ListNode *low, *pivot, *high;
    low = pivot = high = nullptr;
    partition(low, pivot, high, front);
    EXPECT(low == nullptr);
    EXPECT(pivot == front);
    EXPECT(pivot->data == 1);
    EXPECT(pivot->next == nullptr);
    EXPECT(high == nullptr);
    deallocateList(pivot);
}

STUDENT_TEST("test partition: 2 elements"){
    ListNode* front = createList({1, 2});
    ListNode *low, *pivot, *high;
    low = pivot = high = nullptr;
    partition(low, pivot, high, front);
    EXPECT(low == nullptr);
    EXPECT(pivot == front);
    EXPECT(pivot->data == 1);
    EXPECT(pivot->next == nullptr);
    EXPECT(high->data == 2);
    EXPECT(high->next == nullptr);
    deallocateList(pivot);
    deallocateList(high);
}

STUDENT_TEST("test partition: 7 elements"){
    ListNode* front = createList({0, -1, -2, -3, 1, 2, 3});
    ListNode *low, *pivot, *high;
    low = pivot = high = nullptr;
    partition(low, pivot, high, front);
    EXPECT(pivot == front);
    EXPECT(pivot->data == 0);
    EXPECT(pivot->next == nullptr);

    ListNode* tmp = low;
    for (int i = -3; i < 0; i++){
        EXPECT(tmp->data == i);
        tmp = tmp->next;
    }
    EXPECT(tmp == nullptr);

    tmp = high;
    for (int i = 3; i > 0; i--){
        EXPECT(tmp->data == i);
        tmp = tmp->next;
    }
    EXPECT(tmp == nullptr);

    deallocateList(low);
    deallocateList(pivot);
    deallocateList(high);
}

STUDENT_TEST("test partition: repeat elements"){
    ListNode* front = createList({0, 0, 0, -1, -1, -1, 1, 1, 1});
    ListNode *low, *pivot, *high;
    low = pivot = high = nullptr;
    partition(low, pivot, high, front);

    ListNode* tmp = low;
    for (int i = 1; i <= 3; i++){
        EXPECT(tmp->data == -1);
        tmp = tmp->next;
    }
    EXPECT(tmp == nullptr);

    tmp = pivot;
    for (int i = 1; i <= 3; i++){
        EXPECT(tmp->data == 0);
        tmp = tmp->next;
    }
    EXPECT(tmp == nullptr);

    tmp = high;
    for (int i = 1; i <= 3; i++){
        EXPECT(tmp->data == 1);
        tmp = tmp->next;
    }
    EXPECT(tmp == nullptr);

    deallocateList(low);
    deallocateList(pivot);
    deallocateList(high);
}

STUDENT_TEST("test concatenate: nullptr"){
    ListNode* front = nullptr;
    ListNode *low, *pivot, *high;
    low = pivot = high = nullptr;
    partition(low, pivot, high, front);
    concatenate(low, pivot, high, front);
    EXPECT(front == nullptr);
}

STUDENT_TEST("test concatenate: 1 element"){
    ListNode* front = new ListNode(1, nullptr);
    ListNode* temp = front;
    ListNode *low, *pivot, *high;
    low = pivot = high = nullptr;
    partition(low, pivot, high, front);
    concatenate(low, pivot, high, front);
    EXPECT(front == temp);
    EXPECT(areEquivalent(front, {1}));
    deallocateList(front);
}

STUDENT_TEST("test concatenate: 2 elements"){
    ListNode* front = createList({1, 2});
    ListNode *low, *pivot, *high;
    low = pivot = high = nullptr;
    partition(low, pivot, high, front);
    concatenate(low, pivot, high, front);
    EXPECT(areEquivalent(front, {1, 2}));
    deallocateList(front);
}

STUDENT_TEST("test concatenate: 7 elements"){
    ListNode* front = createList({0, -1, -2, -3, 1, 2, 3});
    ListNode *low, *pivot, *high;
    low = pivot = high = nullptr;
    partition(low, pivot, high, front);
    concatenate(low, pivot, high, front);
    EXPECT(areEquivalent(front, {-3, -2, -1, 0, 3, 2, 1}));
    deallocateList(front);
}

STUDENT_TEST("test concatenate: repeat elements"){
    ListNode* front = createList({0, 0, 0, -1, -1, -1, 1, 1, 1});
    ListNode *low, *pivot, *high;
    low = pivot = high = nullptr;
    partition(low, pivot, high, front);
    concatenate(low, pivot, high, front);
    EXPECT(areEquivalent(front, {-1, -1, -1, 0, 0, 0, 1, 1, 1}));
    deallocateList(front);
}

STUDENT_TEST("test quicksort: 4 elements, simple test"){
    Vector<int> values = {2, 3, 1, 4};
    ListNode* list = createList(values);
    quickSort(list);
    values.sort();
    EXPECT(areEquivalent(list, values));
    deallocateList(list);
}

STUDENT_TEST("test quicksort: repeat elements"){
    Vector<int> values = {2, 2, 3, 3, 1, 4};
    ListNode* list = createList(values);
    quickSort(list);
    values.sort();
    EXPECT(areEquivalent(list, values));
    deallocateList(list);
}

PROVIDED_TEST("test quicksort: operation time for worst case") {
    int startSize = 5000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v(n);
        ListNode* list = nullptr;

        /* Create linked list and vector with the same random sequence. */
        for (int i = n-1; i >= 0; i--) {
            v[i] = i;
            list = new ListNode(v[i], list);
        }

        /* NOTE: This test does not check correctness of the linked list sort
         * function. It only times the two operations to compare relative speed. */
        TIME_OPERATION(n, quickSort(list));
        TIME_OPERATION(n, v.sort());        /* Standard vector sort operation is backed
                                               with quicksort algorithm. */

        EXPECT(areEquivalent(list, v));
        deallocateList(list);
    }
}
