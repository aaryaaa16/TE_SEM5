#include <bits/stdc++.h>
using namespace std;

string division(string dividend, string divisor) {
    vector<char> result;
    for (int i = 0; i <= dividend.length() - divisor.length(); i++) {
		result.clear();
		if (dividend[i] == '1') {
			for (int j = 0; j < divisor.length(); j++) {
				int temp = int(dividend[i + j] - '0') ^ int(divisor[j] - '0');
				dividend[i + j] = char(temp + '0');
				result.push_back(char(temp + '0'));
			}
		} else {
			for (int j = 0; j < divisor.length(); j++) {
				result.push_back(dividend[i + j]);
			}
		}
	}

    result.erase(result.begin());
    string remainder(result.begin(), result.end());
    return remainder;
}

int main() {
	string dividend = "1101011011";
	string divisor = "10011";
    string remainder;

	for (int i = 0; i < divisor.length() - 1; i++) {
		dividend += '0';
	}
    remainder = division(dividend, divisor);
    
    for (int i = 0; i < remainder.length(); i++) {
        int temp = dividend.length() - divisor.length() + i + 1;
        dividend[temp] = remainder[i];
    }
    remainder = division(dividend, divisor);
    cout<<remainder<<endl;
}