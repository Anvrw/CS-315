#include <iostream>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;


string b[30][28];
int c[30][28];
ofstream out;

void LCS_LENGTH(string X, string Y){

    int m, n;
    m = X.length();
    n = Y.length();

    for (int i = 0; i <= m; i++){
        c[i][0] = 0;
    }
    for (int j = 0; j <= n; j++){
        c[0][j] = 0;
    }
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = "↖";
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = "↑";
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = "←";
            }
        }
    }
}

void PRINT_LCS(string X,  int i, int j){

    if(i == 0 || j == 0)
        return;
    else if (b[i][j] == "↖"){
        PRINT_LCS(X, i - 1 , j - 1);
        out << X[i-1];
    }
    else if (b[i][j] == "↑"){
        PRINT_LCS(X,i-1,j);
    }
    else{
        PRINT_LCS(X,i,j-1);
    }
}

int NAIVE_STRING_MATCH(string T, string P){
    int m, n;
    n = T.length();
    m = P.length();

    for(int s = 0; s <= n-m; s++){
        if(P.substr(0,m) == T.substr(s,m))
            return s;
    }
    return -1;
}

int main() {

    string X, Y;
    int naive;

    ifstream myFile;
    myFile.open("dna.txt");

    if (!myFile.good()){
        cout << "Warning: Can't open file" << endl;
    }
    else{
        string input;
        myFile>>input;
        X = input;
        myFile>>input;
        Y = input;
    }
    myFile.close();

    int m = X.length();
    int n = Y.length();

    LCS_LENGTH(X,Y);

    out.open("results.txt");
    out << c[m][n] << endl;
    PRINT_LCS(X,m,n);
    out.close();
    out.open("bonusResults.txt");
    naive = NAIVE_STRING_MATCH(X,"GCCGGCC");
    out << naive << endl;
    naive = NAIVE_STRING_MATCH(Y, "GCCGGCC");
    out << naive << endl;

}