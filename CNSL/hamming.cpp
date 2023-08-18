#include <bits/stdc++.h>
using namespace std;

string parity(string str) {
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '1') {
            count++;
        }
    }

    if (count % 2 == 0) {
        return "0";
    } else {
        return "1";
    }
}

string takeDrop(string arr[], int temp, int n) {
    int count = 0;
    string str;
    bool flag = true;
    for (int j = n - temp; j >= 0; j--) {
        if (count == temp) {
            flag = !flag;
            count = 0;
        }
        if (flag && (arr[j] == "1" || arr[j] == "0")) {
            str += arr[j];
        }
        count++;
    }
    cout<<str<<endl;
    return parity(str);
}

int main() {
    string str = "100110011001";
    int m = str.length();
    int r = 0;

    while (pow(2, r) < m + r + 1) {
        r++;
    }
    
    int n = m + r;
    string arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = " ";
    }

    for (int i = 0; i < r; i++) {
        int temp = pow(2, i);
        arr[n - temp] = "r" + to_string(temp);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == " ") {
            arr[i] = str[count];
            count++;
        }
    }

    for (int i = 0; i < r; i++) {
        int temp = pow(2, i);
        arr[n - temp] = takeDrop(arr, temp, n);
    }

    string word;
    for (int i = 0; i < r; i++) {
        int temp = pow(2, i);
        word += takeDrop(arr, temp, n);
    }
    cout<<word<<endl;
}