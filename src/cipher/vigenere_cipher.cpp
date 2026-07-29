// vigenere_cipher.cpp

#include <string>
#include <stdexcept>
#include <cctype>

#include <cryptolibrium/cipher/vigenere_cipher.hpp>

namespace cryptolibrium {

    cipher::VigenereCipher::VigenereCipher(const std::string &key) : key_(prepareKey(key)) { }

    
    // Validating key for recomendations by Vigenere Cipher
    void cipher::VigenereCipher::validateKey(const std::string& key) {
        if (key.empty()) {
            throw std::invalid_argument("Key cannot be empty");
        }   

        for (unsigned char c : key) {
            const bool isUpperCase = (c >= 'A' && c <= 'Z');
            const bool isLowerCase = (c >= 'a' && c <= 'z');

            if (!isUpperCase && !isLowerCase) {
                throw std::invalid_argument("Key must contain only English alphabet letters");
            }
        }
    }

    
    // Normalize key value for Vigenere Cipher
     std::string cipher::VigenereCipher::prepareKey(const std::string& key) {
        validateKey(key);

        std::string preparedKey;
        preparedKey.reserve(key.size());

        for (unsigned char c : key) {
            preparedKey += static_cast<char>(std::toupper(c));
        }

        return preparedKey;
    }

    
    std::string cipher::VigenereCipher::encrypt(const std::string& plaintext) const {
        std::size_t plaintextLength = plaintext.length();
        std::size_t keyIndex = 0;
        std::size_t engAlphabetSize = 26;

        std::string encryptedText;

        char engAlphabetBase = 'A';
        char keyChar;
        char plain;

        for(std::size_t i = 0; i < plaintextLength; ++i) {
            unsigned char c = plaintext[i];            
            const bool isLetter = (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')));

            if (isLetter) {
                keyChar = key_[keyIndex];
                keyIndex = (keyIndex + 1) % key_.length();

                plain = std::toupper(c);

                char encrypted = engAlphabetBase + (plain - engAlphabetBase + keyChar - engAlphabetBase) % engAlphabetSize;
            }
        }




        return encryptedText;
    }


    std::string cipher::VigenereCipher::decrypt(const std::string& ciphertext) const {

    }
}    