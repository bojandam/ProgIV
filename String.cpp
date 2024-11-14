#include <iostream>
#include <vector>
#include <cmath>



class String {
    char * str;
    unsigned int length;

public:
    String() { length = 0; str = new char[1]; str[0] = 0; }
    ~String() { if (str != nullptr) delete[] str; }
    String(const char * o);
    String(const String & o);
    String operator=(const String & o);
    char & operator[](unsigned int i) { return str[i]; }
    char operator[] (unsigned int i)const { return str[i]; }

    friend std::ostream & operator<<(std::ostream & out, const String & Str) { out << Str.str; return out; }


    std::vector<int> findAllSubStr(const String & subStr);
    int findFirstSubStr(const String & subStr);
    int findLastSubStr(const String & subStr);
    std::vector<int> findAllSubStrReverse(const String & subStr);

    std::vector<int> rollingHash(const String & subStr);
    unsigned int size() const { return length; }

    String substr(unsigned int len) {
        if (len >= length) return *this;
        char pom = str[len];
        str[len] = 0;
        String rez(str);
        str[len] = pom;
        return rez;
    }

};
String::String(const String & o)
{
    length = o.length;
    str = new char[length + 1];
    for (int i = 0; i <= length; i++) {
        str[i] = o.str[i];
    }
}
String::String(const char * o)
{
    for (length = 0; o[length] != 0; length++);
    str = new char[length + 1];
    for (int i = 0; i <= length; i++)
        str[i] = o[i];
}
String String::operator=(const String & o)
{
    if (this == &o) return *this;

    if (str != nullptr) delete[] str;
    length = o.length;
    str = new char[length + 1];
    for (int i = 0; i <= length; i++) {
        str[i] = o.str[i];
    }
    return *this;
}


int Hash1(String item) {

    int rez = 0;

    for (int i = 0; i < item.size(); i++) {
        rez += item[i] - 'a' + 1;
    }


    return rez;
}
int  Hash(String item) {

    const long long b = 26;
    const long long m = 1e9 + 9;
    unsigned long long p_pow = 1;
    unsigned long long rez = 0;

    for (int i = 0; i < item.size(); i++) {

        rez = (rez + (item[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * b) % m;
    }
    return rez;
}

void update_hash1(int & val, char old, char nov, int len) {

    val = val - old + nov;

}
void update_hash(int & val, char old, char nov, int len) {

    int m = 1e9 + 9;

    val = (val - (old - 'a' + 1)) % m;
    val /= 26;


    int pom = (nov - 'a' + 1);


    float pom1 = pow(26, len - 1);

    val += pom * pom1;

    val %= m;

}



std::vector<int> String::findAllSubStr(const String & subStr)
{
    std::vector<int> rez;
    //table geniration
    int i = 0, j = 1;
    int arr[subStr.length] = { 0 };
    while (j < subStr.length)
    {
        if (subStr[i] == subStr[j]) {

            arr[j] = i + 1;
            i++; j++;
        }
        else if (i == 0)
            j++;
        else
            i = ((arr[i] == 0) ? 0 : (arr[i] - 1));
    }

    //search              
    i = j = 0;

    while (i <= length)
    {
        if (j == subStr.length) {
            rez.push_back(i - j);
            //For every instance
            j = arr[j - 1];
        }
        if (str[i] == subStr[j]) {
            i++; j++;
        }
        else if (j == 0)
            i++;
        else
            j = arr[j - 1];
    }
    return rez;
}
int String::findFirstSubStr(const String & subStr)
{
    int rez;
    //table geniration
    int i = 0, j = 1;
    int arr[subStr.length] = { 0 };
    while (j < subStr.length)
    {
        if (subStr[i] == subStr[j]) {

            arr[j] = i + 1;
            i++; j++;
        }
        else if (i == 0)
            j++;
        else
            i = ((arr[i] == 0) ? 0 : (arr[i] - 1));
    }

    //search              
    i = j = 0;

    while (i < length)
    {
        if (j == subStr.length)
            return i - j;

        if (str[i] == subStr[j]) {
            i++; j++;
        }
        else if (j == 0)
            i++;
        else
            j = arr[j - 1];
    }
    return -1; //no solution found
}
std::vector<int> String::findAllSubStrReverse(const String & subStr)

{
    std::vector<int> rez;


    //table geniration
    int i = subStr.length - 1, j = subStr.length - 2;
    int arr[subStr.length] = { 0 };
    for (int k = 0; k <= i; k++)
        arr[k] = i;
    while (j >= 0)
    {
        if (subStr[i] == subStr[j]) {

            arr[j] = i - 1;
            i--; j--;
        }
        else if (i == subStr.length - 1)
            j--;

        else
            i = ((arr[i] == subStr.length - 1) ? subStr.length - 1 : (arr[i]));
    }

    //search              
    i = length - 1;
    j = subStr.length - 1;

    while (i >= 0)
    {
        if (j < 0) {
            rez.push_back(i + 1);
            //For every instance
            j = arr[j + 1];
        }
        if (str[i] == subStr[j]) {
            i--; j--;
        }
        else if (j == subStr.length - 1)
            i--;
        else
            j = arr[j + 1];
    }
    return rez;

}
int String::findLastSubStr(const String & subStr)

{

    //table geniration
    int i = subStr.length - 1, j = subStr.length - 2;
    int arr[subStr.length] = { 0 };
    for (int k = 0; k <= i; k++)
        arr[k] = i;
    while (j >= 0)
    {
        if (subStr[i] == subStr[j]) {

            arr[j] = i - 1;
            i--; j--;
        }
        else if (i == subStr.length - 1)
            j--;

        else
            i = ((arr[i] == subStr.length - 1) ? subStr.length - 1 : (arr[i]));
    }

    //search              
    i = length - 1;
    j = subStr.length - 1;

    while (i >= 0)
    {
        if (j < 0) {
            return i + 1;
            //For every instance
            j = arr[j + 1];
        }
        if (str[i] == subStr[j]) {
            i--; j--;
        }
        else if (j == subStr.length - 1)
            i--;
        else
            j = arr[j + 1];
    }
    return -1;

}

std::vector<int> String::rollingHash(const String & subStr)
{
    std::vector<int> rez;

    int subStr_val = Hash(subStr);
    int val = 0;



    for (int i = 0; i <= (int)length - (int)subStr.size(); i++) {
        if (i != 0) {
            update_hash(val, str[i - 1], str[i + subStr.size() - 1], subStr.size());
        }
        else {
            val = Hash(substr(subStr.size()));
        }


        if (val == subStr_val) {
            bool same = true;
            for (int j = 0; j < subStr.size(); j++) {
                if (subStr[j] != str[i + j]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                rez.push_back(i);

            }
        }
    }
    return rez;
}


int main() {
    String string("aabbaaabb");
    String item("bb");




    auto vec = string.findAllSubStr(item);
    for (auto el : vec) {
        std::cout << el << " ";
    }
    std::cout << std::endl << string.findFirstSubStr(item) << "\n";
    std::cout << string.findLastSubStr(item) << "\n";
    vec = string.findAllSubStrReverse(item);
    for (auto el : vec) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    vec = string.rollingHash(item);
    for (auto el : vec) {
        std::cout << el << " ";
    }

}


