// vigenere_cipher.cpp

#include <string>
#include <stdexcept>

#include <cryptolibrium/cipher/vigenere_cipher.hpp>

namespace cryptolibrium {

    cipher::VigenereCipher::VigenereCipher(const std::string &key) : key_(key) {
        validateKey(key_);
    }

    
    // Validating key for recomendations by Vigenere Cipher// vigenere_cipher.cpp

#include <string>
#include <stdexcept>

#include <cryptolibrium/cipher/vigenere_cipher.hpp>

namespace cryptolibrium {

    cipher::VigenereCipher::VigenereCipher(const std::string &key) : key_(key) {
        validateKey(key_);
    }

    
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
        std::string preparedKey;
        preparedKey.reserve(key.size());

        for (unsigned char c : key) {
            preparedKey += static_cast<unsigned char>(std::toupper(c));
        }

        return preparedKey;
    }

    
    std::string cipher::VigenereCipher::encrypt(const std::string& plaintext) const {
        std::size_t plaintextLength = plaintext.length();
        std::string keyStream;
        keyStream.reserve(plaintextLength);
        std::size_t keyIndex = 0;

        for(std::size_t i = 0; i < plaintextLength; ++i) {
            unsigned char c = plaintext[i];            
            const bool isLetter = (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')));

            if (isLetter) {
                keyStream[i] = key_[keyIndex];
                keyIndex = (keyIndex + 1) % key_.length();
            }
        }

        std::string encryptedText;

        return encryptedText;
    }


    std::string cipher::VigenereCipher::decrypt(const std::string& ciphertext) const {

    }
}
    static void validateKey(const std::string& key) {
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
    static std::string prepareKey(const std::string& key) {
        std::string preparedKey;
        preparedKey.reserve(key.size());

        for (unsigned char c : key) {
            preparedKey += static_cast<unsigned char>(std::toupper(c));
        }

        return preparedKey;
    }

    
    std::string encrypt(const std::string& plaintext) {
        std::size_t plaintextLength = plaintext.length();
        std::string keyStream;
        keyStream.reserve(plaintextLength);
        std::size_t keyIndex = 0;

        for(std::size_t i = 0; i < plaintextLength; ++i) {
            unsigned char c = plaintext[i];            
            const bool isLetter = (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')));

            if (isLetter) {
                keyStream[i] = key_[keyIndex];
                keyIndex = [keyIndex + 1] % key_.length();
            }
        }

        std::string encryptedText;

        return encryptedText;
    }


    std::string decrypt(const std::string& ciphertext) {

    }
}