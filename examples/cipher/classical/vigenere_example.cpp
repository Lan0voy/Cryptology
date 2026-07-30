// vigenere_example.cpp

#include <iostream>

#include <cryptolibrium/cipher/vigenere_cipher.hpp>

using cryptolibrium::cipher::VigenereCipher;

int main() {
    const std::string plaintext = "ATTACK AT DAWN";
    const std::string key = "LEMON";

    VigenereCipher cipher(key);

    const std::string ciphertext = cipher.encrypt(plaintext);
    const std::string decryptedText = cipher.decrypt(ciphertext);

    std::cout << "Plaintext : " << plaintext << '\n';
    std::cout << "Key       : " << key << '\n';
    std::cout << "Ciphertext: " << ciphertext << '\n';
    std::cout << "Decrypted : " << decryptedText << '\n';

    return 0;
}