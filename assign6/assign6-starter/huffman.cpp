#include "bits.h"
#include "treenode.h"
#include "huffman.h"
#include "map.h"
#include "vector.h"
#include "priorityqueue.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
#include "error.h"
#include "set.h"
using namespace std;

void deallocateTree(EncodingTreeNode* t);

/**
 * Given a Queue<Bit> containing the compressed message bits and the encoding tree
 * used to encode those bits, decode the bits back to the original message text.
 *
 * You can assume that tree is a well-formed non-empty encoding tree and
 * messageBits queue contains a valid sequence of encoded bits.
 *
 * Your implementation may change the messageBits queue however you like. There
 * are no requirements about what it should look like after this function
 * returns. The encoding tree should be unchanged.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
string decodeText(EncodingTreeNode* tree, Queue<Bit>& messageBits) {
    /* TODO: Implement this function. */
    string result = "";
    EncodingTreeNode* cur = tree; // use cur to traverse the tree
    while (!messageBits.isEmpty()){
        // move cur to left
        if (messageBits.peek() == 0){
            cur = cur->zero;
        }
        // move cur to right
        else {
            cur = cur->one;
        }
        // current node is leaf node, append character to string and move cur to the root node
        if (cur->isLeaf()){
            result += cur->getChar();
            cur = tree;
        }
        messageBits.dequeue(); // next bit
    }
    return result;
}

/**
 * Reconstruct encoding tree from flattened form Queue<Bit> and Queue<char>.
 *
 * You can assume that the queues are well-formed and represent
 * a valid encoding tree.
 *
 * Your implementation may change the queue parameters however you like. There
 * are no requirements about what they should look like after this function
 * returns.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
EncodingTreeNode* unflattenTree(Queue<Bit>& treeShape, Queue<char>& treeLeaves) {
    // edge case
    if (treeShape.isEmpty()){
        return nullptr;
    }
    // base case: leaf node, current peek bit of treeShape is 0
    if (treeShape.dequeue() == 0){
        return new EncodingTreeNode(treeLeaves.dequeue());
    }
    // recursive case: interior node
    else {
        return new EncodingTreeNode(unflattenTree(treeShape, treeLeaves),
                                    unflattenTree(treeShape, treeLeaves));
    }
}

/* iteration edtion of unflattenTree:
 * can't use iteration method to write unflattenTree,
 * just can use recursion method to write unflattenTee.
 */
//EncodingTreeNode* unflattenTree(Queue<Bit>& treeShape, Queue<char>& treeLeaves) {
//    /* TODO: Implement this function. */
//    // treeShape is empty
//    if (treeShape.isEmpty()){
//        return nullptr;
//    }
//    // singleton tree: first bit of treeShape is 0, tree just has one node
//    else if (treeShape.dequeue() == 0) {
//        EncodingTreeNode* root = new EncodingTreeNode(treeLeaves.dequeue());
//        return root;
//    }
//    // tree has interior node: first bit of treeShape is 1
//    else {
//        EncodingTreeNode* root = new EncodingTreeNode(nullptr, nullptr);
//        EncodingTreeNode* cur = root; // use cur to build tree
//        while (!treeShape.isEmpty()){
//            // there exits such equation: treeShape.size() = 2 * treeLeaves.size() + 1, so pop two times each iteration,
//            // and treeShape obey pre-order, so root first, left node second, and right node last.
//            Bit left = treeShape.dequeue();
//            Bit right = treeShape.dequeue();
//            // left node is leaf node, right node is interior node
//            if (left == 0 && right == 1){
//                cur->zero = new EncodingTreeNode(treeLeaves.dequeue());
//                cur->one = new EncodingTreeNode(nullptr, nullptr);
//                cur = cur->one;
//            }
//            // left node is interior node, right node is leaf node
//            else if (left == 1 && right == 0){
//                cur->zero = new EncodingTreeNode(nullptr, nullptr);
//                cur->one = new EncodingTreeNode(treeLeaves.dequeue());
//                cur = cur->zero;
//            }
//            // both left node and right node are leaf node
//            else {
//                cur->zero = new EncodingTreeNode(treeLeaves.dequeue());
//                cur->one = new EncodingTreeNode(treeLeaves.dequeue());
//            }
//        }
//        return root;
//    }
//}

/**
 * Decompress the given EncodedData and return the original text.
 *
 * You can assume the input data is well-formed and was created by a correct
 * implementation of compress.
 *
 * Your implementation may change the data parameter however you like. There
 * are no requirements about what it should look like after this function
 * returns.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
string decompress(EncodedData& data) {
    /* TODO: Implement this function. */
    EncodingTreeNode* tree = unflattenTree(data.treeShape, data.treeLeaves);
    string message = decodeText(tree, data.messageBits);
    deallocateTree(tree);
    return message;
}

/**
 * Constructs an optimal Huffman coding tree for the given text, using
 * the algorithm described in lecture.
 *
 * Reports an error if the input text does not contain at least
 * two distinct characters.
 *
 * When assembling larger trees out of smaller ones, make sure to set the first
 * tree dequeued from the queue to be the zero subtree of the new tree and the
 * second tree as the one subtree.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
EncodingTreeNode* buildHuffmanTree(string text) {
    /* TODO: Implement this function. */
    // get frequency of each character in text
    Map<char, int> frequency;
    for (auto ch : text){
        if (frequency.containsKey(ch)){
            frequency[ch]++;
        }
        else {
            frequency[ch] = 1;
        }
    }
    // text does not contain at least two distinct characters
    if (frequency.size() < 2){
        error("text does not contain at least two distinct characters");
    }
    // create singleton tree of each character
    PriorityQueue<EncodingTreeNode*> pq;
    for (auto ch : frequency){
        pq.enqueue(new EncodingTreeNode(ch), frequency[ch]);
    }
    // merge tree
    while (pq.size() > 1){
        double zeroPriority = pq.peekPriority();
        EncodingTreeNode* zero = pq.dequeue();
        double onePriority = pq.peekPriority();
        EncodingTreeNode* one = pq.dequeue();
        pq.enqueue(new EncodingTreeNode(zero, one), zeroPriority + onePriority);
    }
    return pq.dequeue();
}

//get mapping of the tree from character to the encoding string .
void mapping(EncodingTreeNode* tree, Map<char, string>& codeList, string code){
    // edge case
    if (tree == nullptr){
        return;
    }
    // base case: leaf node
    if (tree->isLeaf()){
        // store the encoding string of character into the map
        codeList[tree->getChar()] = code;
    }
    // recursive case: interior node
    else {
        mapping(tree->zero, codeList, code + "0");
        mapping(tree->one, codeList, code + "1");
    }
}

/**
 * Given a string and an encoding tree, encode the text using the tree
 * and return a Queue<Bit> of the encoded bit sequence.
 *
 * You can assume tree is a valid non-empty encoding tree and contains an
 * encoding for every character in the text.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
Queue<Bit> encodeText(EncodingTreeNode* tree, string text) {
    /* TODO: Implement this function. */
    // make up the map from charactor to bits
    Map<char, string> codeList;
    mapping(tree, codeList, "");
    // encode text by mapping each character of text
    string message;
    for (auto ch : text){
        message += codeList[ch];
    }
    // convert string to Queue<Bit>
    Queue<Bit> messageBits;
    for (auto ch : message){
        Bit bit = (ch == '0')? 0: 1;
        messageBits.enqueue(bit);
    }
    return messageBits;
}

/**
 * Flatten the given tree into a Queue<Bit> and Queue<char> in the manner
 * specified in the assignment writeup.
 *
 * You can assume the input queues are empty on entry to this function.
 *
 * You can assume tree is a valid well-formed encoding tree.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
void flattenTree(EncodingTreeNode* tree, Queue<Bit>& treeShape, Queue<char>& treeLeaves) {
    /* TODO: Implement this function. */
    // edge case
    if (tree == nullptr){
        return;
    }
    // base case: leaf node
    if (tree->isLeaf()){
        treeShape.enqueue(0); // push bit 0 into queue
        treeLeaves.enqueue(tree->getChar()); // push char of leaf node into queue
    }
    // recursive case: interior node
    else {
        treeShape.enqueue(1); // push bit 1 into queue, bits in treeShape obey pre-order
        // because interior node doesn't has char, characters in treeLeavres has same order using pre-order/in-order/post-order
        flattenTree(tree->zero, treeShape, treeLeaves);
        flattenTree(tree->one, treeShape, treeLeaves);
    }
}

//void preOrder(EncodingTreeNode* tree, Queue<Bit>& treeShape){
//    // edge case
//    if (tree == nullptr){
//        return;
//    }
//    // base case: leaf node, push bit 0 into the queue
//    if (tree->isLeaf()){
//        treeShape.enqueue(0);
//    }
//    // recursive case: interior node, push bit 1 into the queue
//    else {
//        // use pre-order to traverse the tree
//        treeShape.enqueue(1);
//        preOrder(tree->zero, treeShape);
//        preOrder(tree->one, treeShape);
//    }
//}

//void inOrder(EncodingTreeNode* tree, Queue<char>& treeLeaves){
//    // edge case
//    if (tree == nullptr){
//        return;
//    }
//    // base case: leaf node, push char of leaf node into the queue
//    if (tree->isLeaf()){
//        treeLeaves.enqueue(tree->getChar());
//    }
//    // recursive case: interior node
//    else {
//        // use in-order to traverse the tree, interior node doesn't has char
//        inOrder(tree->zero, treeLeaves);
//        inOrder(tree->one, treeLeaves);
//    }
//}

/* in this problem pre-order and in-order traverse can take the same time to save time
 */
//void flattenTree(EncodingTreeNode* tree, Queue<Bit>& treeShape, Queue<char>& treeLeaves) {
//    /* TODO: Implement this function. */
//    preOrder(tree, treeShape);
//    inOrder(tree, treeLeaves);
//}

/**
 * Compress the input text using Huffman coding, producing as output
 * an EncodedData containing the encoded message and flattened
 * encoding tree used.
 *
 * Reports an error if the message text does not contain at least
 * two distinct characters.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
EncodedData compress(string messageText) {
    /* TODO: Implement this function. */
    // report error message
    Set<char> distinctChar;
    for (char ch : messageText){
        distinctChar.add(ch);
    }
    if (distinctChar.size() < 2){
        error("text does not contain at least two distinct characters");
    }
    // make up EncodeData
    EncodingTreeNode* tree = buildHuffmanTree(messageText);
    Queue<Bit>  treeShape;
    Queue<char> treeLeaves;
    flattenTree(tree, treeShape, treeLeaves);
    Queue<Bit>  messageBits = encodeText(tree, messageText);

    deallocateTree(tree);
    return {treeShape, treeLeaves, messageBits};
}

/* * * * * * Testing Helper Functions Below This Point * * * * * */

EncodingTreeNode* createExampleTree() {
    /* Example encoding tree used in multiple test cases:
     *                *
     *              /   \
     *             T     *
     *                  / \
     *                 *   E
     *                / \
     *               R   S
     */
    EncodingTreeNode* R = new EncodingTreeNode('R');
    EncodingTreeNode* S = new EncodingTreeNode('S');
    EncodingTreeNode* E = new EncodingTreeNode('E');
    EncodingTreeNode* T = new EncodingTreeNode('T');
    EncodingTreeNode* root = new EncodingTreeNode(R, S);
    root = new EncodingTreeNode(root, E);
    root = new EncodingTreeNode(T, root);
    return root;
}

void deallocateTree(EncodingTreeNode* t) {
    // edge case
    if (t == nullptr){
        return;
    }
    // base case: leaf node
    if (t->isLeaf()){
        delete t;
    }
    // recursive case: interior node
    else {
        // use post-order to deallocte the tree
        deallocateTree(t->zero);
        deallocateTree(t->one);
        delete t;
    }
}

bool areEqual(EncodingTreeNode* a, EncodingTreeNode* b) {
    Queue<Bit> treeShapeA, treeShapeB;
    Queue<char> treeLeavesA, treeLeavesB;
    flattenTree(a, treeShapeA, treeLeavesA);
    flattenTree(b, treeShapeB, treeLeavesB);
    // two trees are same if shape and leaves are same
    return treeShapeA == treeShapeB && treeLeavesA == treeLeavesB;
}

//void traverse(EncodingTreeNode* tree, Vector<char>& leaf){
//    // edge case
//    if (tree == nullptr){
//        return;
//    }
//    // base case: leaf node
//    if (tree->isLeaf()){
//        leaf.add(tree->getChar());
//    }
//    // recursive case: interior node
//    else {
//        traverse(tree->zero, leaf);
//        traverse(tree->one, leaf);
//    }
//}

/* wrong: only compare the characters of two trees, it's not enough, should also compare
 * the shape of two trees.
 */
//bool areEqual(EncodingTreeNode* a, EncodingTreeNode* b) {
//    Vector<char> leafA, leafB;
//    traverse(a, leafA);
//    traverse(b, leafB);
//    return leafA == leafB;
//}

/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Write your own student tests. */
STUDENT_TEST("test areEqual: compare singleton tree with empty tree"){
    EncodingTreeNode* one = new EncodingTreeNode('A');
    EXPECT(!areEqual(one, nullptr));
    deallocateTree(one);
}

STUDENT_TEST("test areEqual: compare one singleton tree with another singleton tree"){
    EncodingTreeNode* one = new EncodingTreeNode('A');
    EncodingTreeNode* two = new EncodingTreeNode('A');
    EXPECT(areEqual(one, two));

    EncodingTreeNode* three = new EncodingTreeNode('a');
    EXPECT(!areEqual(one, three));
    deallocateTree(one);
    deallocateTree(two);
    deallocateTree(three);
}

STUDENT_TEST("test areEqual: compare one singleton tree with createExampleTree"){
    EncodingTreeNode* one = new EncodingTreeNode('A');
    EncodingTreeNode* two = createExampleTree();
    EXPECT(!areEqual(one, two));
    deallocateTree(one);
    deallocateTree(two);
}

STUDENT_TEST("test areEqual: compare createExampleTree with createExampleTree"){
    EncodingTreeNode* one = createExampleTree();
    EncodingTreeNode* two = createExampleTree();
    EXPECT(areEqual(one, two));
    deallocateTree(one);
    deallocateTree(two);
}

STUDENT_TEST("test areEqual: compare createExampleTree with it's subtree"){
    EncodingTreeNode* one = createExampleTree();
    EXPECT(!areEqual(one, one->zero));
    EXPECT(!areEqual(one, one->one));
    deallocateTree(one);
}

STUDENT_TEST("decodeText, empty messageBits") {
    EncodingTreeNode* tree = createExampleTree(); // see diagram above
    EXPECT(tree != nullptr);

    Queue<Bit> messageBits = {}; // empty
    EXPECT_EQUAL(decodeText(tree, messageBits), "");
    deallocateTree(tree);
}

STUDENT_TEST("test mapping: create codeList for createExampleTree"){
    EncodingTreeNode* one = createExampleTree();
    Map<char, string> codeList;
    mapping(one, codeList, "");
    EXPECT(codeList['T'] == "0");
    EXPECT(codeList['R'] == "100");
    EXPECT(codeList['S'] == "101");
    EXPECT(codeList['E'] == "11");
    deallocateTree(one);
}

STUDENT_TEST("buildHuffmanTree: text doesn't has least two distinct characters") {
    EXPECT_ERROR(buildHuffmanTree(""));
    EXPECT_ERROR(buildHuffmanTree("ss"));
    EXPECT_ERROR(buildHuffmanTree("sss"));
}

STUDENT_TEST("compress, text doesn't has least two distinct characters") {
    EXPECT_ERROR(buildHuffmanTree(""));
    EXPECT_ERROR(buildHuffmanTree("ss"));
    EXPECT_ERROR(buildHuffmanTree("sss"));
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("decodeText, small example encoding tree") {
    EncodingTreeNode* tree = createExampleTree(); // see diagram above
    EXPECT(tree != nullptr);

    Queue<Bit> messageBits = { 1, 1 }; // E
    EXPECT_EQUAL(decodeText(tree, messageBits), "E");

    messageBits = { 1, 0, 1, 1, 1, 0 }; // SET
    EXPECT_EQUAL(decodeText(tree, messageBits), "SET");

    messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1}; // STREETS
    EXPECT_EQUAL(decodeText(tree, messageBits), "STREETS");

    deallocateTree(tree);
}

PROVIDED_TEST("unflattenTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    Queue<Bit>  treeShape  = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> treeLeaves = { 'T', 'R', 'S', 'E' };
    EncodingTreeNode* tree = unflattenTree(treeShape, treeLeaves);

    EXPECT(areEqual(tree, reference));

    deallocateTree(tree);
    deallocateTree(reference);
}

PROVIDED_TEST("decompress, small example input") {
    EncodedData data = {
        { 1, 0, 1, 1, 0, 0, 0 }, // treeShape
        { 'T', 'R', 'S', 'E' },  // treeLeaves
        { 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1 } // messageBits
    };

    EXPECT_EQUAL(decompress(data), "TRESS");
}

PROVIDED_TEST("buildHuffmanTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    EncodingTreeNode* tree = buildHuffmanTree("STREETTEST");
    EXPECT(areEqual(tree, reference));

    deallocateTree(reference);
    deallocateTree(tree);
}

PROVIDED_TEST("encodeText, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above

    Queue<Bit> messageBits = { 1, 1 }; // E
    EXPECT_EQUAL(encodeText(reference, "E"), messageBits);

    messageBits = { 1, 0, 1, 1, 1, 0 }; // SET
    EXPECT_EQUAL(encodeText(reference, "SET"), messageBits);

    messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1 }; // STREETS
    EXPECT_EQUAL(encodeText(reference, "STREETS"), messageBits);

    deallocateTree(reference);
}

PROVIDED_TEST("flattenTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    Queue<Bit>  expectedShape  = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> expectedLeaves = { 'T', 'R', 'S', 'E' };

    Queue<Bit>  treeShape;
    Queue<char> treeLeaves;
    flattenTree(reference, treeShape, treeLeaves);

    EXPECT_EQUAL(treeShape,  expectedShape);
    EXPECT_EQUAL(treeLeaves, expectedLeaves);

    deallocateTree(reference);
}

PROVIDED_TEST("compress, small example input") {
    EncodedData data = compress("STREETTEST");
    Queue<Bit>  treeShape   = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> treeChars   = { 'T', 'R', 'S', 'E' };
    Queue<Bit>  messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0 };

    EXPECT_EQUAL(data.treeShape, treeShape);
    EXPECT_EQUAL(data.treeLeaves, treeChars);
    EXPECT_EQUAL(data.messageBits, messageBits);
}

PROVIDED_TEST("Test end-to-end compress -> decompress") {
    Vector<string> inputs = {
        "HAPPY HIP HOP",
        "Nana Nana Nana Nana Nana Nana Nana Nana Batman"
        "Research is formalized curiosity. It is poking and prying with a purpose. – Zora Neale Hurston",
    };

    for (string input: inputs) {
        EncodedData data = compress(input);
        string output = decompress(data);

        EXPECT_EQUAL(input, output);
    }
}
