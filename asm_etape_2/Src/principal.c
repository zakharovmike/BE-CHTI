#include "gassp72.h"

#define N 64

extern unsigned short TabSig;

int squares(short i);
int dft_sum(short k, unsigned short *TabSig);

int main(void)
{	
	int arrM2[N];
	for (int k = 0; k < N; k++)
	{
		arrM2[k] = dft_sum(k, &TabSig);
	}
	
	while	(1)
	{
	}
}
