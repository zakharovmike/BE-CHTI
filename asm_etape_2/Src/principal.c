#include "gassp72.h"

int squares(short i);

int main(void)
{
	// **** **** 2.1 **** ****
	// Test S = cos^2(i) + sin^2*(i) output
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
	// **** **** 2.1 **** ****

	while (1)
	{
	}
}
