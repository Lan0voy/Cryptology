#include <iostream>
#include <vector>

// Дешифровка шифра частоколу
static std::string RailFenceDecipher(std::string str, int key) {
    std::string s = str;

    // Подсчет кол-ва букв и столбцов
    int letterCounter = s.length();
    int column = (letterCounter + key - 1) / key; // + key - 1: столбец последний может быть не до конца заполнен, не потерять остаточные значения

    // Массив символов куда будет записывать разбитые строки
    std::vector<std::vector<char>> table(key, std::vector<char>(column));

    // Заполняем вектор как разбивается зашифрованный текст на строки и столбцы
    for (int i = 0, k = 0; i < key; ++i) {
        for (int j = 0; j < column; ++j) {
            if (k < s.length()) {
                std::cout << s[k];
                table[i][j] = s[k];
                ++k;
            }
        }

        std::cout << std::endl;
    }

    std::string result;

    // Выводим снизу вверх, столбцы по очереди и получаем результат
    for (int j = 0; j < column; ++j) {
        for (int i = key - 1; i >= 0; --i) {
            if (table[i][j] != '\0') {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

int main()
{
    const int key = 4;
    std::string enc_text = "TEOSTSWHISARTEEEOSMB";
    std::cout << "Encrypted text: " << enc_text << std::endl;

    std::string dec_text = RailFenceDecipher(enc_text, key);
    std::cout << "Decrypted text: " << dec_text << std::endl;
    // East or West, Home is Best

    return 0;
}