#include <iostream>
#include <cstdio>

using namespace std;

struct node {
    unsigned dist[20];
    unsigned from[20];
}rt[10];

int main() {
    int costmat[20][20];
    int nodes, i, j, k, count = 0;
    cout << "Enter no of nodes \n";
    cin>> nodes;
    cout << "Enter the cost of matrix \n";
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            cin>> costmat[i][j];
            costmat[i][i] = 0;
            rt[i].dist[j] = costmat[i][j];
            rt[i].from[j] = j;
        }
    }
    do {
        count = 0;
        for(i = 0; i < nodes; i++)
        for(j = 0; j < nodes; j++)
        for(k = 0; k < nodes; k++)
            if(rt[i].dist[j]>costmat[i][k]+rt[k].dist[j]) {//We calculate the minimum distance
                rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
                rt[i].from[j]=k;
                count++;
            }
    } while (count != 0);
    for(i = 0; i < nodes; i++) {
        cout << ("\n\n For router ") << i+1 << "\n";
        for(j = 0; j < nodes; j++) {
            cout << "\nnode " << j+1 << " via "<<  rt[i].from[j] + 1  << " Distance "  << rt[i].dist[j];
        }
    }
    return 0;
}
