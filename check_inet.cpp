#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

vector<int> customInput(string myString) {
    vector<int> arr;
    for (int i = 0; i < myString.size(); ++i) {
        stringstream s;
        bitset<8> str2(myString[i]);
        s << str2.to_ullong();
        uint16_t x = 0;
        s >> x;
        arr.push_back(x);
  	}
    return arr;
}

int sender(int b[],int k) {
 	uint16_t checksum, i;
    uint32_t sum = 0;
    printf("\n****SENDER****\n");
    for(i = 0; i < k; i++) {
        sum += b[i];
    }
    bitset<32> sp(sum);
    if (sp[16] != 0) {
        bitset<32> temp;
        temp[0] = sp[16];
        sum += temp[0];
    }
    sum = (sum & 0xFFFF) + (sum >> 16);
    cout <<"SENDER SUM IS: "<< hex << sum;           
    checksum = ~sum;
    cout<<"\n"<< "SENDER'S CHECKSUM IS: "<< hex << checksum<<endl;
    printf("*************\n");
    return checksum;
}
 
int receiver(int c[], int k, int scheck) {
    uint16_t checksum, i;
    uint32_t sum = 0;
    printf("\n****RECEIVER****\n");
    for(i = 0; i < k; i++)
        sum += c[i];
    bitset<32> sp(sum);
    if (sp[16] != 0) {
        cout << sp[16];
        bitset<32> temp;
        temp[0] = sp[16];
        sum += temp[0];
    }
    cout <<"RECEIVER SUM IS: "<< hex << sum;           
    sum = sum + scheck;
    bitset<32> sp2(sum);
    if (sp2[16] != 0) {
        bitset<32> temp;
        temp[0] = sp2[16];
        sum += temp[0];
    }
    checksum = ~sum;
    cout<<"\nRECEIVER's CHECKSUM IS: "<< hex << checksum<<endl;
    printf("*************\n");
    return checksum;
}

int main() {
	string myString;
    string anotherInput;
    cout << "\nEnter the sender string\n";
    cin>> myString;
  	vector<int> send = customInput(myString);
    int input[send.size()];
    copy(send.begin(), send.end(), input);
    int sCheck = sender(input, send.size());

    cout <<"\nEnter the receiver string\n";
    cin>> anotherInput;
    vector<int> receive = customInput(anotherInput);
    int output[receive.size()];
    copy(receive.begin(), receive.end(), output);
    int rCheck = receiver(output, receive.size(), sCheck);

    if (rCheck == 0) {
        cout<< "\nNo error in transmission\n";
    } else {
        cout << "\nError in transmission\n";
    }
    return 0;
}
