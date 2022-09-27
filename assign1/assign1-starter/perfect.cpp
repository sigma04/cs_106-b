/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include "testing/SimpleTest.h"
#include <cmath>
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * This function uses smarter algrithom to calculate sum of all divisors of n.
 * Rather than trying each divisor of n from 1 to n-1 , it stops when divisor
 * is larger than sqrt(n) to save time.
 */
long smarterSum(long n) {
    /* TODO: Fill in this function. */
    long total = 0;
    // divisor ranges from 1 to sqrt(n)
    for (long divisor = 1; n > 0 && divisor < long(sqrt(n)) + 1; divisor++)
    {
        // Ture divisor is small than n itself.
        if (n % divisor == 0 && divisor < n)
        {
            total += divisor;
            // If divisor is larger than 1 , so the quotient n/divisor is
            // another true divisor of n.
            if (divisor > 1 && (divisor * divisor != n))
            {
                total += n / divisor;
            }
        }
    }
    return total;
}

/* TODO: Replace this comment with a descriptive function
 * Use the smaterSum() to test if n is perfect number.
 */
bool isPerfectSmarter(long n) {
    /* TODO: Fill in this function. */
    return (n != 0) && (n == smarterSum(n));
}

/* TODO: Replace this comment with a descriptive function
 * Find out all perfect numbers which is smaller than sotp.
 */
void findPerfectsSmarter(long stop) {
     /* TODO: Fill in this function. */
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * Use the mehtod of Euclid the find the Nth perfect number.
 */
long findNthPerfectEuclid(long n) {
    /* TODO: Fill in this function. */
    int k = 1;
    // Counter of perfect number finded, when countofPerfect equals n, return the result.
    int countOfPerfect = 0;
    // m is the current mason number 2^k - 1.
    long m = 0;
    while(true)
    {
       m = pow(2, k) - 1;
       // use smarterSum to find out if m is prime number.
       if (m > 1 && smarterSum(m) <= 1)
       {
          // new perfect number finded
          countOfPerfect++;
          // if it is the nth perfect number, return.
          if (countOfPerfect == n)
          {
              return pow(2, k-1) * m;
          }
          k++;
       }
       else
       {
           k++;
       }
    }
}

/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

//PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
//    TIME_OPERATION(10000, findPerfects(10000));
//    TIME_OPERATION(20000, findPerfects(20000));
//    TIME_OPERATION(40000, findPerfects(40000));
//    TIME_OPERATION(50000, findPerfects(50000));
//    TIME_OPERATION(60000, findPerfects(60000));
//    TIME_OPERATION(80000, findPerfects(80000));
//    TIME_OPERATION(110000, findPerfects(110000));
//}

// TODO: add your student test cases here
STUDENT_TEST("Comfirm non-zero negative number is not perfect")
{
    EXPECT(!isPerfect(-1));
    EXPECT(!isPerfect(-10000));
}

STUDENT_TEST("Confirm smarterSum of the input")
{
    EXPECT_EQUAL(smarterSum(1), 0);
    EXPECT_EQUAL(smarterSum(6), 6);
    EXPECT_EQUAL(smarterSum(12), 16);
    EXPECT_EQUAL(smarterSum(25), 6);
}

//STUDENT_TEST("Time trials of findPerfects on doubling input sizes") {
//    TIME_OPERATION(375000, findPerfectsSmarter(375000));
//    TIME_OPERATION(750000, findPerfectsSmarter(750000));
//    TIME_OPERATION(1500000, findPerfectsSmarter(1500000));
//    TIME_OPERATION(3000000, findPerfectsSmarter(3000000));
//}


STUDENT_TEST("Comfirm findNthPerfectEuclid works right ") {
    EXPECT_EQUAL(findNthPerfectEuclid(1), 6);
    EXPECT_EQUAL(findNthPerfectEuclid(2), 28);
    EXPECT_EQUAL(findNthPerfectEuclid(3), 496);
    EXPECT_EQUAL(findNthPerfectEuclid(4), 8128);
    EXPECT_EQUAL(findNthPerfectEuclid(5), 33550336);
//    EXPECT(isPerfectSmarter(findNthPerfectEuclid(5)));
}
