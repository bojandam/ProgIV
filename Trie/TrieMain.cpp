#include <iostream>
#include <fstream>

#define MKD
#include "Trie.h"




int main() {

    wifstream in("words.txt");
    wofstream out("result.txt");
    wstring word;
    Trie trie;
    while (in >> word)
    {
        out << word;
        trie.add(word);
        out << " " << trie.exists(word) << " " << trie.exists(word + IndexToLetter(0)) << endl;// 1 0
        // edno tocno i edno gresno kveri
    }
    out << endl;

    //Gi pecati site zborovi po leksikografski redosled
    trie.print(out);
    in.close();
    out.close();
}
