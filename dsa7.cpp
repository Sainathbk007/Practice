#include <iostream>
#include <string>
using namespace std;
void primsAlgorithm(int adj_mat[][10], int n) {
    int visit[10] = {0};
    int mincost = 0;
    int min, row, col;
    cout << "Enter the starting vertex (0 to " << n-1 << "): ";
    int s;
    cin >> s;
    if (s < 0 || s >= n) {
        cout << "Invalid starting vertex." << endl;
        return;
    }
    visit[s] = 1;
    for (int k = 1; k < n; k++) {
        min = 999;
        for (int i = 0; i < n; i++) {
            if (visit[i] == 1) {
                for (int j = 0; j < n; j++) {
                    if (visit[j] == 0 && adj_mat[i][j] != -1) {
                        if (adj_mat[i][j] < min) {
                            min = adj_mat[i][j];
                            row = i;
                            col = j;
                        }
                    }
                }
            }
        }
        cout << "Selected Edge in MST is (" << row << ", " << col << ") with cost " << min << endl;
        mincost += min;
        visit[col] = 1;
        adj_mat[row][col] = adj_mat[col][row] = -1; // Mark the edge as visited
    }
    cout << "Total Minimum Cost is " << mincost << endl;
}
int main() {
    int row, cal, w;
    cout << "Enter the number of Offices: ";
    cin >> row;
    cal = row;
    int adj_mat[10][10];
    string city[10];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < cal; j++) {
            adj_mat[i][j] = -1; // Initialize with -1 indicating no connection
        }
    }
    for (int i = 0; i < row; i++) {
        cout << "Enter the location of Office: " << i + 1 << ": ";
        cin >> city[i];
    }
    for (int i = 0; i < row; i++) {
        for (int j = i + 1; j < cal; j++) {
            cout << "Enter phone line cost between " << city[i] << " & " << city[j] << " (enter -1 if no connection): ";
            cin >> w;
            adj_mat[i][j] = adj_mat[j][i] = w;
        }
    }
    cout << "The adjacency matrix is: " << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < cal; j++) {
            cout << adj_mat[i][j] << " ";
        }
        cout << endl;
    }
    primsAlgorithm(adj_mat, row);
    return 0;
}