// ДЗ 3, pr7 — работа с файлами тремя способами: WinAPI, fopen (C), fstream (C++)
//   1. CreateFile — создать новый файл через WinAPI (если файл существует — спросить о перезаписи)
//   2. Add — через функции C-библиотеки: предложение в конец, затем в начало, затем снова в конец
//   3. Read — прочитать файл через fstream
//   4. Вывести текст на консоль

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const char* FILE_NAME = "text.txt";

// ---------- 1. Создание файла через WinAPI ----------
bool createFileWinAPI(const char* name)
{
    // CREATE_NEW — создать файл, только если его ещё нет
    HANDLE hFile = CreateFileA(name, GENERIC_WRITE, 0, NULL,
                               CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() != ERROR_FILE_EXISTS)
        {
            cout << "Ошибка создания файла, код: " << GetLastError() << endl;
            return false;
        }

        cout << "Файл \"" << name << "\" уже существует. Перезаписать? (y/n): ";
        string answer;
        getline(cin, answer);
        if (answer.empty() || (answer[0] != 'y' && answer[0] != 'Y'))
        {
            cout << "Файл оставлен без изменений." << endl;
            return true;
        }

        // CREATE_ALWAYS — создать заново (старое содержимое удаляется)
        hFile = CreateFileA(name, GENERIC_WRITE, 0, NULL,
                            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            cout << "Ошибка перезаписи файла, код: " << GetLastError() << endl;
            return false;
        }
        cout << "Файл перезаписан." << endl;
    }
    else
    {
        cout << "Файл \"" << name << "\" создан." << endl;
    }

    CloseHandle(hFile);
    return true;
}

// ---------- 2. Добавление записей через функции C ----------

// Добавить строку в конец файла
bool addToEnd(const char* name, const string& text)
{
    FILE* f = fopen(name, "a");
    if (!f)
    {
        cout << "Не удалось открыть файл для дозаписи." << endl;
        return false;
    }
    fputs(text.c_str(), f);
    fputs("\n", f);
    fclose(f);
    return true;
}

// Добавить строку в начало файла:
// читаем всё содержимое, затем записываем новую строку и старое содержимое
bool addToBeginning(const char* name, const string& text)
{
    FILE* f = fopen(name, "rb");
    if (!f)
    {
        cout << "Не удалось открыть файл для чтения." << endl;
        return false;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buffer = (char*)malloc(size > 0 ? size : 1);
    size_t readBytes = fread(buffer, 1, size, f);
    fclose(f);

    f = fopen(name, "wb");
    if (!f)
    {
        cout << "Не удалось открыть файл для записи." << endl;
        free(buffer);
        return false;
    }
    fputs(text.c_str(), f);
    fputs("\r\n", f);
    fwrite(buffer, 1, readBytes, f);
    fclose(f);

    free(buffer);
    return true;
}

string inputSentence(const char* prompt)
{
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

// ---------- 3. Чтение через fstream ----------
bool readFileFstream(const char* name, string& content)
{
    ifstream in(name);
    if (!in.is_open())
    {
        cout << "Не удалось открыть файл через fstream." << endl;
        return false;
    }
    string line;
    while (getline(in, line))
        content += line + "\n";
    in.close();
    return true;
}

int main()
{
    // Русский текст в консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // 1. CreateFile (WinAPI)
    cout << "=== 1. Создание файла (WinAPI) ===" << endl;
    if (!createFileWinAPI(FILE_NAME))
        return 1;

    // 2. Add (функции C)
    cout << "\n=== 2. Добавление записей (fopen) ===" << endl;
    if (!addToEnd(FILE_NAME, inputSentence("Введите предложение (в конец файла): ")))
        return 1;
    if (!addToBeginning(FILE_NAME, inputSentence("Введите предложение (в начало файла): ")))
        return 1;
    if (!addToEnd(FILE_NAME, inputSentence("Введите предложение (снова в конец файла): ")))
        return 1;

    // 3. Read (fstream)
    string content;
    if (!readFileFstream(FILE_NAME, content))
        return 1;

    // 4. Вывод на консоль
    cout << "\n=== 3-4. Содержимое файла (fstream) ===" << endl;
    cout << content;

    system("pause");
    return 0;
}
