#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    // 1. Делим число на целую и дробную часть по точке
    string whole = s;
    string frac = "";
    int dot = s.find('.');
    if (dot != -1) {
        whole = s.substr(0, dot);
        frac = s.substr(dot + 1);
    }

    // 2. Убираем незначащие нули: слева у целой части, справа у дробной
    while (whole.size() > 0 && whole[0] == '0') {
        whole.erase(0, 1);
    }
    while (frac.size() > 0 && frac[frac.size() - 1] == '0') {
        frac.erase(frac.size() - 1, 1);
    }
    if (whole == "") {
        whole = "0";
    }

    // 3. Дополняем нулями до длины, кратной 4
    //    (целую часть - слева, дробную - справа)
    while (whole.size() % 4 != 0) {
        whole = "0" + whole;
    }
    while (frac.size() % 4 != 0) {
        frac = frac + "0";
    }

    string digits = "0123456789ABCDEF";

    // 4. Целая часть: каждые 4 бита -> одна шестнадцатеричная цифра
    string result = "";
    for (int i = 0; i < whole.size(); i += 4) {
        int number = 0;
        for (int j = 0; j < 4; j++) {
            number = number * 2 + (whole[i + j] - '0');
        }
        result = result + digits[number];
    }

    // 5. Дробная часть - так же, если она не пустая
    if (frac.size() > 0) {
        result = result + ".";
        for (int i = 0; i < frac.size(); i += 4) {
            int number = 0;
            for (int j = 0; j < 4; j++) {
                number = number * 2 + (frac[i + j] - '0');
            }
            result = result + digits[number];
        }
    }

    cout << result << endl;
    return 0;
}
