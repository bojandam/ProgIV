#include <iostream>
#include <cstdint>

enum SIGN {
    POS = 0,
    NEG
};

class Number
{
private:
    uint8_t * number;
    SIGN sign;
    int length;

    void Assign(int value);
    void Assign(Number & other);
public:
    Number(int value = 0, int digits = 10) {
        length = digits;
        number = new uint8_t[digits];
        Assign(value);
    }
    Number(Number & other) {
        number = new uint8_t[other.length];
        Assign(other);
    }
    ~Number() { if (number != nullptr)delete[] number; }
    Number & operator=(Number & other) {
        Assign(other);
        return *this;
    }
    Number & operator=(int value) {
        Assign(value);
        return *this;
    }
    Number operator+(Number & other);
    Number operator+(int value) { Number other(value); this->operator+(other); }


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
    for (int i = 0; i < length && value != 0; i++) {
        number[i] = value % 10;
        value /= 10;
    }

}

void Number::Assign(Number & other)
{
    int i;
    for (i = 0; i < std::min(length, other.length); i++)
        number[i] = other.number[i];
    for (; i < length; i++)
        number[i] = 0;
    sign = other.sign;
}

Number Number::operator+(Number & other)
{
    if (!(this->sign ^ other.sign)) {

    }
    return *this;
}

