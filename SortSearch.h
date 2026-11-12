#pragma once
#include "DynamicArray.h"
#include <cstdlib>
#include <ctime>

inline bool byResultDesc(const StudentResult& a, const StudentResult& b) {
    return a.result > b.result;
}
inline bool byRegNoAsc(const StudentResult& a, const StudentResult& b) {
    return a.regNo < b.regNo;
}

template <typename T, typename Compare>
void insertionSort(DynamicArray<T> &arr, Compare comp) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        T key = arr.at(i);
        int j = i - 1;
        while (j >= 0 && comp(key, arr.at(j))) {
            arr.at(j + 1) = arr.at(j);
            j--;
        }
        arr.at(j + 1) = key;
    }
}

template <typename T, typename Compare>
int partition(DynamicArray<T> &arr, int low, int high, Compare comp) {
    int pivotIndex = low + rand() % (high - low + 1);
    T pivot = arr.at(pivotIndex);
    T temp = arr.at(pivotIndex);
    arr.at(pivotIndex) = arr.at(high);
    arr.at(high) = temp;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (comp(arr.at(j), pivot)) {
            i++;
            T t = arr.at(i); arr.at(i) = arr.at(j); arr.at(j) = t;
        }
    }
    T t = arr.at(i + 1); arr.at(i + 1) = arr.at(high); arr.at(high) = t;
    return i + 1;
}

template <typename T, typename Compare>
void quickSortHelper(DynamicArray<T> &arr, int low, int high, Compare comp) {
    if (low < high) {
        int pi = partition(arr, low, high, comp);
        quickSortHelper(arr, low, pi - 1, comp);
        quickSortHelper(arr, pi + 1, high, comp);
    }
}

template <typename T, typename Compare>
void quickSort(DynamicArray<T> &arr, Compare comp) {
    srand((unsigned)time(0));
    if (arr.size() > 1)
        quickSortHelper(arr, 0, arr.size() - 1, comp);
}

int binarySearchByRegNo(DynamicArray<StudentResult> &arr, std::string target) {
    int low = 0;
    int high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr.at(mid).regNo == target) return mid;
        else if (arr.at(mid).regNo < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}