#include <iostream>
#include <cstdint>
#include<vector>

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

    void Assign(int value);
    void Assign(const Number & other);
public:
    Number(int value = 0, int digits = 10) : number(digits) {
        Assign(value);
    }
    Number(const Number & other) : number(other.number) {
        Assign(other);
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
    Number operator+(const Number & other) const;
    Number operator+(int value) { Number other(value); this->operator+(other); }
    void print() {
        int i = number.size();
        for (; number[i] == 0; i--);
        for (; i >= 0; i--)
            std::cout << number[i];
    }
    void addDigit(short int dig = 0) {
        number.push_back(dig);
    }


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
        return rez;
    }
    return *this;
}

int main() {

    int a, b; std::cin >> a >> b;
    Number A(a), B(b); A.print(); std::cout << " "; B.print(); std::cout << " "; Number c(0, 3); c = A; c.print();
    c = A + B; std::cout << " "; c.print();

}