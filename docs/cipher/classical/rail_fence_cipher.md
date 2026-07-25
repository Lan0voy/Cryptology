# Rail Fence Cipher

## Overview

The **Rail Fence Cipher** is a classical transposition cipher that encrypts text by rearranging the positions of characters without modifying the characters themselves.

During encryption, the plaintext is written in a zigzag pattern across a specified number of rails. The ciphertext is then produced by reading each rail from top to bottom.

Unlike substitution ciphers, the Rail Fence Cipher preserves every character exactly as it appears in the original message, including uppercase letters, lowercase letters, digits, spaces, and punctuation.

---

## Encryption

### Algorithm

1. Choose the number of rails.
2. Write the plaintext in a zigzag pattern across the rails.
3. Change direction whenever the top or bottom rail is reached.
4. Read the rails sequentially from top to bottom.
5. Concatenate all rails to obtain the ciphertext.

### Example

**Plaintext**

```text
WEAREDISCOVEREDFLEEATONCE
```

**Rails**

```text
W . . . E . . . C . . . R . . . L . . . T . . . E
. E . R . D . S . O . E . E . E . A . O . C . I . D
. . A . . . I . . . V . . . D . . . F . . . N . .
```

**Ciphertext**

```text
WECRLTEERDSOEEFEAOCAIVDEN
```

---

## Decryption

### Algorithm

1. Reconstruct the zigzag traversal pattern.
2. Count how many characters belong to each rail.
3. Split the ciphertext into individual rails.
4. Traverse the zigzag pattern again.
5. Read the next character from the corresponding rail until the plaintext is reconstructed.

---

## Complexity

| Operation | Time | Memory |
|-----------|------|--------|
| Encryption | O(n) | O(n) |
| Decryption | O(n) | O(n) |

where **n** is the length of the input text.

---

## Example Usage

```cpp
#include <cryptolibrium/cipher/rail_fence_cipher.hpp>

using cryptolibrium::cipher::RailFenceCipher;

RailFenceCipher cipher(3);

std::string plaintext = "HELLOWORLD";

std::string ciphertext = cipher.encrypt(plaintext);
// HOLELWRDLO

std::string decrypted = cipher.decrypt(ciphertext);
// HELLOWORLD
```

---

## Input Requirements

- The number of rails must be greater than or equal to **2**.
- The plaintext and ciphertext may contain any characters.
- Character case is preserved.
- Spaces, digits, and punctuation are preserved.
- Empty strings are supported.

---

## Notes

- The Rail Fence Cipher is a **transposition cipher**, not a substitution cipher.
- Encryption changes only the order of characters.
- The algorithm is intended for educational purposes and historical interest.
- It does **not** provide security for modern applications.

---

## References

1. David Kahn, *The Codebreakers*
2. Simon Singh, *The Code Book*
3. Helen Fouché Gaines, *Cryptanalysis*
4. Wikipedia contributors, *Rail Fence Cipher*
