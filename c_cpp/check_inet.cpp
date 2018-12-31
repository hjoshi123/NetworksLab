#include <iostream>

using namespace std;

// Calculating Checksum for both sender and receiver
int checksum(string s, int check) {
  int temp;
  int n, sum = 0;
  if (s.size() % 2 != 0) {
    n = (s.size() + 1) / 2;
  } else {
    n = s.size() / 2;
  }
  // temp << 8 shifts 8 bits so that the other 8 bits can be appended
  // for example Fo implies 46--. To add -- we use temp << 8
  for (int i = 0; i < n; i++) {\
    temp = s[i*2];
    temp = (temp << 8) + s[(i*2)+1];
    sum += temp;
  }
  
  //Valid only for receiver
  if (check != 0)
    sum += check;
  
  // Folding 32 bits to 16 bits for final checksum
  while (sum >> 16)
    sum = (sum & 0xFFFF) + (sum >> 16);
  return sum;
}

int main(void) {
  int ch, send, recv;
  string s;
  do {
    cout << "\nEnter a choice \n1:Send \n2:Receive \n3:Exit\n";
    cin>> ch;

    switch(ch) {
      case 1: {
        cout << "\nEnter string\n";
        cin>>s;
        send = checksum(s, 0);

        // ~ => complementing oxFFFF is a mask to print only the 16 bits and ignore the rest
        send = ~send & 0xFFFF ;

        cout << "\n---------SENDER'S CHECKSUM----------- " << hex << send << "\n";
        break;
      }
      case 2: {
        cout << "\nEnter string\n";
        cin>>s;
        recv = checksum(s, send);
        cout <<"\n------------RECEIVER'S CHECKSUM-------- "<< hex << recv;
        recv = ~recv & 0xFFFF;
        if (recv == 0)
          cout << "\nCorrect string\n";
        else
          cout << "\nWrong String\n";
        break;
      }
      case 3:
        break;
      default:
        cout << "Try Again\n";
    }
  } while (ch != 3);
  return 0;
}