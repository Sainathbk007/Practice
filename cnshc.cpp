#include<iostream>
using namespace std;
int main() {
    int a;
    cout << "who are you?? 1.Sender 2.Reciver.:";
    cin >> a;
    int a1[4], a2[7];
    switch (a) {
        case 1:
            cout << "Enter the 4-bit data bit:";
            for (int i =0; i <4; i++) {
                cin >> a1[i];
            }
            a2[4] =a1[0];
            a2[2] =a1[1];
            a2[1] =a1[2];
            a2[0] =a1[3];
            a2[6] =(a2[4]^a2[2])^a2[0];
            a2[5] =(a2[4]^a2[1])^a2[0];
            a2[3] =(a2[2]^a2[1])^a2[0];
            cout << "Code word at sender side is:";
            for (int j =0; j <7; j++) {
                cout << a2[j] << " ";
            }
            cout << endl;
            break;
        case 2:
            int b, a3[7], c1, c2, c3;
            cout << "Enter the code word recived from senders side:";
            for (int k =0; k <7; k++) {
                cin >> a3[k];
            }
            c1 =a3[6]^a3[4]^a3[2]^a3[0];
            c2 =a3[5]^a3[4]^a3[1]^a3[0];
            c3 =a3[3]^a3[2]^a3[1]^a3[0];
            b =(c3*4)+(c2*2)+(c1*1);
            if (b ==0) {
                cout << "No error in CRC process.";
            }
            else {
                cout << "Error occured at position:" << 7-b << endl;
                a3[7-b] =a3[7-b]^1;
                cout << "Correct code word:";
                for (int l =0; l <7; l++) {
                    cout << a3[l] << " ";
                }
            }
            cout << endl;
            break;
        default:
            cout << "invalid input";
            break;
    }
    return 0;
}
