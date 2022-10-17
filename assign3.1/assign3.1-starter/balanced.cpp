/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "testing/SimpleTest.h"

using namespace std;

/* Return only operators in the string.
 */
string operatorsFrom(string str) {
    // base case
    if (str.empty()){
        return "";
    }
    else {
        // first char is operator character
        switch (str[0]) {
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
            return str[0] + operatorsFrom(str.substr(1));
            break;
        // first char is not operatr character
        default:
            return operatorsFrom(str.substr(1));
        }
    }
}

/*
 * Return if the oprators in string are macthed.
 */
bool operatorsAreMatched(string ops) {
//    cout << "ops: " << ops << endl;
    if (ops.empty()){   // base case for true
        return true;
    }
    else if (stringContains(ops, "()")){   // contains ()
        return operatorsAreMatched(stringReplace(ops,"()", ""));
    }
    else if (stringContains(ops, "[]")){    // contains []
        return operatorsAreMatched(stringReplace(ops,"[]", ""));
    }
    else if (stringContains(ops, "{}")){    // contains {}
        return operatorsAreMatched(stringReplace(ops,"{}", ""));
    }
    else {
        return false;  // not in the cases before
    }
}

/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}

STUDENT_TEST("operatorsFrom on several examples"){
    EXPECT_EQUAL(operatorsFrom("int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }"), "(){([])(())}");
    EXPECT_EQUAL(operatorsFrom("( ( [ a ] )"), "(([])");
    EXPECT_EQUAL(operatorsFrom("3 ) ("), ")(");
    EXPECT_EQUAL(operatorsFrom("{ ( x } y )"), "{(})");
}

STUDENT_TEST("operatorAreMatched on several examples"){
    EXPECT(operatorsAreMatched(""));
    EXPECT(operatorsAreMatched("([{}])"));
    EXPECT(!operatorsAreMatched("}{"));
}
