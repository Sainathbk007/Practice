#include <iostream> 
using namespace std; 
 
void constructorOBST(float p[], float q[], int n, float c[][20], int r[][20], float w[][20]) 
{     
    for (int i = 0; i <= n; ++i) 
    {              
        c[i][i] = 0;         
        r[i][i] = 0;         
        w[i][i] = q[i]; 
    } 
 
    for (int len = 1; len <= n; ++len) 
    {         
        for (int i = 0; i <= n - len; ++i) 
        { 
            int j = i + len;             
            w[i][j] = p[j] + q[j] + w[i][j - 1];             
            c[i][j] = 9999; 
            for (int k = i + 1; k <= j; ++k) 
            { 
                float cost = c[i][k - 1] + c[k][j] + w[i][j];                 
                if (cost < c[i][j]) 
                { 
                    c[i][j] = cost;                     
                    r[i][j] = k; 
                } 
            } 
        } 
    } 
} 
 
void printOBST(int r[][20], int i, int j) 
{ 
    if (i >= j)     
    {         
        return;     
    } 
    int root = r[i][j]; 
    cout << "Root of subtree[" << i << "," << j << "] is key " << root << endl; 
    if (i < root - 1) 
    { 
        cout << "Left child of " << root << ": "; 
        printOBST(r, i, root - 1); 
    }     
    if (root < j) 
    { 
        cout << "Right child of " << root << ": ";         
        printOBST(r, root, j); 
    } 
} 
 
int main() 
{     
    int n; 
    cout << "Enter number of keys: ";     
    cin >> n;  
    float p[20];     
    float q[20]; 
    cout << "Enter probability for successful search (p1 to p" << n << "):\n";     
    for (int i = 1; i <= n; ++i) 
    { 
        cin >> p[i]; 
    } 
    cout << "Enter probability for unsuccessful search (q0 to q" << n << "):\n";     
    for (int i = 0; i <= n; ++i) 
    { 
        cin >> q[i]; 
    } 
    float c[20][20] = {0};     
    int r[20][20] = {0}; 
    float w[20][20] = {0}; 
    constructorOBST(p, q, n, c, r, w); 
    cout << "\nOptimal BST Weight: " << w[0][n] << endl;     
    cout << "\nOptimal BST Cost: " << c[0][n] << endl;     
    cout << "\nRoot of Optimal BST [0][" << n << "]: " << r[0][n] << endl;     
    cout << "\nTree structure: \n"; 
    printOBST(r, 0, n); 
    return 0; 
} 
