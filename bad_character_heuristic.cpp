#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void boyerMoorePreProcessing_Bch(string pattern, unordered_map<char, int> &badMatchTable) {
    int length = pattern.size();
    for (int i = 0; i < length; i++) {
        badMatchTable[pattern[i]] = length - i - 1;
    }
    badMatchTable[pattern[length - 1]] = length;
}

void SearchPattern(string text, string pattern, vector<int> &occurances_pos) {
    unordered_map<char, int> badMatchTable;
    boyerMoorePreProcessing_Bch(pattern, badMatchTable);
    int l = 0, r = pattern.size() - 1;
    int len_p = pattern.size();
    int len_t = text.size();
    while (r < len_t) {
        int shift = 0;
        for (int i = len_p-1; i >=0; i--) {
            if (pattern[i] != text[l + i]) {
                if (i != len_p - 1) {
                    shift = len_p;
                } else {
                    if (badMatchTable.find(text[l + i]) == badMatchTable.end()) {
                        shift = len_p;
                    } else {
                        shift = badMatchTable[text[l + i]];
                    }
                }
                break;
            }
        }
        if (shift == 0) {
            occurances_pos.push_back(l);
            shift=1;
        }
        l += shift;
        r += shift;
    }
}

int main() {
    vector<int> v;
    string text;
    string pattern="gcaact";

    ifstream MyReadFile("C:\\Users\\Sukumar Ganesan\\Desktop\\BoyerMoore\\DNA.txt");
    string myText;
    while (getline (MyReadFile, myText)) {
        myText.erase(myText.size()-2);
        text+=myText;
    }

    SearchPattern(text, pattern, v);
    for(int i=0;i<v.size();i++)
    {
        cout<<"Occurance at position : "<<v[i]<<endl;
    }
    cout<<"Total occurances of the pattern is : "<<v.size()<<endl;
    MyReadFile.close();
    return 0;
}
