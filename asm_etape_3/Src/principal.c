#include "gassp72.h"

#define N 64
#define M2TIR 0xF0B48 // Hit threshold @ 50 mV
#define HITS_TO_VALIDATE 12

int squares(short i);
int dft_sum(short k, volatile unsigned short dma_buf[]);

volatile unsigned short dma_buf[N];
int frequency_k[6] = {17, 18, 19, 20, 23, 24};
int hits_per_frequency[6] = {0, 0, 0, 0, 0, 0};
int hit_validated = 0;
int score[6] = {0, 0, 0, 0, 0, 0};

void sys_callback()
{
	// Profiling start
	// To count time of DMA + DFT + counter
	GPIO_Set(GPIOB, 1);
	
	// D�marrage DMA pour 64 points
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	// For each of the six frequencies
	int m2_k;
	for (int i = 0; i < 6; i++)
	{
		// Calculate its magnitude
		m2_k = dft_sum(frequency_k[i], dma_buf);
		
		// Check if magnitude exceeds threshold (i.e. counts as hit)
		if (m2_k >= M2TIR)
		{
			// Update hits counter for said frequency if that's the case
			hits_per_frequency[i]++;
			
			// Check if number of hits passes the hit validation threshold
			if (hits_per_frequency[i] == HITS_TO_VALIDATE)
			{
				hit_validated = 1;
				score[i]++;
			}
		}
		else
		{
			// Reset to zero otherwise
			hits_per_frequency[i] = 0;
		}
	}
	
	// Profiling end
	// ~0.36 ms to process
	GPIO_Clear(GPIOB, 1);
}

int main(void)
{		
	// activation de la PLL qui multiplie la fr�quence du quartz par 9
	CLOCK_Configure();
	// PA2 (ADC voie 2) = entr�e analog
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
	// PB1 = sortie pour profilage � l'oscillo
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// PB14 = sortie pour LED
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);

	// activation ADC, sampling time 1us
	Init_TimingADC_ActiveADC_ff( ADC1, 0x43 );
	Single_Channel_ADC( ADC1, 2 );
	// D�clenchement ADC par timer2, periode (72MHz/320kHz)ticks
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	// Config DMA pour utilisation du buffer dma_buf
	Init_ADC1_DMA1( 0, dma_buf );

	// Config Timer, p�riode exprim�e en p�riodes horloge CPU (72 MHz)
	Systick_Period_ff( 360000 ); // Interrupt every 360000 ticks <=> every 5 ms
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 3 est la priorit�, sys_callback est l'adresse de cette fonction
	Systick_Prio_IT( 3, sys_callback );
	SysTick_On;
	SysTick_Enable_IT;
	
	while	(1)
	{
		// Blink LED when one frequency has a validated hit
		if (hit_validated)
		{
			GPIO_Set( GPIOB, 14 );
			hit_validated = 0;
			GPIO_Clear( GPIOB, 14);
		}
	}
}
