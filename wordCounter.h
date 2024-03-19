#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>


// Function to read a file and count the occurrences of words
Dictionary<string, int> wordCounter(const string& filename) {
    Dictionary<string, int> dict;

    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Failed to open input file." << endl;
        return dict;
    }

    string word;
    long long wordCount = 0;

    // Read words from file and count occurrences
    while (inputFile >> word) {
        dict.insertNode(word, dict.insertAmount());
        wordCount++;
    }

    cout << "Total words: " << wordCount << endl;

    inputFile.close();

    return dict;
}