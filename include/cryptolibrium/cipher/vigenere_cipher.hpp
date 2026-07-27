// visenere_cipher.hpp

// Include guard to prevent multiple inclusions of this header file
#pragma once

// Include necessary standard library headers
#include <string>
#include <cstddef>

// Define the namespace for the cryptolibrium library and its cipher module
namespace cryptolibrium::cipher {

    // Define the VigenereCipher class for encrypting and decrypting text using the Visenere cipher technique
    class VigenereCipher {
        public:

            // Create Vigenere cipher with specified key
            explicit VigenereCipher(const std::string& key);
        
            // Encrypt the input text using the Vigenere cipher
            [[nodiscard]]
            std::string encrypt(
                const std::string& plaintext
            ) const;
            
            // Decrypt the input text using the Vigenere cipher
            [[nodiscard]]
            std::string decrypt(
                const std::string& ciphertext
            ) const;

        private:
            
            // Keyword used to generate the Vigenere key string.
            const std::string key_;

            // Validate the key to ensure it meets the requirements for the Vigenere Cipher
            static void validateKey(const std::string& key);

            // Prepare key by removing spaces and converting to uppercase
            static std::string prepareKey(const std::string& key);
    }
}