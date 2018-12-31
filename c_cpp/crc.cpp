#include <iostream>
#include <cstring>

using namespace std;

#define N strlen(g)

char t[28];
char cs[28];
char g[] = "10001000000100001";

int a, e, c;

void Xor() {
    for (c = 1; c < N; c++) {
        cs[c] = (cs[c] == g[c]) ? '0' : '1';
    }
}

void crc() {
    for (e = 0; e < N; e++)
        cs[e] = t[e];
    do {
        if (cs[0] == '1')
            Xor();
        for (c = 0; c < N; c++) {
            cs[c] = cs[c+1];
        }
        cs[c] = cs[e++];
    } while (e <= a + N - 1);
}

int main() {
    cout << "\nEnter data\n";
    cin >> t;
    cout << "\n--------------\n";
    cout << "Generating Polynomial " << g;
    a = strlen(t);
    for (e = a; e < a+N-1; e++) {
        t[e] = '0';
    }
    cout<< "\nPadded data is " << t;
    crc();
    cout << "\nThe checksum is " << cs;
    for (e = a; e < a+N-1; e++) 
        t[e] = cs[e-a];
    cout << "\nThe final codeword is " << t;
    cout << "\n\nTest Error detection yes or no (0 or 1) \n";
    cin >> e;
    if (e == 0) {
        do{
            cout << ("\nEnter the position where error is to be inserted : ");
            cin >> e;
        }while(e==0 || e>a+N-1);
        t[e-1]=(t[e-1]=='0')?'1':'0';
        cout << ("\n----------------------------------------");
        cout << "\nErroneous data : " << t;
    }
    crc();
    for(e=0;(e<N-1) && (cs[e]!='1');e++){}  // checksum (i.e cs array ) should have all zeroes after performing crc operation, so if any 1 is found e is not incremented and hence e will become less than N-1 and therefore we can say there is an error in the transmitted message.
    if(e<N-1)
        cout << ("\nError detected\n\n");
    else
        cout << ("\nNo error detected\n\n");
        cout << ("\n----------------------------------------\n");
    return 0;
}