#include <stdio.h>
#include <stdlib.h>

#define MAX 5
int pq[MAX];

int front, rear;

void create() {
	front = rear = -1;
}

void check(int data) {
    int i, j;
    for (i = 0; i <= rear; i++) {
        if (data >= pq[i]) {
            for (j = rear + 1; j > i; j--) {
                pq[j] = pq[j - 1];
            }
            pq[i] = data;
            return;
        }
    }
    pq[i] = data;
}

void insert(int data) {
	if (rear >= MAX - 1) {
		printf ("\nQueue Overflow\n");
		return;
	}
	if ((front == -1) || (rear == -1)) {
		front++;
		rear++;
		pq[rear] = data;
		return;
	} else check(data);
	rear++;
}

void delete(int data) {
	int i;
	if ((front == -1) || (rear == -1)) {
		printf ("\nQueue is empty");
		return;
	}
	for (i = 0; i <= rear; i++) {
		if (data == pq[i]) {
			for (; i < rear; i++) {
				pq[i] = pq[i + 1];
			}
			pq[i] = -99;
			rear--;
			if (rear == -1)
				front = -1;
			return;
		}
	}
	printf ("\n%d not found in queue to delete", data);
}

void display() {
	if ((front == -1) || (rear == -1)) {
		printf ("\nNothing to print");
		return;
	}
	for (; front <= rear; front++) {
		printf ("%d ", pq[front]);
	}
	front = 0;
}

int main() {
	int ch, n;
	printf ("\nEnter your choice: \n1:Insert \n2:Delete \n3:Display \n4:Exit\n");
	create();

	while (1) {
		scanf("%d", &ch);
		switch(ch) {
			case 1:
				printf ("\nEnter value to be inserted\n");
				scanf("%d", &n);
				insert(n);
				break;
			case 2:
				printf ("\nEnter element to be deleted\n");
				scanf("%d", &n);
				delete(n);
				break;
			case 3:
				display();
				break;
			case 4:
				exit(0);
			default:
				printf ("\nChoice wrong");
		}
	}
	return 0;
}

