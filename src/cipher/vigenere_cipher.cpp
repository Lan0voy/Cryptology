// vigenere_cipher.cpp

#include <string>
#include <stdexcept>
#include <cctype>

#include <cryptolibrium/cipher/vigenere_cipher.hpp>

namespace cryptolibrium {

    cipher::VigenereCipher::VigenereCipher(const std::string &key) : key_(prepareKey(key)) { }

    
    // Validating key for recomendations by Vigenere Cipher
    void cipher::VigenereCipher::validateKey(const std::string& key) {
        // Check if the key is empty and throw an exception if it is
        if (key.empty()) {
            throw std::invalid_argument("Key cannot be empty.");
        }

        int letterCounter = 0;

        // Check if the characters are alphabetic or a whitespace character (space, tab, newline)
        for (char symbol : key) {
            const bool isUpper = symbol >= 'A' && symbol <= 'Z';
            const bool isLower = symbol >= 'a' && symbol <= 'z';
            const bool isWhitespace = symbol == ' ' || symbol == '\t' || symbol == '\n';

            if (!isUpper && !isLower && !isWhitespace) {
                throw std::invalid_argument("Key must contain only English alphabetic characters and whitespaces.");
            }

            if (isUpper || isLower) {
                ++letterCounter;
            }
        }

        // Check if the key contains at least one letter and throw an exception if it does not
        if (letterCounter == 0) {
            throw std::invalid_argument("Key must contain at least one letter.");
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
        constexpr std::size_t engAlphabetSize = 26;
        constexpr char engAlphabetBase = 'A';

        std::size_t plaintextLength = plaintext.size();
        std::size_t keyIndex = 0;
        std::string encryptedText;
        char keyChar;

        for(std::size_t i = 0; i < plaintextLength; ++i) {
            unsigned char c = plaintext[i];            
            const bool isLetter = (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')));

            if (isLetter) {
                keyChar = key_[keyIndex];
                keyIndex = (keyIndex + 1) % key_.size();

                c = std::toupper(c);
                c = engAlphabetBase + (c - engAlphabetBase + keyChar - engAlphabetBase) % engAlphabetSize;                
            }

            encryptedText += c;
        }

        return encryptedText;
    }


    std::string cipher::VigenereCipher::decrypt(const std::string& ciphertext) const {
        constexpr std::size_t engAlphabetSize = 26;
        constexpr char engAlphabetBase = 'A';

        std::size_t ciphertextLength = ciphertext.size();
        std::size_t keyIndex = 0;
        std::string decryptedText;
        char keyChar;

        for (std::size_t i = 0; i < ciphertextLength; ++i) {
            unsigned char c = ciphertext[i];
            const bool isLetter = (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')));

            if (isLetter) {
                keyChar = key_[keyIndex];
                keyIndex = (keyIndex + 1) % key_.size();

                c = std::toupper(c);
                c = engAlphabetBase +   
                    (c - engAlphabetBase    
                     - (keyChar - engAlphabetBase)  
                     + engAlphabetSize) % engAlphabetSize;             
            }

            decryptedText += c;
        }

        return decryptedText;
    }
}    