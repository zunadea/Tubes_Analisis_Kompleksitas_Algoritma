#include <iostream>
#include <chrono>

using namespace std;

int MaxMinIteratif(int A[], int n, int &minVal, int &maxVal) {
    minVal = A[0];
    maxVal = A[0];

    for (int i = 1; i < n; i++) {
        if (A[i] < minVal)
            minVal = A[i];
        if (A[i] > maxVal)
            maxVal = A[i];
    }
    return 0;
}

int MaxMinDAC(int A[], int low, int high, int &minVal, int &maxVal) {
    if (low == high) {
        minVal = maxVal = A[low];
        return 0;
    }

    if (high == low + 1) {
        if (A[low] < A[high]) {
            minVal = A[low];
            maxVal = A[high];
        } else {
            minVal = A[high];
            maxVal = A[low];
        }
        return 0;
    }

    int mid = (low + high) / 2;
    int min1, max1, min2, max2;

    MaxMinDAC(A, low, mid, min1, max1);
    MaxMinDAC(A, mid + 1, high, min2, max2);

    minVal = (min1 < min2) ? min1 : min2;
    maxVal = (max1 > max2) ? max1 : max2;

    return 0;
}

int main() {
    const int ulang = 300000;
    volatile int dummy = 0;

    const int sizes[3] = {200, 500, 1000};

    static int A200[200];
    static int A500[500];
    static int A1000[1000];

    for (int i = 0; i < 200; i++) A200[i] = (i * 37) % 997;
    for (int i = 0; i < 500; i++) A500[i] = (i * 53) % 1999;
    for (int i = 0; i < 1000; i++) A1000[i] = (i * 71) % 2999;

    int *arrays[3] = {A200, A500, A1000};

    cout << "n,iteratif_ns,rekursif_ns\n";

    for (int i = 0; i < 3; i++) {
        int n = sizes[i];
        int *A = arrays[i];
        int minVal, maxVal;

        auto start1 = chrono::high_resolution_clock::now();
        for (int k = 0; k < ulang; k++) {
            MaxMinIteratif(A, n, minVal, maxVal);
            dummy += minVal + maxVal;
        }
        auto end1 = chrono::high_resolution_clock::now();

        auto start2 = chrono::high_resolution_clock::now();
        for (int k = 0; k < ulang; k++) {
            MaxMinDAC(A, 0, n - 1, minVal, maxVal);
            dummy += minVal + maxVal;
        }
        auto end2 = chrono::high_resolution_clock::now();

        long long tIter =
            chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();
        long long tRek =
            chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count();

        cout << n << "," << (tIter / ulang) << "," << (tRek / ulang) << "\n";
    }

    return 0;
}
