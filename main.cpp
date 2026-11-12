#include <iostream>
#include "DynamicArray.h"
#include "SortSearch.h"
using namespace std;

int main() {
    DynamicArray<StudentResult> arr;
    arr.loadFromFile("results.txt");
    cout << "--- Loaded ---" << endl;
    arr.display();

    insertionSort(arr, byResultDesc);
    cout << "\n--- Insertion Sort by Result (High to Low) ---" << endl;
    arr.display();

    quickSort(arr, byRegNoAsc);
    cout << "\n--- Quicksort (Random Pivot) by RegNo ---" << endl;
    arr.display();

    string searchReg;
    cout << "\nEnter RegNo to search: ";
    cin >> searchReg;
    int index = binarySearchByRegNo(arr, searchReg);
    if (index != -1) cout << "FOUND: " << arr.at(index) << endl;
    else cout << "NOT FOUND" << endl;

    cout << "Search for 999 returned: " << binarySearchByRegNo(arr, "999") << " (should be -1)" << endl;
    return 0;
}