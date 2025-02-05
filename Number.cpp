#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <utility>

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
    Number(vector<short> vec,SIGN sign = POS){
        number=vec;
        this->sign=sign;
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

    Number operator/(const Number & other)  ;
    Number operator/(int value) { Number other(value); return this->operator/(other); }

    Number operator%(const Number & other)  ;
    Number operator%(int value) {Number other(value); return this->operator%(other); }

    bool operator<(const Number & other) const;
    bool operator<(int value) {Number other(value); return this->operator<(other); }

    bool operator==(const Number & other) const;
    bool operator==(int value) {Number other(value); return this->operator==(other); }

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
    vector<std::pair<Number, int> > factor(){
        vector<std::pair<Number, int>> rez;
        Number x = *this;
        for (Number i = 2; i * i < x + 1 ; i = i+2) {
            int k = 0;
            while (!((x % i) == 0))
            {
                k++; x = x / i;
            }
            if (k) { rez.push_back({ i, k }); }
            if (x == 1) { break; }
            if (i == 2) i= i-1;
        }
        if (!(x==0 || x==1)) rez.push_back({ x  ,1 });
        return rez;
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

Number Number::operator*(const Number & other) const
{
    int otherLen = other.getLength();
    Number rez;
    for (int i = 0; i < otherLen; i++) {
        rez = rez + SingleDigitMultiplication(other[i], i);
    }
    rez.sign = ((sign^other.sign)?NEG:POS);
    return rez;
}

Number Number::operator/(const Number & other)  // Pisuvajki go ova nauciv deka ne znam da delam 
{
    Number rez(0,number.size());
    std::stack<int> rezDigs;
    Number subtructee(*this);
    Number subtractor;
    Number withOne;
    int osLen=other.getLength();
    int firstDig = other[osLen-1];
    int DigLen=subtructee.getLength();
    while (osLen+rezDigs.size()<=DigLen)
    {

        int L=0,R=9,M=4;
        while (L<=R)
        {
            int DigMod=DigLen-rezDigs.size()-osLen;
            if(DigMod<0)DigMod=0;
            withOne=other.SingleDigitMultiplication(1, DigMod);
            subtractor = other.SingleDigitMultiplication(M, DigMod);
            Number tempRez(subtructee-subtractor); 

            if(tempRez.sign==NEG){
                R=M;
                M= (L+R)/2;
            }
            else if(!(tempRez<withOne))
            {
                L=M+1;
                M=(L+R)/2;
            }
            else{
                subtructee = tempRez;
                L=R+1; //break
            }
        }
         
        rezDigs.push(M);
        
    }
    for(int i=0; !rezDigs.empty();i++){
        rez[i]=rezDigs.top();
        rezDigs.pop();
    }
    rez.sign = ((sign^other.sign)?NEG:POS);
    
    moduloRez = vector<short>(subtructee.number);

    return rez;
}

Number Number::operator%(const Number & other) 
{
    (this->operator/)(other);
    return Number(moduloRez);
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

bool Number::operator==(const Number & other) const
{
    if(this->sign != other.sign)
        return false;
    
    for (int i = std::max(number.size(), other.number.size()); i >= 0; i--)
        if ((this->operator[])(i) != other[i])
            return false;
    return true;
}

bool Sranded = false;
Number generateRandomNumber(int digs){
    Number num(0,digs);
    if(!Sranded){
        srand(time(0));
        Sranded =true;
    }

    for(int i=0;i<digs;i++)
    {
        num[i] = rand()%10;   
    }
    
    return num;
}


int main() {


   
    int a, b;
    // Number A(generateRandomNumber(50)); 
    // Number B(generateRandomNumber(50));
    // // while (std::cin >> a >> b)
    // // {

    // //     Number A(a), B(b);
    // A.print(); std::cout << " "; B.print(); std::cout << "\n"; 
    // (A + B).print(); std::cout<< "\n";
    // (A - B).print(); std::cout<< "\n";
    // (A * B).print(); std::cout<< "\n";
    // (A / B).print(); std::cout<< "\n";
    // (A % B).print(); std::cout<< "\n";
    // }

    while (std::cin>>a)
    {   
        Number A(a);
        auto f = A.factor();
        for (auto el : f) {
             el.first.print(); std::cout<< "^" << el.second << ", ";
        }
        std::cout << std::endl;
    }
    



}  