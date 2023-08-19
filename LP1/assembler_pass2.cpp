#include <bits/stdc++.h>
using namespace std;

class Tables {
    vector<pair<string, string>> SYMBTAB;
    vector<pair<string, string>> LITTAB;

    public:
    Tables() {
        fstream symb_tab;
        symb_tab.open("symbol_table.txt", ios::in);
        if (!symb_tab.is_open()) {
            cout<<"Error opening file"<<endl;
        }

        fstream lit_tab;
        lit_tab.open("literal_table.txt", ios::in);
        if (!lit_tab.is_open()) {
            cout<<"Error opening file"<<endl;
        }
    }
};