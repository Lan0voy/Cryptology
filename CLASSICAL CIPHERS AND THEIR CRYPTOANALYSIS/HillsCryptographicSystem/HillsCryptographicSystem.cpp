#include <iostream>
#include <vector>
#include <unordered_map>

// mod 26
const int alphabetSize = 26;

//-- ALPHABET --//
std::unordered_map<int, char> alphabet =
{   {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'},
    {5, 'F'}, {6, 'G'}, {7, 'H'}, {8, 'I'}, {9, 'J'},
    {10, 'K'}, {11, 'L'}, {12, 'M'}, {13, 'N'}, {14, 'O'},
    {15, 'P'}, {16, 'Q'}, {17, 'R'}, {18, 'S'}, {19, 'T'},
    {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'}, {24, 'Y'},
    {25, 'Z'},
};

//-- Search key by value function in unordered_map --//
int letterKeySearch(char letter) {
    int letterKey = -1;

    for (const auto& pair : alphabet) {
        if (pair.second == letter) {
            letterKey = pair.first;
            break;
        }
    }

    return letterKey;
}

// Умножение матрицы на вектор
std::vector<int> matrixMultiplication(std::vector<std::vector<int>>& matrix, std::vector<int> tmpVector, int size) {
    std::vector<int> result(size, 0);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i] += matrix[i][j] * tmpVector[j];
        } 
        result[i] = result[i] % alphabetSize;
        std::cout << result[i] << std::endl;
    }


    return result;
}

// Дешифровка криптосистемы Хилла
static std::string HillsDecipher(std::vector<std::vector<int>>& matrix, std::string& str) {
    std::string result;
    int matrixSize = matrix.size();
    std::vector<int> lettersVector(matrixSize);

    for (int i = 0; i < str.length(); i += matrixSize) {
        // Разбиваем зашифрованное сообщение на кол-во букв, равное размерности матрицы
        // для последующего умножения и преобразуем буквы в численное значение
        for (int j = 0; j < matrixSize; ++j) {
            int letterIndex = i + j;
            lettersVector[j] = letterKeySearch(str[letterIndex]);
       }

        // Умножение матрицы ключа на преобразованные буквы
        std::vector<int> tmpVector = matrixMultiplication(matrix, lettersVector, matrixSize);
        
        // По вычисленным значениям записываем полученные буквы
        for (int l = 0; l < matrixSize; ++l) {
            result += alphabet[tmpVector[l]];
        }     
    }

    return result;
}

int main()
{
    std::vector<std::vector<int>> encMatrix = {
        {8, 5, 10},
        {21, 8, 21},
        {21, 12, 8}
    };

    std::string enc_text = "WRHSHXLASLQV";
    std::cout << "Encrypted text: " << enc_text << std::endl;

    std::string dec_text = HillsDecipher(encMatrix, enc_text);
    std::cout << "Decrypted text: " << dec_text << std::endl;

    return 0;
}