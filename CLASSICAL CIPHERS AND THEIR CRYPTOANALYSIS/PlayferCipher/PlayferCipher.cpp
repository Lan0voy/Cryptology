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

static std::string PlayferDecipher(std::string enc_str, std::string key) {
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

    // Расшифровка текста
    char tmp1, tmp2;
    for (int i = 0; i < enc_str.length(); i += 2) {
        // Берем по 2 символа
        tmp1 = enc_str[i];
        tmp2 = enc_str[i + 1];
        int tmp1_i, tmp1_j, tmp2_i, tmp2_j;

        // Находим значения индексов символов в матрице
        for (int l = 0; l < matrixRows; ++l) {
            for (int k = 0; k < matrixCols; ++k) {
                if (matrix[l][k] == tmp1) {
                    tmp1_i = l;
                    tmp1_j = k;
                }

                if (matrix[l][k] == tmp2) {
                    tmp2_i = l;
                    tmp2_j = k;
                }
            }
        }

        // Если 2 символа в разных строках и столбцах, то меняем значение индексов столбцов
        if ((tmp1_i != tmp2_i) && (tmp1_j != tmp2_j)) {
            result += matrix[tmp1_i][tmp2_j];
            result += matrix[tmp2_i][tmp1_j];
        }

        // Если символы находятся в 1 строке, то сдвигаем букву на 1 влево
        if (tmp1_i == tmp2_i) {
            if (tmp1_j == 0)
                result += matrix[tmp1_i][matrixCols - 1];
            else
                result += matrix[tmp1_i][tmp1_j - 1];
    
            if (tmp2_j == 0)
                result += matrix[tmp2_i][matrixCols - 1];
            else
                result += matrix[tmp2_i][tmp2_j - 1];
        }

        // Если символы находятся в 1 столбце, то сдвигаем букву та 1 вверх
        if (tmp1_j == tmp2_j) {
            if (tmp1_i == 0)
                result += matrix[matrixRows - 1][tmp1_j];
            else
                result += matrix[tmp1_i - 1][tmp1_j];

            if (tmp2_i == 0)
                result += matrix[matrixRows - 1][tmp2_j];
            else
                result += matrix[tmp2_i - 1][tmp2_j];
        }

        std::cout << tmp1 << " " << tmp1_i << " " << tmp1_j << std::endl;
        std::cout << tmp2 << " " << tmp2_i << " " << tmp2_j << std::endl;

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
    // PRACTICE MAKES PERFECT

    return 0;
}