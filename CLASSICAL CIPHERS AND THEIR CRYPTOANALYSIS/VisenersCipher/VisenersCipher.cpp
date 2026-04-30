#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

//-- ALPHABET --//
std::unordered_map<int, char> alphabet =
{   {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'},
    {5, 'F'}, {6, 'G'}, {7, 'H'}, {8, 'I'}, {9, 'J'},
    {10, 'K'}, {11, 'L'}, {12, 'M'}, {13, 'N'}, {14, 'O'},
    {15, 'P'}, {16, 'Q'}, {17, 'R'}, {18, 'S'}, {19, 'T'},
    {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'}, {24, 'Y'},
    {25, 'Z'},
};
const int alphabetSize = 26;


//-- Search key by value function in unordered_map --//
static int letterKeySearch(char letter) {
    int letterKey = -1;

    for (const auto& pair : alphabet) {
        if (pair.second == letter) {
            letterKey = pair.first;
            break;
        }
    }

    return letterKey;
}


// Зашифровка текста
static std::string VisenersCipher(std::string str, std::string key) {
    std::string result = "";

    // Убираем пробелы из текста
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    int strSize = str.length();
    int keySize = key.length();
    std::string newKey(strSize, ' ');

    // Ключ повторяем до значения длины текста
    for (int i = 0; i < strSize; ++i) {
        newKey[i] = key[i % keySize];
    }

    std::cout << "New key: " << newKey << std::endl;

    // Матрица числовых эквивалентов букв
    // 1 строка - текст для зашифровки // 2 строка - ключ
    int matrixRows = 2;
    int matrixCols = strSize;
    std::vector<std::vector<int>> matrix(matrixRows, std::vector<int>(matrixCols));

    // Заполняем матрицу числами соответсвутющих букв
    for (int i = 0; i < matrixRows; ++i) {
        for (int j = 0; j < matrixCols; ++j) {
            if (i == 0)
                matrix[i][j] = letterKeySearch(str[j]);
            else
                matrix[i][j] = letterKeySearch(newKey[j]);

            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "+ & (mod 26)" << std::endl << "----------------------------------" << std::endl;

    // Считаем числовые значения зашифрованных букв и записываем результат
    for (int i = 0; i < strSize; ++i) {
        int encLetterIndex = (matrix[0][i] + matrix[1][i]) % alphabetSize;
        std::cout << encLetterIndex << " ";

        result += alphabet[encLetterIndex];
    }

    std::cout << std::endl;

    return result;
}


int main()
{
    std::string key = "TIME";
    std::string text = "LIKE CURES LIKE";
    std::cout << "Text for encrypting: " << text << " ||Key: " << key << std::endl;

    std::string enc_text = VisenersCipher(text, key);
    std::cout << "Encrypted text: " << enc_text << std::endl;

    return 0;
}