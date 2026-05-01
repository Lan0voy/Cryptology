#include <iostream>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <cmath>
#include <algorithm>

//-- АЛФАВИТ --//
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
static std::vector<int> getDivisors(int n) {
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
    std::cout << "----------------------------------------" << std::endl;
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


// Частоты каждой буквы в англ языке
std::unordered_map<char, double> frequencyEngAlphabet = {
    {'A', 0.082}, {'B', 0.015}, {'C', 0.028}, {'D', 0.043}, {'E', 0.127},
    {'F', 0.022}, {'G', 0.020}, {'H', 0.061}, {'I', 0.070}, {'J', 0.002},
    {'K', 0.008}, {'L', 0.040}, {'M', 0.024}, {'N', 0.067}, {'O', 0.075},
    {'P', 0.019}, {'Q', 0.001}, {'R', 0.060}, {'S', 0.063}, {'T', 0.091},
    {'U', 0.028}, {'V', 0.010}, {'W', 0.023}, {'X', 0.001}, {'Y', 0.020},
    {'Z', 0.001},
};

// Частоты каждой буквы в тексте
static std::unordered_map<char, double> frequencyLettersText(std::string text) {
    // Создаем unordered_map и считаем количество появлений каждой буквы в
    // зашифрованном тексте, считаем вероятность их появлений и берём букву
    // с наибольшей вероятностью
    std::unordered_map<char, double> frequencyEncryptedText = {
        {'A', 0}, {'B', 0}, {'C', 0}, {'D', 0}, {'E', 0},
        {'F', 0}, {'G', 0}, {'H', 0}, {'I', 0}, {'J', 0},
        {'K', 0}, {'L', 0}, {'M', 0}, {'N', 0}, {'O', 0},
        {'P', 0}, {'Q', 0}, {'R', 0}, {'S', 0}, {'T', 0},
        {'U', 0}, {'V', 0}, {'W', 0}, {'X', 0}, {'Y', 0},
        {'Z', 0},
    };

    //std::cout << "Letter frequencies in text: " << std::endl;
    // Считаем частоту появлений букв в зашифрованном тексте
    for (char c : text) {
        if (c >= 'A' && c <= 'Z') {
            frequencyEncryptedText[c]++;
        }
    }

    // Вывод полученного
    /*
    int k = 0;
    for (char c = 'A'; c <= 'Z'; ++c) {
        k++;
        std::cout << c << ": " << frequencyEncryptedText[c] << "   ";
        if (k == 7) {
            std::cout << std::endl;
            k = 0;
        }
    }
    std::cout << std::endl;*/

    return frequencyEncryptedText;
}


//Метод Фридмана для проверки длины и получению 1 самого вероятного значения
/*
static int FriedmanMethod(std::vector<int> numbers, std::string text) {
    std::cout << "----------------------------------------" << std::endl;

    // Необходимо подсчитать длину ключа - l:
    double l = 0;               // длина ключа
    
    double lcx = 0;             // индекс совпадений шифротекста
    double m = alphabetSize;    // размер алфавита
    double kr = 1 / m;          // индекс совпадений случайного текста
    double kp = 0;              // индекс совпадений англ языка   
    double p = 0;               // верояность для каждой буквы англ алфавита
    double n = text.length();   // длина шифротекста 

    // индекс совпадений англ языка kp = 0.065
    for (auto &pair : frequencyEngAlphabet) {
        p = pair.second;
        kp += p * p;
    }
    
    // считаем частоту появлений букв в зашифрованном тексте для lcx
    std::unordered_map<char, double> frequencyEncryptedText = frequencyLettersText(text);

    // считаем lcx - индекс совпадений шифротекста
    for (auto& pair : frequencyEncryptedText) {
        double ni = pair.second;
        lcx += ni * (ni - 1);
    }
    lcx = lcx / (n * (n - 1));

    // Теперь с помощью формулы считаем приблизительное значение длины ключа
    l = (kp - kr) / (lcx - kr + ((kp - lcx) / n));

    // Дальше имея вектор возможных значений длин ключ из метода Казиски
    // можем сравнить с полученным значением из метода Фридмана и выбрать
    // наиболее подходящее

    int result = numbers[0];
    double minDiff = std::abs(numbers[0] - l);
    for (int i : numbers) {
        double diff = std::abs(i - l);

        if (diff < minDiff) {
            minDiff = diff;
            result = i;
        }
    }



    //std::cout << "kr = " << kr << std::endl;
    std::cout << "kp = " << kp << std::endl;
    std::cout << "Ic = " << lcx << std::endl;
    std::cout << " l = " << l << std::endl;
    std::cout << "Key length = " << result << std::endl;

    return result;
}*/

//Метод Фридмана для проверки длины вектора возможных длин и сортировки их от наиболее вероятного
static std::vector<int> FriedmanMethod(std::vector<int> numbers, std::string text) {
    std::cout << "----------------------------------------" << std::endl;

    // Необходимо подсчитать длину ключа - l:
    double l = 0;               // длина ключа

    double lcx = 0;             // индекс совпадений шифротекста
    double m = alphabetSize;    // размер алфавита
    double kr = 1 / m;          // индекс совпадений случайного текста
    double kp = 0;              // индекс совпадений англ языка   
    double p = 0;               // верояность для каждой буквы англ алфавита
    double n = text.length();   // длина шифротекста 

    // индекс совпадений англ языка kp = 0.065
    for (auto& pair : frequencyEngAlphabet) {
        p = pair.second;
        kp += p * p;
    }

    // считаем частоту появлений букв в зашифрованном тексте для lcx
    std::unordered_map<char, double> frequencyEncryptedText = frequencyLettersText(text);

    // считаем lcx - индекс совпадений шифротекста
    for (auto& pair : frequencyEncryptedText) {
        double ni = pair.second;
        lcx += ni * (ni - 1);
    }
    lcx = lcx / (n * (n - 1));

    // Теперь с помощью формулы считаем приблизительное значение длины ключа
    l = (kp - kr) / (lcx - kr + ((kp - lcx) / n));
    
    // std::sort
    // берёт все элементы в numbers и начинает их сравнивать попарно :
    // “что должно идти раньше: a или b?”
    // (a, b) → true / false
    // std::abs(a - l) < std::abs(b - l) --> a ближе к l, чем b?
    std::sort(numbers.begin(), numbers.end(),
        [l](int a, int b) {
            return std::abs(a - l) < std::abs(b - l);
        }
    );
    
    // Вывод полученных данных
    std::cout << "Friedman l = " << l << std::endl;
    std::cout << "Key length candidates: ";

    for (int x : numbers) {
        if (x > 1) {
            std::cout << x << " ";
        }
    }
    std::cout << std::endl;

    /*
    // Дальше имея вектор возможных значений длин ключ из метода Казиски
    // можем сравнить с полученным значением из метода Фридмана и выбрать
    // 1 наиболее подходящее

    int result = numbers[0];
    double minDiff = std::abs(numbers[0] - l);
    for (int i : numbers) {
        double diff = std::abs(i - l);

        if (diff < minDiff) {
            minDiff = diff;
            result = i;
        }
    }



    //std::cout << "kr = " << kr << std::endl;
    std::cout << "kp = " << kp << std::endl;
    std::cout << "Ic = " << lcx << std::endl;
    std::cout << " l = " << l << std::endl;
    std::cout << "Key length = " << result << std::endl;*/

    return numbers;
}



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

//-- Caesar Decrypting text function --//
static std::string CaesarDecipher(std::string str, int key) {
    std::string s = str;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] != ' ') {
            int number = (letterKeySearch(str[i]) - key + alphabetSize) % alphabetSize;
            s[i] = alphabet[number];
        }
    }
    //std::cout << "Decrypted text: " << s << std::endl;

    return s;
}




// По длине ключа взламываем сам ключ
static std::string keyDecipher(int keyLength, std::string enc_text) {
    std::string result = "";
    std::cout << "----------------------------------------" << std::endl;

    // идея от чата гпт - использовать критерий метрики Пирсона. Это позволяет нам гораздо точнее определить вероятный ключ от текста
    // но для этого нам нужно перебрать всевозможные варианты (26 букв алфавита для каждого столбца)
    // 1. Берём длину ключа l
    // 2. Разбиваем текст на l столбцов
    // 3. Каждый столбец считаем отдельным шифром цезаря
    // 4. Для каждого столбца перебираем все 26 сдвигов и выбираем лучшее значение по критерию метрики Пирсона
    // 5. Получаем с каждого столбца свою букву ключа
    // 6. Собираем ключ со всех столбцов

    int textLength = enc_text.length();
    std::vector<std::string> tables(keyLength);
    std::vector<std::unordered_map<char, double>> letterFrequencies(keyLength);
    std::vector<std::unordered_map<char, double>> tmpLetterFrequencies(keyLength);
    
    // Разбиваем текст на l столбцов и рассматриваем по очереди каждый столбец
    for (int i = 0; i < keyLength; ++i) {

        // Заполняем столбец буквами
        for (int j = i; j < textLength; j += keyLength) {
            tables[i].push_back(enc_text[j]);
        }
        std::cout << tables[i] << std::endl;

        double tmpTableLength = tables[i].length(); // длина текста в столбце

        // Считаем частоты появлений каждой буквы в столбце
        letterFrequencies[i] = frequencyLettersText(tables[i]);
        for (auto& pair : letterFrequencies[i]) {
            pair.second = pair.second / tmpTableLength;
            //std::cout << pair.second << " ";
        }

        // Для каждого столбца перебираем все возможные 26 сдвигов по шифру Цезаря
        // расшифровываем столбец и считаем критерий метрики Пирсона
        // х^2 = sum((observed - expected)^2 / expected)
        // observed - сколько раз буква реально встретилась
        // expected - сколько раз должно быть по частотам появлений букв в англ языке
        // далее сдвиг с минимальным х^2 это и будет нужный сдвиг

        double bestCaesarKey = 0;
        double bestX2 = 1e18;
        // Проход по каждой букве алфавита как возможный ключ шифра цезаря
        for (int k = 0; k < alphabetSize; ++k) {
            // Пробуем расшифровать столбец
            std::string tmpStr = CaesarDecipher(tables[i], k);

            
            // Считаем частоты появлений каждой буквы в расшифрованном столбце
            tmpLetterFrequencies[i] = frequencyLettersText(tmpStr);

            // Считаем метрику Пирсона для каждого из случаев ключа шифра Цезаря
            // и выбираем лучший вариант
            double x2 = 0;

            for (char c = 'A'; c <= 'Z'; ++c) {
                double observed = tmpLetterFrequencies[i][c] / tmpTableLength;
                double expected = frequencyEngAlphabet[c];
                
                if (expected > 0) {
                    x2 += pow(observed - expected, 2) / expected;
                }
            }

            if (x2 < bestX2) {
                bestX2 = x2;
                bestCaesarKey = k;
            }
        }

        result += char('A' + bestCaesarKey);
    }

    //std::cout << "Key = " << result << std::endl;
    return result;
}

// Расшифровываем шифр Виженера ключом
static std::string VisenereDecipher(std::string enc_text, std::string key) {
    std::string result = "";
    int textLength = enc_text.length();
    int keyLength = key.length();

    for (int i = 0; i < textLength; ++i) {
        char letter = enc_text[i];

        if (letter >= 'A' && letter <= 'Z') {
            int cipherIndex = letter - 'A';             // число зашифрованной буквы
            int keyIndex = key[i % keyLength] - 'A';    // число буквы ключа

            int dec = (cipherIndex - keyIndex + alphabetSize) % alphabetSize;

            result += char('A' + dec);
        }
    }

    //std::cout << result << std::endl;
    return result;
}

int main()
{
    //int keyLength = 3;
    std::string enc_text = "TCKQZANRAEGDNJAIWOVCJNBZVBOCWNRCPUSNFHKUSHCHDRAPHFJIWOVCJVBPBFANZEGMCESWGZANRAEGYESWGSIBFAYSWQSNFBKGTKYZKJSNFUNROPYSWQSNFVWISRVGEBBOUONRJEFWKAOJQWJFDEESKGVAEGPBQNROPRHDRWNBKJ";
    std::cout << "Encrypted text: " << enc_text << std::endl;

    // Получаем возможные значения длины ключа по методу Казиски
    std::vector<int> probablyKeys = KaziskiMethod(enc_text);    
    
    // Получаем наиболее вероятные значения длины ключа по методу Фридмана
    std::vector<int> keyCandidates = FriedmanMethod(probablyKeys, enc_text);

    for (int keyLength : keyCandidates) {
        if (keyLength <= 1) continue;   // случай когда длина = 1 - нас не интересует

        // Расшифровка ключа
        std::string key = keyDecipher(keyLength, enc_text);
        
        // Расшифровка текста
        std::string dec_text = VisenereDecipher(enc_text, key);

        std::cout << "Length: " << keyLength << std::endl;
        std::cout << "Key: " << key << std::endl;
        std::cout << "Text: " << dec_text << std::endl;
    }

    


    /*
    // Проверяем полученные значения по методу Фридмана и сортируем по наиболее вероятным
    //int keyl = FriedmanMethod(probablyKeys, enc_text);   - если берём только 1 наиболее вероятный
    std::string key = keyDecipher(keyl, enc_text);
    std::string dec_text = VisenereDecipher(enc_text, key);
    std::cout << "Decrypted text: " << dec_text << std::endl;
    */


    return 0;
}