#include "dictionary.h"
#include "wordCounter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    //file location should be adjusted according to your computer
    string filename = "C:\\Users\\DELL\\Desktop\\Project_3\\text.txt";

    // Test wordCounter function an dthe graph function... ex.
    Dictionary<string, int> test1 = wordCounter(filename);
    cout << "Test 1 - Word Counter:" << endl;
    test1.graph();
    cout << endl;
 
    // Test insertNode function
    Dictionary<int, string> test2;
    cout << "Test 2 - Insert Node:" << endl;
    test2.insertNode(10, "Info 10");
    test2.insertNode(20, "Info 20");
    test2.insertNode(5, "Info 5");
    test2.insertNode(15, "Info 15");
    test2.insertNode(25, "Info 25");
    test2.insertNode(17, "Info 17");
    test2.print();
    cout << endl;

    // Test graph function
    cout << "Test 4 - Graph (Empty Dictionary):" << endl;
    test2.graph();
    cout << endl;

    // Test removeLast function
    cout << "Test 3 - Remove Last:" << endl;
    test2.removeLast();
    test2.print();
    cout << endl;

    cout << "Test 4 - Graph (Empty Dictionary):" << endl;
    test2.graph();
    cout << endl;

    // Test insertAmount function
    cout << "Test 5 - Insert Amount:" << endl;
    cout << "Number of inserted nodes: " << test2.insertAmount() << endl;
    cout << endl;

    return 0;
}
