#pragma once
#include "Operations.h"
#include<random>



Number expmod(Number a, Number d, Number n) {
    Number rez = 1;
    Number one = 1;
    for (Number i = 0; i < d; i = i + 1) {
        rez = (rez * a) % n;
    }
    return rez;
}

bool MillerRabin(Number n, int k = 4) {
    if (n == 2 || n == 3) return true;
    if (n == 1 || n == 4 || n % 2 == 0) return false;

    int s = 0;  // n - 1 = d * 2^s
    Number d;

    Number pom = n - 1;
    while (pom % 2 == 0)
    {
        /* code */
        pom = pom / 2;
        s++;
    }
    d = pom;



    for (int i = 0; i < k; i++) {

        Number a = generateRandomNumber(n.getLength() + 5) % (n - 4) + 2;
        Number x = expmod(a, d, n);
        Number y;
        for (int j = 0; j < s; j++) {
            y = (x * x) % n;
            if (y == 1 && !(x == 1) && !(x == n - 1))
                return false;
            x = y;
        }
        if (!(y == 1))
            return false;
    }
    return true;
}

