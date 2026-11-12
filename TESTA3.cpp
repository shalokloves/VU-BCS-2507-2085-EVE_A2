#include <iostream>
#include "DynamicArray.h"
#include "SortSearch.h"
using namespace std;

void check(string name, bool pass) {
    cout << (pass ? "[PASS] " : "[FAIL] ") << name << endl;
}

int main() {
    // T1 - Empty array
    DynamicArray<StudentResult> e;
    check("T1 Empty size==0", e.size() == 0);
    check("T1 Empty binary search == -1", binarySearchByRegNo(e, "VU001") == -1);

    // T2 - 1 record
    DynamicArray<StudentResult> one;
    one.push_back({1, "A", "B", "VU001", 80, "A"});
    insertionSort(one, byResultDesc);
    check("T2 One record sort ok", one.size() == 1 && one.at(0).result == 80);
    check("T2 One record search found", binarySearchByRegNo(one, "VU001") == 0);

    // T3 - Duplicate key - stability test for Insertion Sort
    DynamicArray<StudentResult> dup;
    dup.push_back({1, "First", "A", "VU001", 75, "B"});
    dup.push_back({2, "Second", "B", "VU002", 75, "B"});
    dup.push_back({3, "Third", "C", "VU003", 90, "A"});
    insertionSort(dup, byResultDesc);
    // Insertion is STABLE: First (75) must stay before Second (75)
    check("T3 Duplicate 75 - Insertion STABLE", dup.at(1).firstName == "First" && dup.at(2).firstName == "Second");
    cout << "  Order after sort: " << dup.at(0).firstName << ", " << dup.at(1).firstName << ", " << dup.at(2).firstName << endl;

    // T4 - Remove First / Remove Last
    DynamicArray<StudentResult> r;
    r.push_back({1, "A", "A", "VU001", 10, "C"});
    r.push_back({2, "B", "B", "VU002", 20, "C"});
    r.push_back({3, "C", "C", "VU003", 30, "C"});
    r.removeFirst();
    check("T4 RemoveFirst", r.size() == 2 && r.at(0).regNo == "VU002");
    r.removeLast();
    check("T4 RemoveLast", r.size() == 1 && r.at(0).regNo == "VU002");

    // T5 - Already sorted + Reversed
    DynamicArray<StudentResult> sorted;
    sorted.push_back({1, "A", "A", "VU001", 90, "A"});
    sorted.push_back({2, "B", "B", "VU002", 80, "A"});
    insertionSort(sorted, byResultDesc);
    check("T5 Already sorted stays sorted", sorted.at(0).result == 90);

    DynamicArray<StudentResult> rev;
    rev.push_back({1, "A", "A", "VU001", 10, "C"});
    rev.push_back({2, "B", "B", "VU002", 20, "C"});
    rev.push_back({3, "C", "C", "VU003", 30, "C"});
    quickSort(rev, byResultDesc);
    check("T5 Reversed -> Quicksort sorts", rev.at(0).result == 30 && rev.at(2).result == 10);

    // T6 - Search absent
    quickSort(rev, byRegNoAsc);
    check("T6 Search absent == -1", binarySearchByRegNo(rev, "VU999") == -1);

    cout << "\nA3 DONE - All boundary tests run" << endl;
    return 0;
}