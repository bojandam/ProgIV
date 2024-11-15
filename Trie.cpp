#include <iostream>
#include <stack>
using namespace std;

const unsigned int AlphabetSize = 26; //eng: 26     mkd: 31
const unsigned char FirstLetter = 'a';//eng: 'a'    mkd:   
typedef char Char;                    //eng: char   mkd:
typedef string String;                //eng: string mkd:

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

    void preorder(TrieNode * node, String str, ostream & out) {
        if (node->word_end)
            out << str << endl;
        for (int i = 0; i < AlphabetSize; i++) {
            if (node->kids[i] != nullptr) {
                preorder(node->kids[i], str + ((Char)(i + FirstLetter)), out);
            }
        }
    }

public:
    void add(String word) {
        TrieNode * cur = root;
        for (int j = 0; j < word.length(); j++) {
            int i = word[j] - FirstLetter;
            if (cur->kids[i] == nullptr) {
                cur->kids[i] = new TrieNode;
            }
            cur = cur->kids[i];
            if (j + 1 == word.length())
                cur->word_end = true;
        }
    }
    bool exists(String word) {
        TrieNode * cur = root;
        for (int j = 0; j < word.length(); j++) {
            int i = word[j] - FirstLetter;
            if (cur->kids[i] == nullptr)
                return false;
            cur = cur->kids[i];
        }
        return true;
    }
    void print(ostream & out = cout) {
        preorder(root, "", out);
    }

    Trie() {
        root = new TrieNode;
    }
    ~Trie() {
        if (root != nullptr)
            delete root;
    }



};




int main() {

    Trie tree;

    string str;
    for (int i = 0; i < 10; i++)
    {
        cin >> str;
        tree.add(str);
        cout << tree.exists(str) << endl;
    }
    for (int i = 0; i < 4; i++) {
        cin >> str;
        cout << tree.exists(str) << endl;
    }
    tree.print();



    return 0;
}
