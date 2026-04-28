#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

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

//-- Encrypting text function --//
std::string CaesarCipher(std::string str, int key) {
	std::string s = str;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] != ' ') {
			int number = (letterKeySearch(str[i]) + key) % alphabetSize;
			s[i] = alphabet[number];
		}
	}
	std::cout << "Encrypted text: " << s << std::endl;

	return s;
}

//-- Decrypting text function --//
std::string CaesarDecipher(std::string str, int key) {
	std::string s = str;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] != ' ') {
			int number = (letterKeySearch(str[i]) - key + alphabetSize) % alphabetSize;
			s[i] = alphabet[number];
		}
	}
	std::cout << "Decrypted text: " << s << std::endl;

	return s;
}

//-- Main --//
int main()
{
	const int key = 5;
	std::string text = "RAINBOW";
	std::cout << "Text: " << text << std::endl;

	std::string textCipher = CaesarCipher(text, key);
	CaesarDecipher(textCipher, key);

	return 0;
}