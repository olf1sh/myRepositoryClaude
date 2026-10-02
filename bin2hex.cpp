#include <iostream>
#include <string>
using namespace std;

// Переводит строку из нулей и единиц (длина кратна 4) в шестнадцатеричную строку
string toHex(string bits) {
    string digits = "0123456789ABCDEF";
    string hex = "";
    int n = bits.size();
    for (int i = 0; i < n; i += 4) {
        // 4 бита -> число от 0 до 15
        int number = (bits[i] - '0') * 8 + (bits[i + 1] - '0') * 4
                   + (bits[i + 2] - '0') * 2 + (bits[i + 3] - '0');
        hex = hex + digits[number];
    }
    return hex;
}

int main() {
    string s;
    cin >> s;

    // Делим число на целую и дробную части: идём по символам,
    // до точки кладём их в whole, после точки - в frac
    string whole = "";
    string frac = "";
    bool afterDot = false;
    int len = s.size();
    for (int i = 0; i < len; i++) {
        if (s[i] == '.') {
            afterDot = true;
        } else if (afterDot) {
            frac = frac + s[i];
        } else {
            whole = whole + s[i];
        }
    }

    // Дополняем нулями до длины, кратной 4
    while (whole.size() % 4 != 0) {
        whole = "0" + whole;   // слева
    }
    while (frac.size() % 4 != 0) {
        frac = frac + "0";     // справа
    }

    string a = toHex(whole);
    string b = toHex(frac);

    // Убираем лишние нули: слева у целой части, справа у дробной
    while (a.size() > 1 && a[0] == '0') {
        a.erase(0, 1);
    }
    while (b.size() > 0 && b[b.size() - 1] == '0') {
        b.erase(b.size() - 1, 1);
    }
    if (a == "") {
        a = "0";
    }

    // Выводим результат
    if (b == "") {
        cout << a << endl;
    } else {
        cout << a << "." << b << endl;
    }
    return 0;
}
