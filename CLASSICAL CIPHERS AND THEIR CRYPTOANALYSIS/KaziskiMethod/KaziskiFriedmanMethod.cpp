#include <iostream>
#include <unordered_map>
#include <numeric>
#include <vector>

//-- ALPHABET --//
std::unordered_map<int, char> alphabet =
{ {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'},
    {5, 'F'}, {6, 'G'}, {7, 'H'}, {8, 'I'}, {9, 'J'},
    {10, 'K'}, {11, 'L'}, {12, 'M'}, {13, 'N'}, {14, 'O'},
    {15, 'P'}, {16, 'Q'}, {17, 'R'}, {18, 'S'}, {19, 'T'},
    {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'}, {24, 'Y'},
    {25, 'Z'},
};
const int alphabetSize = 26;


// наибольший общий делитель (greatest common divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

// считаем наибольший общий делитель между первым появлением 
// самой частой триграммы и всеми остальными ее появлениями
static int gcdDistances(std::vector<int>& pos) {
    if (pos.size() < 2) return 0;

    int result = pos[1] - pos[0];

    for (int i = 2; i < pos.size(); ++i) {
        result = gcd(result, pos[i] - pos[0]);
    }

    std::cout << "GCD positions: " << result << std::endl;
    return result;
}

// Подсчёт возможных делителей числа
std::vector<int> getDivisors(int n) {
    std::vector<int> divisors;    
    std::cout << "Divisors: ";

    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
            std::cout << i << " ";
        }
    }

    std::cout << std::endl;
    return divisors;
}



// Метод Казиски для нахождения возможной длины ключа
static std::vector<int> KaziskiMethod(std::string& str) {
    int result = 0;
    int strSize = str.length();

    //-- Будем искать наиболее часто встречаемую триграмму и её позиции --//

    // map всех возможных триграмм
    std::unordered_map<std::string, std::vector<int>> positions;

    for (int i = 0; i <= strSize - 3; ++i) {
        std::string sub = str.substr(i, 3); // записываем подстроку из 3 символов
        positions[sub].push_back(i);        // записываем её в map со значением позиции
    }

    // ищем наиболее частую триграмму
    int maxFreq = 0;
    for (auto& pair : positions) {
        if (pair.second.size() > maxFreq) {
            maxFreq = pair.second.size();
        }
    }

    // выводим только самую частую триграмму и её позиции появления
    std::cout << "Most frequent trigrams: ";
    std::vector<int> maxFreqPositions;

    for (auto& pair : positions) {
        if (pair.second.size() == maxFreq && maxFreq > 1) {
            std::cout << pair.first << std::endl << "   positions: ";
            
            for (int pos : pair.second) {
                maxFreqPositions.push_back(pos);
                std::cout << pos << " ";
            }

            std::cout << std::endl;
        }
    }

    // Далее имея наиболее частую триграмму и значения позиций где она появляется в тексте
    // можем подсчитать примерно длину ключа. Для этого нужно найти наибольший общий делитель между
    // расстояниями от первого до второй встречи + от первой до третьей встречи +
    // от первой до четвёртой встречи и так от первого и до последнего.
    int gcd = gcdDistances(maxFreqPositions);

    // Теперь зная наибольший общий делитель - нужная длина ключа лежит
    // в одном из его возможных делителей. Найдём все возможные делители
    std::vector<int> divisors = getDivisors(gcd);

    // Теперь среди полученных чисел (делителей от НОД от расстояний между позициями 
    // первой и следующими встречами наиболее часто встречаемой триграммы в зашифрованном
    // тексте) должен находиться КЛЮЧ. Проверить какое из чисел нам нужно поможет
    // Метод Фридмана.

    return divisors;
}

// Метод Фридмана для проверки длины ключа
static int FriedmanMethod(std::vector<int> numbers) {
    int result = 0;

    // Необходимо подсчитать индекс совпадения:
    double lcX = 0;

    return result;
}

int main()
{
    int keyLength = 3;
    std::string enc_text = "TCKQZANRAEGDNJAIWOVCJNBZVBOCWNRCPUSNFHKUSHCHDRAPHFJIWOVCJVBPBFANZEGMCESWGZANRAEGYESWGSIBFAYSWQSNFBKGTKYZKJSNFUNROPYSWQSNFVWISRVGEBBOUONRJEFWKAOJQWJFDEESKGVAEGPBQNROPRHDRWNBKJ";
    std::cout << "Encrypted text: " << enc_text << std::endl;

    std::string dec_text;
    std::vector<int> probablyKeys = KaziskiMethod(enc_text);
    int key = FriedmanMethod(probablyKeys);
    //std::string dec_text = KaziskiMethod(enc_text);
    std::cout << "Decrypted text: " << dec_text << std::endl;

    return 0;
}