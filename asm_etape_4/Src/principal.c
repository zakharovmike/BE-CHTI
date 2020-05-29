#include "gassp72.h"
#include "etat.h"

#define N 64
#define M2TIR 0xF0B48 // Hit threshold @ 50 mV
#define HITS_TO_VALIDATE 12
#define TCK_PER_MICROSEC 72

// DFT.s
extern int dft_sum(short k, volatile unsigned short dma_buf[]);

// sound.s
extern void timer_callback(void);

// bruitverre.asm
extern int LongueurSon;
extern int PeriodeSonMicroSec;
extern int Son;

// Global container for information about the sound
type_etat sound_state;

// Globals for hit detection and score counting
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
				sound_state.position = 0;
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

	// **********************************************
	// ========= INITIALIZE SOUND EMISSION ==========
	// **********************************************
	
	// Initialize sound state
	sound_state.position = LongueurSon; // Prevent sound emisssion until requested by validated hit
	sound_state.taille = LongueurSon;
	sound_state.son = &Son;
	
	// Microprocessor's clock goes at 72 MHz (72 000 000 ticks / sec)
	// Otherwise expressed as 72 ticks / microsecond
	// We want to play a sample every 91st microsecond
	// Therefore, we play a sample every 91*72 ticks
	sound_state.periode_ticks = TCK_PER_MICROSEC * PeriodeSonMicroSec;
	
	// PWM modulator must work at a frequency sufficiently larger than audible range (~20 kHz)
	// For best results, use a frequency that is an exact multiple of sound sample frequency
	// The sound is sampled @ 10989 Hz (91 microsec), so we'll use 43956 Hz for the modulator (x4 multiple)
	// 43956 Hz -> 22.75 microsec.
	int Pediode_PWM_en_Tck = TCK_PER_MICROSEC * 22.75; // 1638
	
	// config port PB0 pour être utilisé par TIM3-CH3
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	// config TIM3-CH3 en mode PWM
	sound_state.resolution = PWM_Init_ff( TIM3, 3, Pediode_PWM_en_Tck );
	TIM3->CCR3 = sound_state.resolution / 2; // Set sound output to silence as soon as the resolution is known
	
	// initialisation du timer 4
	// Periode_en_Tck doit fournir la durée entre interruptions,
	// exprimée en périodes Tck de l'horloge principale du STM32 (72 MHz)
	Timer_1234_Init_ff( TIM4, sound_state.periode_ticks );
	
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 2 est la priorité, timer_callback est l'adresse de cette fonction, a créér en asm,
	// cette fonction doit être conforme à l'AAPCS
	Active_IT_Debordement_Timer( TIM4, 2, timer_callback );
	
	// lancement des timers
	Run_Timer( TIM3 );
	Run_Timer( TIM4 );
	
	// **********************************************
	// **********************************************
	
	// **********************************************
	// ========= INITIALIZE DFT CALCULATION =========
	// **********************************************
	
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
	
	// **********************************************
	// **********************************************
	
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
