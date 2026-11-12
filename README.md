# VU-BCS-2507-2085-EVE - Assignment 2

**Student:** EVE - VU-BCS-2507-2085-EVE
**Module:** Data Structures & Algorithms

## A1 - DynamicArray (Custom, No std::vector)
Custom templated DynamicArray with doubling resize, push_back, insertAt, removeAt, removeFirst, removeLast, at, size, capacity.

## A2 - Sorting & Searching
- Insertion Sort - STABLE, O(n) best, O(n^2) worst
- Quicksort - RANDOM PIVOT, O(n log n) average, O(n^2) worst (unlikely)
- Binary Search - ITERATIVE, O(log n), requires array sorted by RegNo

## A3 - Testing
Boundary tests in TestA3.cpp:
T1 Empty, T2 One record, T3 Duplicate key (stability), T4 RemoveFirst/RemoveLast, T5 Already sorted/Reversed, T6 Search absent.
All PASS. Compiled with -g -Wall -Wextra, zero warnings.
Note: -fsanitize=address fails to link on Windows MinGW (library not bundled), so -Wall evidence used instead.

## A4 - Timing Results (Average of 3 runs, ms)
| n | Insertion | Quicksort |
|---|---|---|
| 1000 | 80.67 | 17.33 |
| 2000 | 300.00 | 11.33 |
| 4000 | 961.67 | 24.00 |
| 8000 | 4088.00 | 80.33 |
| 16000 | 20332.00 | 216.00 |
| 32000 | skipped (too slow) | 610.33 |
| 64000 | skipped (too slow) | 1277.33 |

Insertion doubling ~4x = O(n^2). Quicksort doubling ~2x = O(n log n).

## How to Run
g++ main.cpp -o A2.exe
.\A2.exe

g++ TestA3.cpp -o TestA3.exe
.\TestA3.exe

g++ TimingA4.cpp -o TimingA4.exe
.\TimingA4.exe

## AI Declaration
AI (Meta AI) was used for guidance, debugging, and structuring the report. All code was understood, tested, and verified by the student. Final code is the student's own work.