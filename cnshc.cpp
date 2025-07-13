#include<iostream>
using namespace std;
int main() {
    int a;
    cout << "who are you?? 1.Sender 2.Reciver.:";
    cin >> a;
    int a1[4], a2[6];
    switch (a) {
        case 1:
            cout << "Enter the 4-bit data bit:";
            for (int i =0; i <4; i++) {
                cin >> a1[i];
            }
            a2[4] =a1[0];
            a2[2] =a1[1];
            a2[0] =a1[3];
            a2[1] =a1[2];
            a2[6] =(a2[4]^a2[2])^a2[0];
            a2[5] =(a2[4]^a2[1])^a2[0];
            a2[3] =(a2[2]^a2[1])^a2[0];
            for (int j =0; j <=6; j++) {
                cout << a2[j] << " ";
            }
            break;
        case 2:
            int b, a3[6];
            for (int k =0; k <=6; k++) {
                cin >> a3[k];
            }
            b =(a3[3]*4)+(a3[5]*2)+(a3[6]*1);
            if (b ==0) {
                cout << "No error in CRC process.";
            }
            else {
                cout << "Error occured at position:" << b;
            }
            break;
        default:
            cout << "invalid input";
            break;
    }
    return 0;
}
