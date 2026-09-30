// Проект 8: размеры типов через sizeof, nullptr, запись в файл, size_t.
// Все данные лежат в куче (new/delete), проверка утечек: valgrind.
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>

struct Entry {
    const char* name;   // указатель на строковый литерал (не владеем)
    std::size_t size;   // результат sizeof
};

struct Point { int x; int y; };

int main() {
    const std::size_t count = 16;

    // Массив результатов в куче. sizeof считаем от типов, значения не нужны.
    Entry* entries = new Entry[count]{
        {"char",               sizeof(char)},
        {"bool",               sizeof(bool)},
        {"short",              sizeof(short)},
        {"int",                sizeof(int)},
        {"long",               sizeof(long)},
        {"long long",          sizeof(long long)},
        {"float",              sizeof(float)},
        {"double",             sizeof(double)},
        {"long double",        sizeof(long double)},
        {"size_t",             sizeof(std::size_t)},
        {"void*",              sizeof(void*)},
        {"int*",               sizeof(int*)},
        {"std::nullptr_t",     sizeof(std::nullptr_t)},
        {"Point (struct)",     sizeof(Point)},
        {"int[10]",            sizeof(int[10])},
        {"Entry (struct)",     sizeof(Entry)},
    };

    // Демонстрация sizeof для объекта, лежащего в куче:
    // sizeof(указателя) != sizeof(объекта, на который он указывает).
    int* heapInt = new int(42);
    int* heapArr = new int[10];
    std::cout << "sizeof(heapInt)  = " << sizeof(heapInt)  << " (размер указателя)\n";
    std::cout << "sizeof(*heapInt) = " << sizeof(*heapInt) << " (размер int)\n";
    std::cout << "sizeof(heapArr)  = " << sizeof(heapArr)  << " (указатель, не массив!)\n";
    std::cout << "10 * sizeof(*heapArr) = " << 10 * sizeof(*heapArr) << "\n\n";

    // Файл тоже создаём в куче.
    std::ofstream* out = new std::ofstream("sizes.txt");
    if (!out->is_open()) {
        std::cerr << "Не удалось открыть sizes.txt\n";
        delete out;
        delete[] heapArr;
        delete heapInt;
        delete[] entries;
        return 1;
    }

    *out << "Размеры типов (байты):\n";
    std::size_t total = 0;
    for (std::size_t i = 0; i < count; ++i) {   // size_t для индексов и сумм
        std::cout << entries[i].name << ": " << entries[i].size << "\n";
        *out << entries[i].name << ": " << entries[i].size << "\n";
        total += entries[i].size;
    }
    *out << "Сумма: " << total << "\n";
    *out << "Максимум size_t: " << static_cast<std::size_t>(-1) << "\n";
    std::cout << "\nСумма: " << total << "\nРезультаты сохранены в sizes.txt\n";

    // Освобождаем и обнуляем указатели через nullptr.
    out->close();
    delete out;       out = nullptr;
    delete[] heapArr; heapArr = nullptr;
    delete heapInt;   heapInt = nullptr;
    delete[] entries; entries = nullptr;

    if (entries == nullptr && heapInt == nullptr && heapArr == nullptr && out == nullptr)
        std::cout << "Все указатели обнулены (nullptr), память освобождена.\n";
    return 0;
}
