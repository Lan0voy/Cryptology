// modular_arithmetic.hpp

#pragma once

namespace cryptolibrium::math {    
    static constexpr int AlphabetSize = 26;

    int gcd(int a, int b);

    int mod(int value, int modulus);
}