#include <iostream>

using namespace std;

const unsigned int AlphabetSize = 26;

struct PtrieNode {
    string prefix;
    PtrieNode * kids[AlphabetSize + 1] = { 0 }; //abc...xyz$
    PtrieNode(string lead = "") :prefix(lead) {
        for (int i = 0; i <= AlphabetSize; i++)
            kids[i] = 0;
    }
    ~PtrieNode() {
        for (int i = 0; i <= AlphabetSize; i++) {
            if (kids[i] != nullptr)
                delete kids[i];
        }
    }
};

int LetterToIndex(char c) {

    if (c == '$') return AlphabetSize;
    return c - 'a';
}

class Patricia
{
    PtrieNode * root;

    void preorder(PtrieNode * node, string str, ostream & out) {
        if (node->kids[AlphabetSize] != nullptr)
            out << str << endl;
        else if (str[str.length() - 1] == '$') out << str.substr(0, str.length() - 1) << endl;
        for (int i = 0; i < AlphabetSize; i++) {
            if (node->kids[i] != nullptr) {
                preorder(node->kids[i], str + node->kids[i]->prefix, out);
            }
        }

    }
public:
    void add(string word) {
        word += '$';
        PtrieNode * cur = root;
        int j = 0;
        while (j < word.length()) {
            int i = LetterToIndex(word[j]);

            if (cur->kids[i] == nullptr) {
                cur->kids[i] = new PtrieNode(word.substr(j));//od j do kraj
                return;
            }

            PtrieNode * next = cur->kids[i];
            // cout << word << " " << next->prefix << endl;
            for (int k = 0; k < next->prefix.length(); k++, j++) {
                // cout << next->prefix[k] << " " << word[j] << "  " << k << " " << j << endl;
                if (next->prefix[k] != word[j]) {
                    PtrieNode * nju = new PtrieNode(next->prefix.substr(k));
                    for (int x = 0; x < AlphabetSize + 1; x++) {
                        nju->kids[x] = next->kids[x];
                        next->kids[x] = nullptr;
                    }
                    next->kids[LetterToIndex(nju->prefix[0])] = nju;
                    next->kids[LetterToIndex(word[j])] = new PtrieNode(word.substr(j));
                    next->prefix = next->prefix.substr(0, k);

                    return;
                }
            }
            cur = next;
        }
    }
    bool exists(string word) {
        word += '$';
        PtrieNode * cur = root;
        int j = 0;
        while (j < word.length()) {
            int i = LetterToIndex(word[j]);

            if (cur->kids[i] == nullptr) {
                return false;
            }


            PtrieNode * next = cur->kids[i];
            for (int k = 0; k < next->prefix.length(); k++, j++) {
                if (next->prefix[k] != word[j]) {
                    return false;
                }
            }
            cur = next;
        }
        return true;
    }
    void print(ostream & out = cout) {
        preorder(root, "", out);
    }
    Patricia() {
        root = new PtrieNode;
    }
    ~Patricia() {
        if (root != nullptr)
            delete root;
    }

};





// int main() {

//     Patricia trie;

//     string str;
//     while (cin >> str)
//     {
//         if (str == "-1")break;
//         trie.add(str);
//         cout << trie.exists(str) << " " << trie.exists(str + 'a') << endl;
//     }
//     cout << endl;
//     trie.print();


//     return 0;
// }