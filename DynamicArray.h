// VU-BCS-2507-2085-EVE - Scenario 6: Student Results Register
// BCS 2204 - A1: Dynamic Array
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

struct StudentResult {
    int id = 0;
    std::string firstName;
    std::string lastName;
    std::string regNo;
    int result = 0;
    std::string grade;
};

// Lets any StudentResult be printed with cout (keeps display() generic)
inline std::ostream& operator<<(std::ostream& os, const StudentResult& s) {
    return os << s.id << " " << s.firstName << " " << s.lastName << " "
              << s.regNo << " " << s.result << " " << s.grade;
}

template <typename T>
class DynamicArray {
private:
    T* data;
    int sz;
    int cap;

    // Doubles the capacity: new array, copy, free old, switch pointer
    void grow() {
        int newCap = cap * 2;
        T* nd = new T[newCap];
        for (int i = 0; i < sz; i++) nd[i] = data[i];
        delete[] data;
        data = nd;
        cap = newCap;
        std::cout << "Resized: new capacity = " << cap << "\n";
    }

public:
    DynamicArray() : data(new T[2]), sz(0), cap(2) {}
    ~DynamicArray() { delete[] data; }

    // Deep copy constructor
    DynamicArray(const DynamicArray& o) : data(new T[o.cap]), sz(o.sz), cap(o.cap) {
        for (int i = 0; i < sz; i++) data[i] = o.data[i];
    }

    // Deep copy assignment (allocate first, then free the old array)
    DynamicArray& operator=(const DynamicArray& o) {
        if (this == &o) return *this;
        T* nd = new T[o.cap];
        for (int i = 0; i < o.sz; i++) nd[i] = o.data[i];
        delete[] data;
        data = nd;
        sz = o.sz;
        cap = o.cap;
        return *this;
    }

    int size() const { return sz; }
    int capacity() const { return cap; }
    bool isEmpty() const { return sz == 0; }
    void clear() { sz = 0; }

    void push_back(const T& v) {
        if (sz == cap) grow();
        data[sz++] = v;
    }

    // Bounds-checked access
    T& at(int i) {
        if (i < 0 || i >= sz) throw std::out_of_range("Index out of range");
        return data[i];
    }
    const T& at(int i) const {
        if (i < 0 || i >= sz) throw std::out_of_range("Index out of range");
        return data[i];
    }

    // Insert at idx and shift the rest right (idx == sz means append)
    bool insertAt(int idx, const T& v) {
        if (idx < 0 || idx > sz) {
            std::cout << "insertAt: invalid index " << idx << "\n";
            return false;
        }
        if (sz == cap) grow();
        for (int i = sz; i > idx; i--) data[i] = data[i - 1];
        data[idx] = v;
        sz++;
        return true;
    }

    bool removeAt(int idx) {
        if (idx < 0 || idx >= sz) {
            std::cout << "removeAt: invalid index " << idx << "\n";
            return false;
        }
        for (int i = idx; i < sz - 1; i++) data[i] = data[i + 1];
        sz--;
        return true;
    }

    bool removeFirst() {
        if (isEmpty()) { std::cout << "removeFirst: array is empty\n"; return false; }
        return removeAt(0);
    }

    bool removeLast() {
        if (isEmpty()) { std::cout << "removeLast: array is empty\n"; return false; }
        sz--;
        return true;
    }

    void display() const {
        if (isEmpty()) { std::cout << "(empty)\n"; return; }
        for (int i = 0; i < sz; i++) std::cout << data[i] << "\n";
    }

    // File format, one record per line: id firstName lastName regNo result grade
    bool loadFromFile(const std::string& filename) {
        std::ifstream in(filename);
        if (!in) { std::cout << "loadFromFile: cannot open " << filename << "\n"; return false; }
        std::string line;
        while (std::getline(in, line)) {
            if (line.empty()) continue;
            std::istringstream ss(line);
            StudentResult s;
            if (ss >> s.id >> s.firstName >> s.lastName >> s.regNo >> s.result >> s.grade)
                push_back(s);
            else
                std::cout << "Skipped malformed line: " << line << "\n";
        }
        return true;
    }

    bool saveToFile(const std::string& filename) const {
        std::ofstream out(filename);
        if (!out) { std::cout << "saveToFile: cannot write " << filename << "\n"; return false; }
        for (int i = 0; i < sz; i++) out << data[i] << "\n";
        return true;
    }
};