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
    vector<pair<string, int>> SYMBTAB;
    vector<pair<string, int>> LITTAB;
    vector<int> POOLTAB;

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
        for (int i = 0; i < SYMBTAB.size(); i++) {
            if (SYMBTAB[i].first == symbol) {
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
            cout<<"Error opening file"<<endl;
        }
    }

    void intermediateCode() {
        vector<string> words;
        string line;
        int counter = 0;
        int lc;
        int scounter = 0;
        int lcounter = 0;
        int pcounter = 0;
        int index;
        int temp = 0;
        pair<string, int> ic;
        pair<string, int> ic1;
        pair<string, int> ic2;
        pair<string, int> symbol;
        pair<string, int> literal;
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
                if (words[0] == "START") { //STRAT
                    counter = stoi(words[1]);
                    ic.first = "AD";
                    ic.second = 01;
                    ic1.first = "C";
                    ic1.second = stoi(words[1]);
                    cout<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.first<<", "<<ic1.second<<")"<<endl;
                } else if (words[0] == "END") { //END
                	lc = counter++;
                    ic.first = "AD";
                    ic.second = 02;
                    cout<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<endl;
                    t.POOLTAB.push_back(pcounter + 1);
                    t.LITTAB[pcounter].second = lc;
                    for (int i = pcounter + 1; i < t.LITTAB.size(); i++) {
                    	lc = counter++;
                    	t.LITTAB[i].second = lc;
                    }
                    break;
                } else if (words.size() == 1) {
                    lc = counter++;
                    if (words[0] == "LTORG") { //LTORG
                    	if (t.OPTAB.find(words[0]) != t.OPTAB.end()) {
                    		ic = t.OPTAB[words[0]];
                    	}
                    	cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<endl;
                    	t.POOLTAB.push_back(pcounter + 1);
                    	t.LITTAB[pcounter].second = lc;
                    	for (int i = pcounter + 1; i < t.LITTAB.size(); i++) {
                    		lc = counter++;
                    		t.LITTAB[i].second = lc;
                    		temp = i;
                    	}
                    	pcounter = temp + 1;
                    } else { //opcode
                    	if (t.OPTAB.find(words[0]) != t.OPTAB.end()) {
                    		ic = t.OPTAB[words[0]];
                    	}
                    	cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<endl;
                    }
                } else if (words.size() == 2) {
                    lc = counter++;
                    if (words[0] == "ORIGIN") { //ORIGIN
                    	if (t.OPTAB.find(words[0]) != t.OPTAB.end()) {
                    		ic = t.OPTAB[words[0]];
                    	}
                    	index = t.searchSymbol(words[1]);
                    	counter = t.SYMBTAB[index].second;
                    	ic1.first = "S";
                    	ic1.second = index + 1;
                    } else { //opcode, symbol
                    	if (t.OPTAB.find(words[0]) != t.OPTAB.end()) {
                    		ic = t.OPTAB[words[0]];
                    	}
                    	index = t.searchSymbol(words[1]);
                    	ic1.first = "S";
                    	if (index >= 0) {
                    		ic1.second = index + 1;
                    	} else {
                    		scounter++;
                    		ic1.second = scounter;
                    		symbol.first = words[1];
                    		symbol.second = -1;
                    		t.SYMBTAB.push_back(symbol);
                    	}
                    }
                    cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.first<<", "<<ic1.second<<")"<<endl;
                } else if (words.size() == 3) {
                    lc = counter++;
                    if (t.OPTAB.find(words[0]) != t.OPTAB.end()) {
                        ic = t.OPTAB[words[0]];
                        if (t.REG.find(words[1]) != t.REG.end()) {
                        	ic1.second = t.REG[words[1]];
                        } else if (t.CONDCS.find(words[1]) != t.CONDCS.end()) {
                        	ic1.second = t.CONDCS[words[1]];
                        }
                        if (t.REG.find(words[2]) != t.REG.end()) { //opcode, register, register
                        	ic2.second = t.REG[words[2]];
                        	cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.second<<")"<<"\t"<<"("<<ic2.second<<")"<<endl;
                        } else if (words[2].at(0) == '=') { //opcode, register, literal
                        	lcounter++;
                        	ic2.first = "L";
                        	ic2.second = lcounter;
                        	literal.first = words[2];
                        	literal.second = -1;
                        	t.LITTAB.push_back(literal);
                        	cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.second<<")"<<"\t"<<"("<<ic2.first<<", "<<ic2.second<<")"<<endl;
                        } else { //opcode, register, symbol
                        	ic2.first = "S";
                        	index = t.searchSymbol(words[2]);
                        	if (index >= 0) {
                        		ic2.second = index + 1;
                        	} else {
                        		scounter++;
                        		ic2.second = scounter;
                        		symbol.first = words[2];
                        		symbol.second = -1;
                        		t.SYMBTAB.push_back(symbol);
                        	}
                        	cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.second<<")"<<"\t"<<"("<<ic2.first<<", "<<ic2.second<<")"<<endl;
                        }
                    } else if (t.OPTAB.find(words[1]) != t.OPTAB.end()) {
                        ic = t.OPTAB[words[1]];
                        if (words[1] == "EQU") { //EQU
                        	index = t.searchSymbol(words[0]);
                        	if (index < 0) {
                        		scounter++;
                        		symbol.first = words[0];
                        		symbol.second = lc;
                        		t.SYMBTAB.push_back(symbol);
                        	} else {
                        		t.SYMBTAB[index].second = lc;
                        	}
                        	ic2.first = "S";
                        	index = t.searchSymbol(words[2]);
                        	ic2.second = index + 1;
                        } else { //symbol, opcode, constant
                        	ic1.first = "C";
                        	ic1.second = stoi(words[2]);
                        	index = t.searchSymbol(words[0]);
                            t.SYMBTAB[index].second = lc;
                        }
                        cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.first<<", "<<ic1.second<<")"<<endl;
                    }
                } else {
                    lc = counter++;
                    if (t.OPTAB.find(words[1]) != t.OPTAB.end()) {
                        ic = t.OPTAB[words[1]];
                    }
                    ic1.second = t.REG[words[2]];
                    scounter++;
                    symbol.first = words[0];
                    symbol.second = scounter;
                    t.SYMBTAB.push_back(symbol);
                    if (t.REG.find(words[3]) != t.REG.end()) {
                    	ic2.second = t.REG[words[3]];
                    	cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.second<<")"<<"\t"<<"("<<ic2.second<<")"<<endl;
                    } else {
                    	index = t.searchSymbol(words[3]);
                    	ic2.first = "S";
                    	if (index >= 0) {
                    		ic2.second = index + 1;
                    		t.SYMBTAB[index].second = lc;
                    	} else {
                    		scounter++;
                    		ic2.second = scounter;
                    		symbol.first = words[3];
                    		symbol.second = lc;
                    		t.SYMBTAB.push_back(symbol);
                    	}
                    	cout<<lc<<"\t"<<"("<<ic.first<<", "<<ic.second<<")"<<"\t"<<"("<<ic1.second<<")"<<"\t"<<"("<<ic2.first<<", "<<ic2.second<<")"<<endl;
                    }
                }
//                for (int i = 0; i < words.size(); i++) {
//                	cout<<words[i]<<endl;
//                }
//                cout<<endl;
                words.clear();
            }
        } else {
            cout<<"Error opening file"<<endl;
        }
    }

    void displaySymbolTable() {
        cout<<"Symbol\tAddress"<<endl;
        for (int i = 0; i < t.SYMBTAB.size(); i++) {
            cout<<t.SYMBTAB[i].first<<"\t"<<t.SYMBTAB[i].second<<endl;
        }
    }

    void displayLiteralTable() {
    	cout<<"Literal\tAddress"<<endl;
    	for (int i = 0; i < t.LITTAB.size(); i++) {
    		cout<<t.LITTAB[i].first<<"\t"<<t.LITTAB[i].second<<endl;
    	}
    }

    void displayPoolTable() {
    	cout<<"Pool"<<endl;
    	for (int i = 0; i < t.POOLTAB.size(); i++) {
    		cout<<t.POOLTAB[i]<<endl;
    	}
    }
};

int main() {
    Assembler a;
    a.intermediateCode();
    a.displaySymbolTable();
    a.displayLiteralTable();
    a.displayPoolTable();
}