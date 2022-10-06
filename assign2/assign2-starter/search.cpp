// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "search.h"
#include "set.h"
#include "strlib.h"
#include "vector.h"
#include "testing/SimpleTest.h"
#include "simpio.h"
using namespace std;


// Delete the punctuation at the begin and end of the token.
// If toke has no alphabetaic character, return null.
string cleanToken(string s)
{
    // delete punctuation at beginning
    while(ispunct(s[0])) {
        s.erase(0, 1);
    }
    // delete punctuation at end
    while( ispunct(s.back()) ) {
        s.pop_back();
    }

    // Word should contains at least one alphabetic character
    // and convert to lower case.
    bool isAlpha = false;
    for (int i = 0; i < s.length(); i++){
        if (isalpha(s[i])) {
            isAlpha = true;
            s[i] = tolower(s[i]);
        }
    }
    if (!isAlpha) {
        // If s does not cotains alphabetic character, return null.
        return "";
    }

    return s;
}

// Split the text to get a set of tokens.
Set<string> gatherTokens(string text)
{
    Set<string> tokens;
    Vector<string> splitTokens = stringSplit(text, " ");
    string word = "";
    for (string tok : splitTokens) {
        word = cleanToken(tok);
        // word is not null.
        if (word.length() > 0) {
            tokens.add(word);
        }
    }

    return tokens;
}

// Build the link between token and website using dbfile.
int buildIndex(string dbfile, Map<string, Set<string>>& index)
{
    ifstream in;
    if (!openFile(in, dbfile))
        error("Cannot open file named " + dbfile);
    Vector<string> lines;
    readEntireFile(in, lines); // read all datas from the dbfile

    string url;
    string tokens;
    Set<string> tokensSet; // convert tokens to set
    int webNum = 0; // counts of processed webs
    for (int i = 0; i < lines.size(); i+=2) {
        webNum++;
        url = lines[i];
        tokens = lines[i+1];
        tokensSet = gatherTokens(tokens);
        for (string tok : tokensSet) {
            index[tok].add(url); // add url to that token
        }
    }

    return webNum;
}

// Find matched website for query using index.
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query)
{
    Set<string> result;
    Vector<string> tokens = stringSplit(query, " ");
    string tokenCleaned;
    Set<string> urls;
    char conj;
    for (string tok : tokens) {
        conj = tok[0]; // conjunction between two tokens
        tokenCleaned = cleanToken(tok);
        urls = index[tokenCleaned];

        if ( isalpha(conj) ) {  // conjunction between two tokens is space, meanning OR
            result.unionWith(urls);
        }
        else if (conj == '+') { // conjunction between two tokens is '+', meanning AND
            result.intersect(urls);
        }
        else if (conj == '-') { // conjunction between two tokens is '-', meanning Minus
            result.difference(urls);
        }
    }

    return result;
}

// Read token from cmdline and return matched website.
void searchEngine(string dbfile)
{
    Map<string, Set<string>> index;
    cout << "Stand by while building index..." << endl;
    int pages = buildIndex(dbfile, index);
    cout << "Indexed " << pages << " pages containing " << index.size() << " unique terms" << endl << endl;

    string query;
    Set<string> result;
    while(true) {
        query = getLine("Enter query sentence (RETURN/ENTER to quit): ");
        if (query.length() == 0) {
            break;
        }

        result = findQueryMatches(index, query);
        cout << "Found " << result.size() << " matching pages" << endl;
        cout << result << endl << endl;
    }
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("cleanToken on strings with no punctuation at beginning or end") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
    EXPECT_EQUAL(cleanToken("CS*106B"), "cs*106b");
}

PROVIDED_TEST("cleanToken on strings with some punctuation at beginning and end") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
}

PROVIDED_TEST("cleanToken on non-word strings (no letters)"){
    EXPECT_EQUAL(cleanToken("106"), "");
    EXPECT_EQUAL(cleanToken("~!106!!!"), "");
}

PROVIDED_TEST("gatherTokens from simple string") {
    Set<string> expected = {"go", "gophers"};
    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
}

PROVIDED_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = {"i", "love", "cs*106b"};
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}

PROVIDED_TEST("gatherTokens from seuss, 5 unique words, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 5);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
    Map<string, Set<string>> index;
    int nPages = buildIndex("res/tiny.txt", index);
//    cout << endl << "index :" << index << endl;
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 11);
    EXPECT(index.containsKey("fish"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


// TODO: add your test cases here

STUDENT_TEST("cleanToken on several cases") {
    EXPECT_EQUAL(cleanToken("section"), "section");
    EXPECT_EQUAL(cleanToken("section!"), "section");
    EXPECT_EQUAL(cleanToken("<<section>>"), "section");
    EXPECT_EQUAL(cleanToken("section's"), "section's");
    EXPECT_EQUAL(cleanToken("section-10"), "section-10");
    EXPECT_EQUAL(cleanToken(""), "");
}
