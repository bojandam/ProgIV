#pragma once
#include "Number.h"


Number Number::operator+(const Number & other) const
{
    Number rez(0, std::max(number.size(), other.number.size()));
    if (!(this->sign ^ other.sign)) {
        bool carry = 0;
        for (int i = 0; i < std::max(number.size(), other.number.size()); i++) {
            int temp = (this->operator[])(i) + other[i] + carry;
            rez[i] = temp % 10;
            carry = temp / 10;
        }
        if (carry)rez.addDigit(1);
        rez.sign = this->sign;
        return rez;
    }
    else if (this->sign == NEG) {
        Number temp(this->sign);
        temp.sign = POS;
        return other - temp;
    }
    else {
        Number temp(other);
        temp.sign = POS;
        return *this - temp;
    }
}

Number Number::operator-(const Number & other) const
{
    if (this->sign ^ other.sign) {
        if (other.sign == NEG) {
            Number temp(other);
            temp.sign = POS;
            return *this + temp;
        }
        else {
            Number temp(other);
            temp.sign = NEG;
            return *this + temp;
        }
    }
    else {
        Number Left(*this), Right(other);
        Left.sign = POS;
        Right.sign = POS;
        if (Left < Right) {
            if (sign == NEG) {

                return (Right - Left);
            } //  -1 - -3 = -1 +3 = 3 - 1
            else
                return -(Right - Left); // 1 - 3 = - (3 - 1)
        }
        else {
            if (sign == NEG) {
                return -(Left - Right);                  //  -3 - -1 = -3 + 1 = - (3 -1)
            }
            // actuall algorithm

            Number rez(0, std::max(number.size(), other.number.size()));
            bool carry = 0;
            for (int i = 0; i < std::max(number.size(), other.number.size()); i++) {
                int temp = (this->operator[])(i) - other[i] - carry;
                if (temp < 0) {
                    temp += 10;
                    carry = 1;
                }
                else
                    carry = 0;
                rez[i] = temp;
            }
            return rez;
        }

    }

    return Number();
}


Number Number::SingleDigitMultiplication(int dig, int offset = 0) const
{
    int len = getLength();
    Number rez(0, std::max((int)number.size(), len + offset + 1));
    int carry = 0;
    int i;
    for (i = 0; i < len; i++) {
        int temp = number[i] * dig + carry;
        rez[i + offset] = temp % 10;
        carry = temp / 10;
    }
    rez[i + offset] = carry;
    return rez;
}

Number Number::operator*(const Number & other) const
{
    int otherLen = other.getLength();
    Number rez;
    for (int i = 0; i < otherLen; i++) {
        rez = rez + SingleDigitMultiplication(other[i], i);
    }
    rez.sign = ((sign ^ other.sign) ? NEG : POS);
    return rez;
}

Number Number::operator/(const Number & other)  // Pisuvajki go ova nauciv deka ne znam da delam 
{
    Number rez(0, number.size());
    std::stack<int> rezDigs;
    Number subtructee(*this);
    Number subtractor;
    Number withOne;
    int osLen = other.getLength();
    int firstDig = other[osLen - 1];
    int DigLen = subtructee.getLength();
    while (osLen + rezDigs.size() <= DigLen)
    {

        int L = 0, R = 9, M = 4;
        while (L <= R)
        {
            int DigMod = DigLen - rezDigs.size() - osLen;
            if (DigMod < 0)DigMod = 0;
            withOne = other.SingleDigitMultiplication(1, DigMod);
            subtractor = other.SingleDigitMultiplication(M, DigMod);
            Number tempRez(subtructee - subtractor);

            if (tempRez.sign == NEG) {
                R = M;
                M = (L + R) / 2;
            }
            else if (!(tempRez < withOne))
            {
                L = M + 1;
                M = (L + R) / 2;
            }
            else {
                subtructee = tempRez;
                L = R + 1; //break
            }
        }

        rezDigs.push(M);

    }
    for (int i = 0; !rezDigs.empty(); i++) {
        rez[i] = rezDigs.top();
        rezDigs.pop();
    }
    rez.sign = ((sign ^ other.sign) ? NEG : POS);

    moduloRez = vector<short>(subtructee.number);

    return rez;
}

Number Number::operator%(const Number & other)
{
    (this->operator/)(other);
    return Number(moduloRez);
}

