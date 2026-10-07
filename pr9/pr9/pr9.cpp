#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include <ctime>
#include <locale>

// Функция спрашивает у пользователя размер N и создаёт динамический массив.
// arr и n передаются по ссылке (знак &), поэтому всё, что мы в них запишем,
// останется в main. Так функция "возвращает" массив, хотя она void.
void getArray(int*& arr, int& n) {
    n = 0;
    while (n <= 0) {
        std::cout << "Введите размер массива N: ";
        std::cin >> n;
        if (std::cin.fail()) {            // ввели не число (например, буквы)
            std::cin.clear();             // убираем ошибку ввода
            std::cin.ignore(1000, '\n');  // выбрасываем лишние символы
            n = 0;
        }
        if (n <= 0) {
            std::cout << "N должно быть числом больше нуля!" << std::endl;
        }
    }
    arr = new int[n];   // создаём массив в куче
}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    system("chcp 1251");
    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(nullptr));   // чтобы числа каждый раз были разные

    int* arr = nullptr;   // указатель на будущий массив
    int n = 0;            // размер массива

    getArray(arr, n);

    // Заполняем через индексацию числами от -50 до 50.
    // rand() % 101 даёт числа от 0 до 100, а минус 50 сдвигает их к диапазону от -50 до 50.
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 101 - 50;
    }

    // Дальше работаем через арифметику указателей.
    // *(arr + i) - это то же самое, что arr[i].
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

    std::cout << "Массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << *(arr + i) << " ";
    }
    std::cout << std::endl;

    std::cout << "Минимальный элемент: " << minValue << std::endl;
    std::cout << "Максимальный элемент: " << maxValue << std::endl;
    std::cout << "Среднее арифметическое: " << average << std::endl;

    // Освобождаем память, которую взяли через new[]
    delete[] arr;
    arr = nullptr;

    return 0;
}
