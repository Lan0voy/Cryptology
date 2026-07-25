# Cryptology-Librarium

> A modern C++ library for classical cryptography, modern cryptographic algorithms, and cryptanalysis.

![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.20+-green.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)
![Status](https://img.shields.io/badge/Status-Active%20Development-orange)

---

## Overview

**Cryptology-Librarium** is an open-source C++ library that provides implementations of classical ciphers, modern cryptographic algorithms, cryptanalysis techniques, and educational examples.

The project is designed with two primary goals:

- provide clean, reusable implementations of cryptographic algorithms;
- serve as an educational resource for learning cryptography and modern C++.

Every algorithm is accompanied by documentation, examples, and unit tests.

---

# Features

## Classical Ciphers

### Implemented

- Caesar Cipher
- Playfair Cipher
- Rail Fence Cipher

### Planned

- Vigenère Cipher
- Affine Cipher
- Hill Cipher

---

## Symmetric Cryptography

Planned:

- AES
- DES
- Triple DES
- Blowfish
- Twofish
- Serpent
- ChaCha20

---

## Asymmetric Cryptography

Planned:

- RSA
- ElGamal
- ECC
- Diffie-Hellman

---

## Hash Algorithms

Planned:

- MD5
- SHA-1
- SHA-2
- SHA-3
- BLAKE2

---

## Cryptanalysis

Planned:

- Frequency Analysis
- Index of Coincidence
- Kasiski Examination
- Chi-Squared Analysis
- Dictionary Attacks
- Brute Force
- N-gram Analysis

---

# Project Structure

```text
Cryptology-Librarium
│
├── include/
│   └── cryptolibrium/
│       ├── cipher/
│       ├── hash/
│       ├── analysis/
│       └── utils/
│
├── src/
│   ├── cipher/
│   ├── hash/
│   ├── analysis/
│   └── utils/
│
├── docs/
│
├── examples/
│
├── tests/
│
├── benchmarks/
│
├── CMakeLists.txt
│
├── LICENSE
│
└── README.md
```

---

# Requirements

- C++20 compatible compiler
- CMake 3.20 or newer

Supported compilers include:

- GCC
- Clang
- MSVC

---

# Installation

Clone the repository:

```bash
git clone https://github.com/Lan0voy/Cryptology-Librarium.git

cd Cryptology-Librarium
```

Build the project:

```bash
mkdir build

cd build

cmake ..

cmake --build .
```

---

# Quick Start

```cpp
#include <iostream>

#include <cryptolibrium/cipher/caesar_cipher.hpp>

using cryptolibrium::cipher::CaesarCipher;

int main()
{
    CaesarCipher cipher(3);

    std::string plaintext = "HELLO";

    std::string ciphertext = cipher.encrypt(plaintext);

    std::string decrypted = cipher.decrypt(ciphertext);

    std::cout << "Plaintext : " << plaintext << '\n';
    std::cout << "Ciphertext: " << ciphertext << '\n';
    std::cout << "Decrypted : " << decrypted << '\n';
}
```

Output

```text
Plaintext : HELLO
Ciphertext: KHOOR
Decrypted : HELLO
```

---

# Documentation

Each implemented algorithm includes:

- theoretical background;
- algorithm description;
- complexity analysis;
- usage examples;
- implementation notes.

Documentation can be found in the `docs/` directory.

---

# Examples

Ready-to-run examples are available in the `examples/` directory.

Each example demonstrates:

- object construction;
- encryption;
- decryption;
- expected output.

---

# Testing

Every implemented algorithm is accompanied by unit tests covering:

- valid input;
- invalid input;
- edge cases;
- classical reference examples;
- encryption;
- decryption;
- round-trip verification.

Run all tests after building:

```bash
ctest
```

or execute individual test binaries from the `build/` directory.

---

# Design Goals

The project follows several principles:

- clean and readable C++20 code;
- consistent project architecture;
- reusable interfaces;
- comprehensive documentation;
- high test coverage;
- educational value.

---


# License

This project is licensed under the MIT License.

See the `LICENSE` file for details.
