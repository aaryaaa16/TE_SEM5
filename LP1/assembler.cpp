//============================================================================
// Name        : Assignment_2.cpp
// Author      : 31458
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

class Tables {
public:
	unordered_map<string, pair<string, int>> OPTAB;
	unordered_map<string, int> REG;
	unordered_map<string, int> CONDCS;
    vector<pair<string, int>> symbolTable;

	Tables(){
		OPTAB["STOP"] = {"IS",0};
		OPTAB["ADD"] = {"IS",1};
		OPTAB["SUB"] = {"IS",2};
		OPTAB["MULT"] = {"IS",3};
		OPTAB["MOVER"] = {"IS",4};
		OPTAB["MOVEM"] = {"IS",5};
		OPTAB["COMP"] = {"IS",6};
		OPTAB["BC"] = {"IS",7};
		OPTAB["DIV"] = {"IS",8};
		OPTAB["READ"] = {"IS",9};
		OPTAB["PRINT"] = {"IS",10};
		OPTAB["START"] = {"AD",1};
		OPTAB["END"] = {"AD",2};
		OPTAB["ORIGIN"] = {"AD",3};
		OPTAB["EQU"] = {"AD",4};
		OPTAB["LTORG"] = {"AD",5};
		OPTAB["DC"] = {"DL",1};
		OPTAB["DS"] = {"DL",2};

		REG["AREG"]=1;
		REG["BREG"]=2;
		REG["CREG"]=3;
		REG["DREG"]=4;

		CONDCS["LT"]=1;
		CONDCS["LE"]=2;
		CONDCS["EQ"]=3;
		CONDCS["GT"]=4;
		CONDCS["GE"]=5;
		CONDCS["ANY"]=6;
	}

    int searchSymbol(string symbol) {
        for (int i = 0; i < symbolTable.size(); i++) {
            if (symbolTable[i].first == symbol) {
                return i;
            }
        }
        return -1;
    }
};

class Assembler {
    Tables t;
    fstream file;

    public:
    Assembler() {
        file.open("sample.txt", ios::in);
        if (!file.is_open()) {
            cout<<"Error openeing file"<<endl;
        }
    }

    void intermediateCode() {
        vector<string> words;
        string line;
        int counter = 0;
        int lc;
        int scounter = 0;
        int index;
        pair<string, int> ic;
        pair<string, int> ic1;
        pair<string, int> ic2;
        pair<string, int> symbol;
        if (file.is_open()) {
            while (!file.eof()) {
                getline(file, line);
                string w = "";
                for (int i = 0;i < line.size(); i++) {
                    if (line[i] != ' ') {
                        w += line[i];
                    } else {
                        words.push_back(w);
                        w = "";
                    }
                }
                words.push_back(w);

                if (words[0] == "START") {
                    counter = stoi(words[1]);
                    ic.first = "AD";
                    ic.second = 01;
                    ic1.first = "C";
                    ic1.second = stoi(words[1]);
                    cout<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.first<<", "<<ic1.second<<")"<<endl;
                } else if (words[0] == "END") {
                    ic.first = "AD";
                    ic.second = 02;
                    cout<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<endl;
                    break;
                } else if (words.size() == 1) {
                    lc = counter++;
                    if (t.OPTAB.find(words[0]) != t.OPTAB.end()) {
                        ic = t.OPTAB[words[0]];
                    }
                    cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<endl;
                } else if (words.size() == 2) {
                    lc = counter++;
                    if (t.OPTAB.find(words[0]) != t.OPTAB.end()) {
                        ic = t.OPTAB[words[0]];
                    }
                    index = t.searchSymbol(words[1]);
                    ic1.first = "S";
                    if (index >= 0) {
                        ic1.second = index;
                    } else {
                        scounter++;
                        ic1.second = scounter;
                        symbol.first = words[1];
                        symbol.second = -1;
                        t.symbolTable.push_back(symbol);
                    }
                    cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.first<<", "<<ic1.second<<")"<<endl;
                } else if (words.size() == 3) {
                    lc = counter++;
                    if (t.OPTAB.find(words[0]) != t.OPTAB.end()) {
                        ic = t.OPTAB[words[0]];
                        ic1.second = t.REG[words[1]];
                        index = t.searchSymbol(words[2]);
                        ic2.first = "S";
                        if (index >= 0) {
                            ic2.second = index;
                        } else {
                            scounter++;
                            ic2.second = scounter;
                            symbol.first = words[2];
                            symbol.second = -1;
                            t.symbolTable.push_back(symbol);
                        }
                        cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.second<<")"<<"\t"<<"("<<ic2.first<<", "<<ic2.second<<")"<<endl;
                    } else if (t.OPTAB.find(words[1]) != t.OPTAB.end()) {
                        ic = t.OPTAB[words[1]];
                        ic1.first = "C";
                        ic1.second = stoi(words[2]);
                        index = t.searchSymbol(words[0]);
                        t.symbolTable[index].second = lc;
                        cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.first<<", "<<ic1.second<<")"<<endl;
                    }
                } else {
                    lc = counter++;
                    if (t.OPTAB.find(words[1]) != t.OPTAB.end()) {
                        ic = t.OPTAB[words[1]];
                    }
                    ic1.second = t.REG[words[2]];
                    index = t.searchSymbol(words[0]);
                    ic2.first = "S";
                    if (index >= 0) {
                        ic2.second = index;
                        t.symbolTable[index].second = lc;
                    } else {
                        scounter++;
                        ic2.second = scounter;
                        symbol.first = words[0];
                        symbol.second = lc;
                        t.symbolTable.push_back(symbol);
                    }
                    cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.second<<")"<<"\t"<<"("<<ic2.first<<", "<<ic2.second<<")"<<endl;
                }
                words.clear();
            }
        } else {
            cout<<"Error opening file"<<endl;
        }
    }

    void displaySymbolTable() {
        cout<<"Symbol\tAddress"<<endl;
        for (int i = 0; i < t.symbolTable.size(); i++) {
            cout<<t.symbolTable[i].first<<"\t"<<t.symbolTable[i].second<<endl;
        }
    }
};

int main() {
    Assembler a;
    a.intermediateCode();
    a.displaySymbolTable();
}