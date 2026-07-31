// hill_cipher.hpp

// Include guard to prevent multiple inclusions of this header file
#pragma once

#include <string>

// Define the namespace for the cryptolibrium library and its cipher module
namespace cryptolibrium::cipher {

    // Define the HillCipher class for encrypting and decrypting text using the Hill Cipher technique
    class HillCipher {
        public:
        
            explicit HillCipher();

            [[nodiscard]]
            std::string encrypt(
                const std::string& plaintext
            ) const;

            [[nodiscard]]
            std::string decrypt(
                const std::string& ciphertext
            ) const;

        private:

    };
}