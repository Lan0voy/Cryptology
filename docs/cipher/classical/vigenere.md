# Vigenère Cipher

## Overview

The **Vigenère cipher** is a classical polyalphabetic substitution cipher invented in the 16th century. Unlike the Caesar cipher, which applies the same shift to every letter, the Vigenère cipher uses a sequence of shifts determined by a keyword. This makes it significantly more resistant to simple frequency analysis.

This implementation:

- Supports English alphabet letters (`A-Z`, `a-z`)
- Converts all letters to uppercase
- Preserves spaces, digits, and punctuation
- Ignores whitespace characters in the key
- Performs input validation before encryption or decryption

---

# Algorithm

## Encryption

Each plaintext letter is shifted according to the corresponding letter of the repeating keyword.

Example:

```text
Plaintext : ATTACK AT DAWN
Key       : LEMON
Key Stream: LEMONL EM ONLE
Ciphertext: LXFOPV EF RNHR
```

Encryption formula:

```text
C = (P + K) mod 26
```

Where:

- `P` = plaintext letter index (`A = 0`)
- `K` = key letter index (`A = 0`)
- `C` = ciphertext letter index

---

## Decryption

Each ciphertext letter is shifted backwards using the same keyword.

Example:

```text
Ciphertext: LXFOPV EF RNHR
Key       : LEMON
Plaintext : ATTACK AT DAWN
```

Decryption formula:

```text
P = (C - K + 26) mod 26
```

Adding `26` guarantees a non-negative result before applying the modulo operation.

---

# Key Requirements

The key:

- must not be empty;
- must contain at least one English alphabetic letter;
- may contain spaces, tabs, or newlines;
- must not contain digits or punctuation.

Examples:

| Key | Valid |
|------|:----:|
| `LEMON` | ✓ |
| `lemon` | ✓ |
| `LeMoN` | ✓ |
| `MY SECRET KEY` | ✓ |
| `KEY123` | ✗ |
| `KEY!` | ✗ |
| `12345` | ✗ |

---

# Key Normalization

Before encryption or decryption the key is normalized.

Normalization performs the following steps:

- validates the key;
- removes all whitespace characters;
- converts every letter to uppercase.

Example:

```text
Input key:
My Secret Key

Normalized:
MYSECRETKEY
```

---

# Plaintext Processing

Plaintext is **not modified** before encryption.

Letters:

- are converted to uppercase.

Non-letter characters remain unchanged:

- spaces;
- punctuation;
- digits.

These characters **do not consume key characters**.

Example:

```text
Plaintext:
Hello, World! 123

Key:
KEY

Ciphertext:
RIJVS, UYVJN! 123
```

---

# Ciphertext Processing

During decryption:

- alphabetic characters are decrypted;
- spaces, digits, and punctuation remain unchanged;
- the original formatting is preserved.

---

# Complexity

| Operation | Complexity |
|-----------|-----------:|
| Encryption | O(n) |
| Decryption | O(n) |
| Extra memory | O(n) |

where **n** is the length of the processed text.

---

# Example

```cpp
#include <iostream>

#include <cryptolibrium/cipher/vigenere_cipher.hpp>

using cryptolibrium::cipher::VigenereCipher;

int main() {
    VigenereCipher cipher("LEMON");

    std::string plaintext = "ATTACK AT DAWN";

    std::string ciphertext = cipher.encrypt(plaintext);
    std::string decrypted = cipher.decrypt(ciphertext);

    std::cout << "Plaintext : " << plaintext << '\n';
    std::cout << "Ciphertext: " << ciphertext << '\n';
    std::cout << "Decrypted : " << decrypted << '\n';

    return 0;
}
```

Output:

```text
Plaintext : ATTACK AT DAWN
Ciphertext: LXFOPV EF RNHR
Decrypted : ATTACK AT DAWN
```

---

# Notes

- Only English alphabet letters are encrypted.
- Letter case is normalized to uppercase.
- The key is repeated automatically as needed.
- Whitespace in the key is ignored.
- Spaces, digits, and punctuation are preserved in the output.
- Encryption and decryption are inverse operations:

```cpp
decrypt(encrypt(text)) == text
```
