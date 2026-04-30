#include <iostream>
#include <string>
#include <unordered_map>
#include <windows.h>

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


// Frequency of every letter in English language texts
std::unordered_map<char, double> frequencyEngAlphabet = {
	{'A', 0.082}, {'B', 0.015}, {'C', 0.028}, {'D', 0.043}, {'E', 0.127},
	{'F', 0.022}, {'G', 0.020}, {'H', 0.061}, {'I', 0.070}, {'J', 0.002},
	{'K', 0.008}, {'L', 0.040}, {'M', 0.024}, {'N', 0.067}, {'O', 0.001},
	{'P', 0.019}, {'Q', 0.001}, {'R', 0.006}, {'S', 0.063}, {'T', 0.091},
	{'U', 0.028}, {'V', 0.010}, {'W', 0.023}, {'X', 0.001}, {'Y', 0.020},
	{'Z', 0.001},
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


// Поиск буквы с максимальной частотой в unordered_map
static char maxUnMap(std::unordered_map<char, double> map){
	char maxLetter = ' ';
	double maxValue = -1;

	for (const auto& pair : map) {
		if (pair.second > maxValue) {
			maxValue = pair.second;
			maxLetter = pair.first;
		}
	}

	return maxLetter;
}


//-- Caesar Decrypting text function --//
std::string CaesarDecipher(std::string str, int key) {
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


// Функция считает наиболее встречаемую букву в зашифрованном сообщении и англ алфавите,
// затем высчитывает предполагаемый ключ шифра Цезаря и расшифровывает по нему сообщение
static std::string FrequencyAnalysisCaesarCipher(std::string str) {
	std::string result;

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

	int strSize = str.length();

	// Считаем частоту появлений букв в зашифрованном тексте
	for (char c : str) {
		if (c >= 'A' && c <= 'Z') {
			frequencyEncryptedText[c]++;
		}
	}

	// Вывод полученного
	int k = 0;
	for (char c = 'A'; c <= 'Z'; ++c) {
		k++;
		std::cout << c << ": " << frequencyEncryptedText[c] << "   ";
		if (k == 7) {
			std::cout << std::endl;
			k = 0;
		}
	}
	std::cout << std::endl;
	
	// Находим самую популярную букву в тексте и в алфавите
	char maxEnc = maxUnMap(frequencyEncryptedText);
	char maxAlphabet = maxUnMap(frequencyEngAlphabet);

	// Находим индексы самых часто встречаемых букв
	int maxEncIndex = letterKeySearch(maxEnc);
	int maxAlphabetIndex = letterKeySearch(maxAlphabet);
	std::cout << "Индекс наиболее встречаемой буквы в " << std::endl << "Зашифрованном сообщении: " << maxEncIndex << "    Англ алфавите: " << maxAlphabetIndex << std::endl;

	// Высчитываем предполагаемый ключ шифра Цезаря
	int CaesarKey = (maxEncIndex + alphabetSize - maxAlphabetIndex) % alphabetSize;
	std::cout << "Высчитанный предполагаемый ключ шифра Цезаря: " << CaesarKey << std::endl;

	// Расшифровываем текст по высчитанному ключу
	result = CaesarDecipher(str, CaesarKey);

	return result;
}


int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::string enc_text = "OIITCSYVJEGIXSXLIWYRWLMRIERHCSYGERRSXWIIEWLEHS";
	std::cout << "Encrypted text: " << enc_text << std::endl;

	std::string dec_text = FrequencyAnalysisCaesarCipher(enc_text);
	std::cout << "Decrypted text: " << dec_text << std::endl;

	return 0;
}