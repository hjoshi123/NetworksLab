#include<stdio.h>
#include<stdlib.h>

#define maxpackets 10

void leaky(int bmax, int rate) {
	int current_packet;
	int buffersize = 0;
	for (int i = 0; i < maxpackets; i++) {
		current_packet = rand();
		current_packet = (current_packet % bmax) + 50;
		printf ("Size of current packet is %d", current_packet);
		if (current_packet > bmax - buffersize) {
			printf ("\nInsufficient space, dropping packet\n");
		} else {
			buffersize += current_packet;
			printf ("\nPacket added to buffer with size %d \n", current_packet);
			if (buffersize >= rate) {
				buffersize -= rate;
				printf ("\nBytes sent is %d\n", rate);
			} else {
				printf ("\nBytes sent is buffersize %d\n", buffersize);
				buffersize = 0;
			}
			printf ("\nCurrent size of buffer is %d\n", buffersize);
		}
	}
	while (buffersize > 0) {
		if (buffersize >= rate) {
			buffersize -= rate;
			printf ("\nBytes sent is %d\n", rate);
			printf ("\nBuffer size is %d\n", buffersize);
		} else {
			printf ("\nBytes sent is %d\n", buffersize);
			printf ("\nNo more data to send\n");
			buffersize = 0;
		}
	}
}

int main() {
	int buffersize, outputrate;
	printf ("\nEnter buffersize and output rate\n");
	scanf ("%d %d", &buffersize, &outputrate);
	leaky(buffersize, outputrate);
	return 0;
}
