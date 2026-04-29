#include <iostream>
#include <vector>
#include <algorithm>

std::string Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


// Убираем символы что повторяются с проверкой на I = J
static std::string removeDuplicates(const std::string& str) {
    std::string result;

    for (char c : str) {
        if (c == 'J') {
            c = 'I';
        }

        if (result.find(c) == std::string::npos) {
            result += c;
        }
    }

    return result;
}
static std::string PlayferDecipher(std::string str, std::string key) {
    std::string result;

    // Убираем пробелы из фразы ключа
    key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
    int keySize = key.length();

    // Создаем матрицу шифра Плейфера
    int matrixRows = 5;
    int matrixCols = 5;
    std::vector<std::vector<char>> matrix(matrixRows, std::vector<char>(matrixCols));

    // Убираем все дублирующиеся символы из текста фразы + алфавита
    std::string matrixString = removeDuplicates(key + Alphabet);
    
    // Заполняем матрицу и выводим на экран
    int tmp = 0;
    for (int i = 0; i < matrixRows; ++i) {
        for (int j = 0; j < matrixCols; ++j) {
            matrix[i][j] = matrixString[tmp++];
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return result;
}

int main()
{
    std::string key = "WORK";
    std::string enc_text = "QOOFQMDFTFELTQDKBFFP";
    std::cout << "Encrypted text: " << enc_text << std::endl;
    
    std::string dec_text = PlayferDecipher(enc_text, key);
    std::cout << "Decrypted text: " << dec_text << std::endl;

    return 0;
}