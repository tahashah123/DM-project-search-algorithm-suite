/*
CS-101: Discrete Mathematics - Research Project
Instructor: Mr. Waqas Ali
Project Title: Search Algorithm Suite and Performance Analyzer
Team members: Syed Muhammad Taha, Muhammad Junaid
University: University of Engineering and Technology Lahore
Department: Computer Science

Project Overview:

This project implements and analyzes four fundamental search algorithms:
1. Linear Search
2. Binary Search
3. Interpolation Search
4. Exponential Search

Features:

-Menu-driven command-line interface.
-options for manual or random array input.
-Sorted array validation for algorithms that require it.
-Execution time measurement for each search operation.
-comparative analysis of all algorithms
===============================================================================
*/
#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

void cntr()
{
    cout << "\t\t\t\t"; // simple center using tabs
}

// validation for sorted array
bool isSorted(int arr[], int n)
{
    bool ascending = true, descending = true;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] < arr[i + 1])
            descending = false;
        if (arr[i] > arr[i + 1])
            ascending = false;
    }
    return ascending || descending;
}

// print array
void showArray(int arr[], int n)
{
    cntr(); // center the line
    cout << "Array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
        if ((i + 1) % 20 == 0)
        { // new line every 20 numbers
            cout << "\n";
            cntr(); // re-center the new line
        }
    }
    cout << "\n";
}

// shuffle array for linear search
void shuffleArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int j = rand() % n;
        swap(arr[i], arr[j]);
    }
}

// measure execution time
long long measureTime(int (*searchFunc)(int[], int, int), int arr[], int n, int key, int &index)
{
    const int runs = 100000;
    long long totalTime = 0;
    for (int i = 0; i < runs; i++)
    {
        auto start = high_resolution_clock::now();
        index = searchFunc(arr, n, key);
        auto end = high_resolution_clock::now();
        totalTime += duration_cast<nanoseconds>(end - start).count();
    }
    return totalTime / runs;
}

// ---------- Search Algorithms ----------
int linearSearch(int arr[], int n, int key)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == key)
            return i;
    return -1;
}

int binarySearch(int arr[], int n, int key)
{
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int interpolationSearch(int arr[], int n, int key)
{
    int low = 0, high = n - 1;
    while (low <= high && key >= arr[low] && key <= arr[high])
    {
        if (arr[high] == arr[low])
            return (arr[low] == key) ? low : -1;
        int pos = low + ((key - arr[low]) * (high - low)) / (arr[high] - arr[low]);
        if (pos < low || pos > high)
            return -1;
        if (arr[pos] == key)
            return pos;
        else if (arr[pos] < key)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}

int exponentialSearch(int arr[], int n, int key)
{
    if (arr[0] == key)
        return 0;
    int i = 1;
    while (i < n && arr[i] <= key)
        i *= 2;
    int low = i / 2, high = (i < n) ? i : n - 1;
    int res = binarySearch(arr + low, high - low + 1, key);
    return (res == -1) ? -1 : res + low;
}

// -------------------- Main --------------------
int main()
{
    srand(time(0));
    int choice;
    do
    {
        cntr();
        cout << "==================================================\n";
        cntr();
        cout << "S E A R C H     A L G O R I T H M     S U I T E \n";
        cntr();
        cout << "==================================================\n";
        cntr();
        cout << "1. Linear Search\n";
        cntr();
        cout << "2. Binary Search\n";
        cntr();
        cout << "3. Interpolation Search\n";
        cntr();
        cout << "4. Exponential Search\n";
        cntr();
        cout << "5. Comparative Analysis\n";
        cntr();
        cout << "6. Exit\n";
        cntr();
        cout << "Select option: ";
        cin >> choice;

        if (choice == 6)
            break;

        int n;
        cntr();
        cout << "Enter number of elements (max 1000): ";
        cin >> n;
        if (n <= 0 || n > 1000)
        {
            cntr();
            cout << "Invalid array size!\n";
            continue;
        }

        int arr[1000], inputType;
        cntr();
        cout << "1. Manual input\n";
        cntr();
        cout << "2. Random numbers (1 to " << n << ")\n";
        cntr();
        cout << "Select: ";
        cin >> inputType;

        if (inputType == 1)
        {
            cntr();
            cout << "Enter elements:\n";
            for (int i = 0; i < n; i++)
                cin >> arr[i];
        }
        else if (inputType == 2)
        {
            for (int i = 0; i < n; i++)
                arr[i] = i + 1;
            if (choice == 1)
                shuffleArray(arr, n);
        }
        else
        {
            cntr();
            cout << "Invalid Input!\n";
            continue;
        }

        if ((choice == 2 || choice == 3 || choice == 4) && !isSorted(arr, n))
        {
            cntr();
            cout << "ERROR: Array must be sorted for this algorithm.\n";
            continue;
        }

        showArray(arr, n);

        int key;
        cntr();
        cout << "Enter number to search: ";
        cin >> key;
        int index = -1;
        long long timeTaken = 0;

        // ---------------- basic intro of each algorithm ----------------
        if (choice >= 1 && choice <= 4)
        {
            cntr();
            switch (choice)
            {
            case 1: // Linear Search
                cout << "Linear Search:\n";
                cntr();
                cout << "Checks each element sequentially.\n";
                cntr();
                cout << "Best for small or unsorted arrays.\n";
                cntr();
                cout << "Time complexity: O(n)\n\n";
                timeTaken = measureTime(linearSearch, arr, n, key, index);
                break;
            case 2: // Binary Search
                cout << "Binary Search:\n";
                cntr();
                cout << "Divides sorted array repeatedly in half.\n";
                cntr();
                cout << "Efficient for large sorted arrays.\n";
                cntr();
                cout << "Time complexity: O(log n)\n\n";
                timeTaken = measureTime(binarySearch, arr, n, key, index);
                break;
            case 3: // Interpolation Search
                cout << "Interpolation Search:\n";
                cntr();
                cout << "Estimates position based on key value.\n";
                cntr();
                cout << "Works best for uniformly distributed sorted arrays.\n";
                cntr();
                cout << "Time complexity: O(log log n) in best case.\n\n";
                timeTaken = measureTime(interpolationSearch, arr, n, key, index);
                break;
            case 4: // Exponential Search
                cout << "Exponential Search:\n";
                cntr();
                cout << "Finds a range then applies binary search.\n";
                cntr();
                cout << "Useful for very large or unbounded sorted arrays.\n";
                cntr();
                cout << "Time complexity: O(log n)\n\n";
                timeTaken = measureTime(exponentialSearch, arr, n, key, index);
                break;
            }
        }
        // ---------------- Result Display ----------------
        if (choice >= 1 && choice <= 4)
        {
            cntr();
            cout << "--- RESULT ---\n";
            if (index != -1)
            {
                cntr();
                cout << "Element found at index: " << index << "\n";
            }
            else
            {
                cntr();
                cout << "Element not found\n";
            }
            cntr();
            cout << "Execution Time: " << timeTaken << " nanoseconds\n";
            cout << "\n";
        }

        // ---------------- Comparative Analysis ----------------
        if (choice == 5)
        {
            cntr();
            cout << "======================\n";
            cntr();
            cout << " COMPARATIVE ANALYSIS \n";
            cntr();
            cout << "======================\n";
            cntr();
            cout << "----------------------------------------\n";
            cntr();
            cout << "Algorithm\t\tIndex\tTime(ns)\n";
            cntr();
            cout << "----------------------------------------\n";
            int idx;
            long long t;
            t = measureTime(linearSearch, arr, n, key, idx);
            cntr();
            cout << "Linear Search\t\t" << idx << "\t" << t << "\n";
            t = measureTime(binarySearch, arr, n, key, idx);
            cntr();
            cout << "Binary Search\t\t" << idx << "\t" << t << "\n";
            t = measureTime(interpolationSearch, arr, n, key, idx);
            cntr();
            cout << "Interpolation Search\t" << idx << "\t" << t << "\n";
            t = measureTime(exponentialSearch, arr, n, key, idx);
            cntr();
            cout << "Exponential Search\t" << idx << "\t" << t << "\n";
        }

    } while (true);

    cntr();
    cout << "Program exited.\n";
    return 0;
}