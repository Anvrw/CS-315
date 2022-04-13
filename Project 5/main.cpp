#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

const int d = 10;
const int q = 61;

int intPower(int base, int exp) {
    int result = 1;
    for (;;) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

int RABIN_KARP_MATCHER(string T, string P) {

 int n = T.length();
 int m = P.length();
 int h = intPower(d,m-1) % q;
 int p = 0;
 int t0 = 0;

    for(int i = 0; i < m; i++){
        p = ((d * p) + P[i]) % q;
        t0 = ((d * t0) + T[i]) % q;
    }
    for(int s = 0; s <= (n-m); s++){
        if(p == t0){
            if(P.substr(0,m) == T.substr(s,m))
                return s;
        }
        if(s < (n - m)){
            t0 = (d * (t0 - T[s] * h) + T[s + m]) % q;
        }
        if (t0 < 0){
            t0 = t0 + q;
        }
    }
   return -1;
}

int main(){

    string T, P;
    int output;
    ofstream out;


    ifstream myFile;
    myFile.open("pi.txt");

    if (!myFile.good()){
        cout << "Warning: Can't open file" << endl;
    }
    else{

        string input;
        myFile>>input;
        T = input;
        myFile>>input;
        P = input;

    }

    myFile.close();

    output = RABIN_KARP_MATCHER(T,P);
    out.open("results.txt");
    out << output << endl;

}
