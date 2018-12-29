#include <iostream>

using namespace std;

#define MIN(x, y) (x > y) ? y : x

int main() {
    int orate, drop = 0, sizeBucket, x, count = 0;
    int inp[10] = {0}, i = 0, noOfSec, ch;

    cout<< "Enter bucket size\n";
    cin>>sizeBucket;

    cout<< "Enter output rate\n";
    cin>> orate;

    do {
        cout << "Enter no of packets coming at second " << i + 1 << "\n";
        cin>> inp[i];

        cout << "Enter 0 to quit and 1 to continue\n ";
        cin >> ch;
    } while (ch);
    noOfSec = i;
    
    cout<<"\nSecond \tReceived \tSent \tDropped \tRemained \n";
    for (i = 0; count || i < noOfSec; i++) {
        cout << i + 1;
        cout << "\t" << inp[i];
        cout << "\t" << (MIN((inp[i] + count), orate));
        if ((x = inp[i] + count - orate) > 0) {
            if (x > sizeBucket) {
                count = sizeBucket;
                drop = x - sizeBucket;
            } else {
                count = x;
                drop = 0;
            }
        } else {
            count = 0;
            drop = 0;
        }
        cout << "\t" << drop << "\t" << count;
    }
    return 0;
}
