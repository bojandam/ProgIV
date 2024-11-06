#include <iostream>
#include <vector>

class String {
    char * str;
    unsigned int length;

public:
    String() { length = 0; str = new char[1]; str[0] = 0; }
    ~String() { if (str != nullptr) delete[] str; }
    String(String & o);
    String(const char * o);
    String operator=(const String & o);
    char & operator[](unsigned int i) { return str[i]; }
    char operator[] (unsigned int i)const { return str[i]; }
    String(const String & other);
    friend std::ostream & operator<<(std::ostream & out, const String & Str) { out << Str.str; }
    // Implement KMP on the whole string
    std::vector<int> findAllSubStr(const String & subStr);

    // Implement KMP until the first match
    int findFirstSubStr(const String & subStr);

    // Implement KMP in reverse (search from the end of both strings).
    // The lookup table should be done from last character
    int findLastSubStr(const String & subStr);

    std::vector<int> findAllSubStrReverse(const String & subStr);
};

String::String(String & o)
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
    if (str != nullptr) delete[] str;
    length = o.length;
    str = new char[length + 1];
    for (int i = 0; i <= length; i++) {
        str[i] = o.str[i];
    }
    return *this;
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

    while (i < length)
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




int main() {
    String string("abcababdabababaabacababaababaabac");
    String item("ababaaba");
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
}


