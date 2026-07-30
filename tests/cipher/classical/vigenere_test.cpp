// vigenere_test.cpp

#include <string>
#include <iostream>
#include <cassert>

#include <cryptolibrium/cipher/vigenere_cipher.hpp>

using cryptolibrium::cipher::VigenereCipher;

// Helper function to test valid keys
void expectValidKey(const std::string& key, const std::string& testCaseDescription) {
    try {
        VigenereCipher cipher(key);
        
        std::cout << "✓ " <<  testCaseDescription << " test passed." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "✗ " << testCaseDescription << " test failed: " << e.what() << std::endl;
        assert(false);  // Force a failure if an exception is thrown
    }
}

// Helper function to test invalid keys
void expectInvalidKey(const std::string& key, const std::string& testCaseDescription) {
    try {
        VigenereCipher cipher(key);

        std::cerr << "✗ " << testCaseDescription << " test failed." << std::endl;
        assert(false);  // Force a failure if no exception is thrown
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ " << testCaseDescription << " test passed: " << e.what() << std::endl;
    }
}

int main() {
    // Valid key
    expectValidKey("VIGENERE", "1.1 Valid key with uppercase letters");
    expectValidKey("vigenere", "1.2 Valid key with lowercase letters");
    expectValidKey("VigeNere", "1.3 Valid key with mixed case letters");
    expectValidKey("A", "1.4 Valid key with one letter");
    expectValidKey("AABBC", "1.5 Valid key with duplicated letters");
    expectValidKey("A B C", "1.6 Valid key with spaces");
    
    // Invalid keys
    expectInvalidKey("", "1.7 Empty key");
    expectInvalidKey("V1GENERE", "1.8 Key with digits");
    expectInvalidKey("VIGENERE!", "1.9 Key with punctuation");
    expectInvalidKey("@#$%^&*", "1.10 Key with only symbols");
    expectInvalidKey("12345", "1.11 Key with only digits");
    expectInvalidKey("ыуауйа", "1.12 Key with non-Latin characters");
    expectInvalidKey(" ", "1.13 Key with only whitespace");



    
    return 0;
}