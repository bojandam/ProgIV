#pragma once
#include "Operations.h"


vector<std::pair<Number, int>> Number::factor() {
    vector<std::pair<Number, int>> rez;
    Number x = *this;
    for (Number i = 2; i * i < x + 1; i = i + 2) {
        int k = 0;
        while (((x % i) == 0))
        {
            k++; x = x / i;
        }
        if (k) { rez.push_back({ i, k }); }
        if (x == 1) { break; }
        if (i == 2) i = i - 1;
    }
    if (!(x == 0 || x == 1)) rez.push_back({ x  ,1 });
    return rez;
}