#include <iostream>
#include <stack>
using namespace std;

 

#ifndef MKD
    const unsigned int AlphabetSize = 26; //eng: 26      mkd: 31
    typedef char Char;                    //eng: char    mkd: wchar_t
    typedef string String;                //eng: string  mkd: wstring
    typedef ostream Ostream;              //eng: ostream mkd: wofstream
    #define Cout cout                     //eng: cout    mkd: wcout
    char IndexToLetter(int i){            
        return ((char)(i + 'a'));
    }
    int LetterToIndex(char c){
        return c-'a';
    }
    String TransformString(String word){return word;} // nishto ne pravi
#endif
#ifdef MKD
    const unsigned int AlphabetSize = 31; //eng: 26     mkd: 31
    typedef wchar_t Char;                    //eng: char   mkd:
    typedef wstring String;
    typedef wostream Ostream;
    #define Cout wcout
    String IndexToLetter(int i){
        const wstring str [31]={L"\u00d0\u00b0", L"\u00d0\u00b1", L"\u00d0\u00b2", L"\u00d0\u00b3", L"\u00d0\u00b4", L"\u00d1\u0093", L"\u00d0\u00b5", L"\u00d0\u00b6", L"\u00d0\u00b7", L"\u00d1\u0095", L"\u00d0\u00b8", L"\u00d1\u0098", L"\u00d0\u00ba", L"\u00d0\u00bb", L"\u00d1\u0099", L"\u00d0\u00bc", L"\u00d0\u00bd", L"\u00d1\u009a", L"\u00d0\u00be", L"\u00d0\u00bf", L"\u00d1\u0080", L"\u00d1\u0081", L"\u00d1\u0082", L"\u00d1\u009c", L"\u00d1\u0083", L"\u00d1\u0084", L"\u00d1\u0085", L"\u00d1\u0086", L"\u00d1\u0087", L"\u00d1\u009f", L"\u00d1\u0088"};
        return str[i];  // str[0]=a, [1]=b [3]=v ... [30]=sh
    }
    
    int LetterToIndex(wchar_t second_half) { //Sekoja bukva se sostoi od dva wchar_t-ovi, za nekolku prvata polovina se poklopuva, no vtorata e sekogas unikatna (vo ovoj slucaj (mak azbuka))
        switch (second_half)
        {
        case  L'\u00b0':
            return 0;
        case  L'\u00b1':
            return 1;
        case  L'\u00b2':
            return 2;
        case  L'\u00b3':
            return 3;
        case  L'\u00b4':
            return 4;
        case  L'\u0093':
            return 5;
        case  L'\u00b5':
            return 6;
        case  L'\u00b6':
            return 7;
        case  L'\u00b7':
            return 8;
        case  L'\u0095':
            return 9;
        case  L'\u00b8':
            return 10;
        case  L'\u0098':
            return 11;
        case  L'\u00ba':
            return 12;
        case  L'\u00bb':
            return 13;
        case  L'\u0099':
            return 14;
        case  L'\u00bc':
            return 15;
        case  L'\u00bd':
            return 16;
        case  L'\u009a':
            return 17;
        case  L'\u00be':
            return 18;
        case  L'\u00bf':
            return 19;
        case  L'\u0080':
            return 20;
        case  L'\u0081':
            return 21;
        case  L'\u0082':
            return 22;
        case  L'\u009c':
            return 23;
        case  L'\u0083':
            return 24;
        case  L'\u0084':
            return 25;
        case  L'\u0085':
            return 26;
        case  L'\u0086':
            return 27;
        case  L'\u0087':
            return 28;
        case  L'\u009f':
            return 29;
        case  L'\u0088':
            return 30;
        }
    }                                       //Ne, ne go pisuvav ova racno

    String TransformString(String word){    //Sekoja mkd bukva se sostoi od dva dela, potreben ni e samo vtoriot
        String rez;                         // vo kodot ide char po char za sekoja bukva, no tuka sekoj dva chara se edna bukva
        for(int i=1;i<word.size();i+=2)     
            rez+=word[i];
        return rez;
    }

#endif




struct TrieNode {
    bool word_end = false;
    TrieNode * kids[AlphabetSize] = { 0 };
    ~TrieNode() {
        for (int i = 0; i < AlphabetSize; i++) {
            if (kids[i] != nullptr)
                delete kids[i];
        }
    }
};

class Trie {
    TrieNode * root;

    void preorder(TrieNode * node, String str, Ostream & out) {
        if (node->word_end)
            out << str << endl;
        for (int i = 0; i < AlphabetSize; i++) {
            if (node->kids[i] != nullptr) {
                preorder(node->kids[i], str + IndexToLetter(i), out);
            }
        }
    }

public:
    void add(String word) {
        word=TransformString(word);
        TrieNode * cur = root;
        for (int j = 0; j < word.length(); j++) {
            int i = LetterToIndex(word[j]);
            if (cur->kids[i] == nullptr) {
                cur->kids[i] = new TrieNode;
            }
            cur = cur->kids[i];
            if (j + 1 == word.length())
                cur->word_end = true;
        }
    }
    bool exists(String word) {
        word=TransformString(word);
        TrieNode * cur = root;
        for (int j = 0; j < word.length(); j++) {
            int i = LetterToIndex(word[j]);
            if (cur->kids[i] == nullptr)
                return false;
            cur = cur->kids[i];
        }
        return true;
    }
    void print(Ostream & out = Cout) {
        preorder(root, String(), out);
    }

    Trie() {
        root = new TrieNode;
    }
    ~Trie() {
        if (root != nullptr)
            delete root;
    }



};


 