#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <utility>

/*
    This is the root file with the definition of the class Number
        * The operations (+ - * / %) are in "Operations.h"
        * The factorisation function is in "Factorisation.h"
    Here there are usefull side functinos:
        - Comparision operators
        - Assignment functions
        - Random number generator
*/

enum SIGN {
    POS = 0,
    NEG
};

using std::vector;


class Number
{
private:

    vector<short int>  number;
    SIGN sign;

    vector<short int> moduloRez;

    void Assign(int value);
    void Assign(const Number & other);
public:
    Number SingleDigitMultiplication(int dig, int offset) const;
    friend Number generateRandomNumber(int);
public:
    Number(int value = 0, int digits = 10) : number(digits) {
        Assign(value);
    }
    Number(const Number & other) : number(other.number) {
        Assign(other);
    }
    Number(vector<short> vec, SIGN sign = POS) {
        number = vec;
        this->sign = sign;
    }
    Number & operator=(Number other) {
        Assign(other);
        return *this;
    }
    Number & operator=(int value) {
        Assign(value);
        return *this;
    }
    short int & operator[](int i) {
        return number[i];
    }
    short int operator[](int i) const {
        if (i < number.size()) return number[i];
        return 0;
    }
    int getLength() const {
        int i = number.size() - 1;
        for (; number[i] == 0 && i >= 0; i--);
        return i + 1;
    }


    Number operator+(const Number & other) const;
    Number operator+(int value) { Number other(value); return this->operator+(other); }

    Number operator-(const Number & other) const;
    Number operator-(int value) { Number other(value); return this->operator-(other); }

    Number operator-() const {  //unaren minus -(3) = -3
        Number rez(*this);
        rez.sign = ((sign == POS) ? NEG : POS);
        return rez;
    }

    Number operator*(const Number & other) const;
    Number operator*(int value) { Number other(value); return this->operator*(other); }

    Number operator/(const Number & other);
    Number operator/(int value) { Number other(value); return this->operator/(other); }

    Number operator%(const Number & other);
    Number operator%(int value) { Number other(value); return this->operator%(other); }

    bool operator<(const Number & other) const;
    bool operator<(int value) { Number other(value); return this->operator<(other); }

    bool operator==(const Number & other) const;
    bool operator==(int value) { Number other(value); return this->operator==(other); }

    void print() const {
        if (sign == NEG) std::cout << "-";
        int i = number.size() - 1;
        for (; number[i] == 0 && i >= 0; i--);
        if (i < 0) {
            std::cout << "0";
            return;
        }
        for (; i >= 0; i--)
            std::cout << number[i];
    }

    void addDigit(short int dig = 0) {
        number.push_back(dig);
    }
    vector<std::pair<Number, int> > factor();

};







void Number::Assign(int value)
{
    if (value < 0) {
        sign = NEG;
        value *= -1;
    }
    else {
        sign = POS;
    }
    for (int i = 0; i < number.size() && value != 0; i++) {
        number[i] = value % 10;
        value /= 10;
    }

}

void Number::Assign(const Number & other)
{
    if (number.size() < other.number.size())
        number.resize(other.number.size(), 0);
    int i;
    for (i = 0; i < std::max(number.size(), other.number.size()); i++)
        number[i] = other[i];
    sign = other.sign;
}


bool Number::operator==(const Number & other) const
{
    if (this->sign != other.sign)
        return false;

    for (int i = std::max(number.size(), other.number.size()); i >= 0; i--)
        if ((this->operator[])(i) != other[i])
            return false;
    return true;
}


bool Sranded = false;
Number generateRandomNumber(int digs) {
    Number num(0, digs);
    if (!Sranded) {
        srand(time(0));
        Sranded = true;
    }

    for (int i = 0; i < digs; i++)
    {
        num[i] = rand() % 10;
    }

    return num;
}

bool Number::operator<(const Number & other) const
{
    if (sign == NEG && other.sign == POS) return true;
    else if (sign == POS && other.sign == NEG) return false;

    for (int i = std::max(number.size(), other.number.size()); i >= 0; i--)
        if ((this->operator[])(i) < other[i])
            if (sign == NEG)
                return false;
            else
                return true;
        else if ((this->operator[])(i) > other[i])
            if (sign == NEG)
                return true;
            else
                return false;

    if (sign == NEG)
        return true;
    else
        return false;
}