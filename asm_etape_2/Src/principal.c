#include "gassp72.h"

#define N 64

int squares(short i);
int dft_sum(short k);

int main(void)
{	
	// **** **** 2.1 **** ****
	// Test S = cos^2(i) + sin^2*(i) output
	/*
	int min = 1999999999;
	int max = -99;
	int x;
	for (int i = 0; i < 64; i++)
	{
		x = squares(i);
		if (x > max)
		{	
			max = x;
		}
		if (x < min)
		{
			min = x;
		}
	}
	*/
	// **** **** 2.1 **** ****
	
	// **** **** 2.2 **** ****
	int arrM2[N];
	for (int k = 0; k < N; k++)
	{
		arrM2[k] = dft_sum(k);
	}
	// **** **** 2.2 **** ****
	
	while	(1)
	{
	}
}
