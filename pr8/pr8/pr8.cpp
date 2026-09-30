#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <locale>

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    system("chcp 1251");
    setlocale(LC_ALL, "Russian");

    // все данные лежат в куче
    const size_t count = 8;
    const char** names = new const char* [count] {
        "char", "short", "int", "long long", "float", "double", "size_t", "int*"
    };
    size_t* sizes = new size_t[count] {
        sizeof(char), sizeof(short), sizeof(int), sizeof(long long),
        sizeof(float), sizeof(double), sizeof(size_t), sizeof(int*)
    };

    size_t* total = new size_t(0);
    int* ptr = nullptr;
    std::ofstream* file = new std::ofstream("sizes.txt");

    if (ptr == nullptr) {
        std::cout << "ptr: nullptr" << std::endl;
    }

    for (size_t i = 0; i < count; ++i) {
        std::cout << names[i] << ": " << sizes[i] << std::endl;
        *file << names[i] << ": " << sizes[i] << std::endl;
        *total += sizes[i];
    }
    std::cout << "Сумма: " << *total << std::endl;
    *file << "Сумма: " << *total << std::endl;

    file->close();
    delete file;
    delete total;
    delete[] sizes;
    delete[] names;
    file = nullptr;
    total = nullptr;
    sizes = nullptr;
    names = nullptr;

    return 0;
}
