#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <locale>

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    system("chcp 1251");
    setlocale(LC_ALL, "Russian");

    // размеры типов (size_t) лежат в куче
    size_t* sizeChar = new size_t(sizeof(char));
    size_t* sizeInt = new size_t(sizeof(int));
    size_t* sizeDouble = new size_t(sizeof(double));
    size_t* sizeLongLong = new size_t(sizeof(long long));
    size_t* sizeLongDouble = new size_t(sizeof(long double));
    size_t* sizePtr = new size_t(sizeof(int*));

    int* p = nullptr;
    if (p == nullptr) {
        std::cout << "p равен nullptr" << std::endl;
    }

    std::cout << "char: " << *sizeChar << std::endl;
    std::cout << "int: " << *sizeInt << std::endl;
    std::cout << "double: " << *sizeDouble << std::endl;
    std::cout << "long long: " << *sizeLongLong << std::endl;
    std::cout << "long double: " << *sizeLongDouble << std::endl;
    std::cout << "указатель: " << *sizePtr << std::endl;

    // сохраняем результаты в файл
    std::ofstream* file = new std::ofstream("result.txt");
    *file << "char: " << *sizeChar << std::endl;
    *file << "int: " << *sizeInt << std::endl;
    *file << "double: " << *sizeDouble << std::endl;
    *file << "long long: " << *sizeLongLong << std::endl;
    *file << "long double: " << *sizeLongDouble << std::endl;
    *file << "указатель: " << *sizePtr << std::endl;
    file->close();

    delete file;
    delete sizeChar;
    delete sizeInt;
    delete sizeDouble;
    delete sizeLongLong;
    delete sizeLongDouble;
    delete sizePtr;

    return 0;
}
