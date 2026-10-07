#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include <ctime>

void getArray(int*& arr, int& n) {
    std::cout << "Enter array size N: ";
    std::cin >> n;
    arr = new int[n];
}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    srand((unsigned)time(nullptr));

    int* arr = nullptr;
    int n = 0;

    getArray(arr, n);

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 101 - 50;
    }

    int minValue = *arr;
    int maxValue = *arr;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        if (*(arr + i) < minValue) {
            minValue = *(arr + i);
        }
        if (*(arr + i) > maxValue) {
            maxValue = *(arr + i);
        }
        sum = sum + *(arr + i);
    }
    double average = (double)sum / n;

    std::cout << "Array: ";
    for (int i = 0; i < n; i++) {
        std::cout << *(arr + i) << " ";
    }
    std::cout << std::endl;

    std::cout << "Min: " << minValue << std::endl;
    std::cout << "Max: " << maxValue << std::endl;
    std::cout << "Average: " << average << std::endl;

    delete[] arr;
    arr = nullptr;

    return 0;
}
