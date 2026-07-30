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

// Helper function to test Vigenere Cipher encrypt
void expectEncrypt(const std::string& key, const std::string& plaintext, const std::string& ciphertext, const std::string& testCaseDescription) {
    VigenereCipher cipher(key);

    if (cipher.encrypt(plaintext) == ciphertext) {
       std::cout << "✓ " <<  testCaseDescription << " test passed." << std::endl;
    } else {
        std::cerr << "✗ " << testCaseDescription << " test failed." << std::endl;
        assert(false);
    }
}

// Help function to test Vigenere Cipher decrypt
void expectDecrypt(const std::string& key, const std::string& ciphertext, const std::string& plaintext, const std::string& testCaseDescription) {
    VigenereCipher cipher(key);

    if (cipher.decrypt(ciphertext) == plaintext) {
       std::cout << "✓ " <<  testCaseDescription << " test passed." << std::endl;        
    } else {
        std::cerr << "✗ " << testCaseDescription << " test failed." << std::endl;
        std::cerr << "Expected: " << plaintext << std::endl;
        std::cerr << "Actual:   " << cipher.decrypt(ciphertext) << std::endl;
        assert(false);
    }
}

// Help function to round-trip test Vigenere Cipher
void expectRoundTrip(
    const std::string& key,
    const std::string& text,
    const std::string& testCaseDescription) 
{
    VigenereCipher cipher(key);

    if (cipher.decrypt(cipher.encrypt(text)) == text) {
        std::cout << "✓ " << testCaseDescription << " test passed." << std::endl;
    } else {
        std::cerr << "✗ " << testCaseDescription << " test failed." << std::endl;
        assert(false);        
    }
}


int main() {

    // =========================
    // 1. Key Validation Tests
    // =========================

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

    // =========================
    // 2. Encryption Tests
    // =========================

    // 2.1 Empty plaintext
    expectEncrypt(
        "KEY",
        "",
        "",
        "2.1 Empty plaintext"
    );

    // 2.2 Single character
    expectEncrypt(
        "KEY",
        "A",
        "K",
        "2.2 Single character"
    );

    // 2.3 Classic Vigenere example
    expectEncrypt(
        "LEMON",
        "ATTACKATDAWN",
        "LXFOPVEFRNHR",
        "2.3 Classic example"
    );

    // 2.4 Lowercase plaintext
    expectEncrypt(
        "KEY",
        "hello",
        "RIJVS",
        "2.4 Lowercase plaintext"
    );

    // 2.5 Mixed case plaintext
    expectEncrypt(
        "KEY",
        "HeLlO",
        "RIJVS",
        "2.5 Mixed case plaintext"
    );

    // 2.6 Spaces
    expectEncrypt(
        "KEY",
        "HELLO WORLD",
        "RIJVS UYVJN",
        "2.6 Spaces"
    );

    // 2.7 Punctuation
    expectEncrypt(
        "KEY",
        "HELLO, WORLD!",
        "RIJVS, UYVJN!",
        "2.7 Punctuation"
    );

    // 2.8 Digits
    expectEncrypt(
        "KEY",
        "ABC123XYZ",
        "KFA123HCX",
        "2.8 Digits"
    );

    // 2.9 Alphabet
    expectEncrypt(
        "ABC",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "ACEDFHGIKJLNMOQPRTSUWVXZYA",
        "2.9 Alphabet"
    );

    // 2.10 Repeated letters
    expectEncrypt(
        "AAA",
        "AAAAAAAAAA",
        "AAAAAAAAAA",
        "2.10 Zero shift"
    );

    // 2.11 Key with spaces
    expectEncrypt(
        "A B C",
        "HELLO",
        "HFNLP",
        "2.11 Key with spaces"
    );

    // =========================
    // 3. Decryption Tests
    // =========================

    expectDecrypt(
    "LEMON",
    "LXFOPVEFRNHR",
    "ATTACKATDAWN",
    "3.1 Classic example"
    );

    expectDecrypt(
        "KEY",
        "RIJVS UYVJN",
        "HELLO WORLD",
        "3.2 Spaces"
    );

    expectDecrypt(
        "KEY",
        "RIJVS, UYVJN!",
        "HELLO, WORLD!",
        "3.3 Punctuation"
    );

    expectDecrypt(
        "KEY",
        "KFA123HCX",
        "ABC123XYZ",
        "3.4 Digits"
    );



    // =========================
    // 4. Round-trip Tests
    // =========================

    expectRoundTrip(
    "KEY",
    "HELLO WORLD",
    "4.1 Round-trip"
    );

    expectRoundTrip(
        "LEMON",
        "ATTACK AT DAWN!",
        "4.2 Classic round-trip"
    );

    expectRoundTrip(
        "ABC",
        "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG",
        "4.3 Long sentence"
    );

    expectRoundTrip(
        "CRYPTOGRAPHY",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "4.4 Alphabet"
    );

    
    return 0;
}