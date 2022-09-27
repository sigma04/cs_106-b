/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 *
 * WARNING: The provided code is buggy!
 *
 * Use unit tests to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string removeNonLetters(string s) {
    string result = charToString(s[0]);
    if (!isalpha(s[0]))
    {
        result.pop_back();
    }
    for (int i = 1; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

// Calculate the code of second name.
string code(string s)
{
    string result = "";
    string codeTable[] = {"AEIOUHWY", "BFPV","CGJKQSXZ", "DT", "L", "MN", "R"};
    for (int i = 0; i < s.length(); i++)
    {
        // change current character to upper case to compare with each string in codeTable
        auto ch = toupper(s[i]);
        for (int j = 0; j < 7; j++)
        {
            if (codeTable[j].find(ch) != string::npos)
            {
                result += to_string(j);
                break;
            }
        }
    }

    return result;
}

// Merge adjacent repeating numbers.
string mergeRepeatNum(string s)
{
    string result = "";
    if (s.length() > 0)
    {
        result += s[0];
        for (int i =1; i < s.length(); i++)
        {
            if (result.back() != s[i])
            {
                result += s[i];
            }
        }
    }
    return result;
}

// Replace the first letter of code with character initial.
string replaceInitial(string s, char initial)
{
    string result = "";
    result += initial;
    for (int i = 1; i < s.length(); i++)
    {
        result += s[i];
    }
    return result;
}

// Delete the zeros in the string
string deleteZero(string s)
{
    string result = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != '0')
        {
            result += s[i];
        }
    }
    return result;
}

// Formating the string to confirm the result has only 4 characters.
string formation(string s)
{
    string result = "0000";
    for (int i = 0; i < s.length(); i++)
    {
        result[i] = s[i];
    }
    return result;
}
/* TODO: Replace this comment with a descriptive function
 * Calculate the soundex code for the string s.
 */
string soundex(string s) {
    /* TODO: Fill in this function. */
    string result = "";
    result = removeNonLetters(s);
    result = code(result);
    result = mergeRepeatNum(result);
    result = replaceInitial(result, toupper(s[0]));
    result = deleteZero(result);
    result = formation(result);
    return result;
}

/* TODO: Replace this comment with a descriptive function
 * Find all names which has same soundex code with input form the database.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames

    /* TODO: Fill in the remainder of this function. */
    string input = "";
    string soundexOfInput = "";
    string soundexOfDatabase = "";
    Vector<string> result;
    while(true)
    {
        // clear the vector calculated last time
        result.clear();

        // get input from the command line
        input = getLine("Enter a surname (RETURN to quit): ");

        // return if no input get
        if (input.length() <= 0)
        {
            cout << "All done!";
            return;
        }

        // calculate soundex code for the input
        soundexOfInput = soundex(input);
        cout << "Soundex code is " << soundexOfInput << endl;

        // search names that has same soundex code with input from database
        for (unsigned i = 0; i < databaseNames.size(); i++)
        {
            soundexOfDatabase = soundex(databaseNames[i]);
            if (soundexOfDatabase == soundexOfInput)
            {
                result.add(databaseNames[i]);
            }
        }
        result.sort();
        cout << "Matches from database: " << result << '\n' << endl;
    }
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here


STUDENT_TEST("Test to show the bug of removeNonLetters")
{
    string s = "6Curie";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Curie");
}

STUDENT_TEST("Test to confirm the function of code ")
{
    string s = "Curie";
    string result = code(s);
    EXPECT_EQUAL(result, "20600");

    s = "O'Conner";
    result = code(s);
    EXPECT_EQUAL(result, "0205506");
}

STUDENT_TEST("Test to confirm the mergeRepeatNum works right")
{
    string s = "20600";
    string result = mergeRepeatNum(s);
    EXPECT_EQUAL(result, "2060");

    s = "0205506";
    result = mergeRepeatNum(s);
    EXPECT_EQUAL(result, "020506");
}

STUDENT_TEST("Test to confirm the replaceInitial works right")
{
    string s = "2060";
    string result = replaceInitial(s, 'C');
    EXPECT_EQUAL(result, "C060");

    s = "020506";
    result = replaceInitial(s, 'O');
    EXPECT_EQUAL(result, "O20506");
}

STUDENT_TEST("Test to confirm the deletZero works right")
{
    string s = "C060";
    string result = deleteZero(s);
    EXPECT_EQUAL(result, "C6");

    s = "O20506";
    result = deleteZero(s);
    EXPECT_EQUAL(result, "O256");
}

STUDENT_TEST("Test to confirm the formation works right")
{
    string s = "C6";
    string result = formation(s);
    EXPECT_EQUAL(result, "C600");

    s = "O256";
    result = formation(s);
    EXPECT_EQUAL(result, "O256");
}

STUDENT_TEST("Test to confirm the soundex works right")
{
    string s = "Curie";
    string result = soundex(s);
    EXPECT_EQUAL(result, "C600");

    s = "O'Conner";
    result = soundex(s);
    EXPECT_EQUAL(result, "O256");
}
