#include <cassert>
#include <iostream>

#include <cryptolibrium/cipher/rail_fence_cipher.hpp>

using cryptolibrium::cipher::RailFenceCipher;

int main() {
    // Create Rail Fence Cipher with 3 rails
    RailFenceCipher cipher(3);

    // Original plaintext
    const std::string plaintext = "WEAREDISCOVEREDFLEEATONCE";

    // Encrypt plaintext
    const std::string ciphertext = cipher.encrypt(plaintext);

    // Print results
    std::cout << "Plaintext : " << plaintext << '\n';
    std::cout << "Ciphertext: " << ciphertext << '\n';

    // Verify encryption
    assert(ciphertext == "WECRLTEERDSOEEFEAOCAIVDEN");

    // Decrypt ciphertext
    const std::string decryptedText = cipher.decrypt(ciphertext);

    // Print decrypted text
    std::cout << "Decrypted : " << decryptedText << '\n';

    // Verify decryption
    assert(decryptedText == plaintext);

    std::cout << "\nRail Fence Cipher example completed successfully.\n";

    return 0;
}