#include "gassp72.h"

void timer_callback(void);

int main(void)
{	
	// activation de la PLL qui multiplie la fréquence du quartz par 9
	CLOCK_Configure();
	// config port PB1 pour être utilisé en sortie
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// initialisation du timer 4
	// Periode_en_Tck doit fournir la durée entre interruptions,
	// exprimée en périodes Tck de l'horloge principale du STM32 (72 MHz)
	int Periode_en_Tck = 72000;
	/*
	 * microprocessor's clock goes at 72 MHz (72 000 000 ticks / sec)
	 * Periode_en_Tck is the number of ticks until an interuption
	 * ex: PeT=72000 -> interuption every 72000 ticks,
	 * which means 72 000 000 / 72000 = 1000 interups per sec
	 * since we need 2 interupts per cycle (one for every switch between 1 and 0)
	 * means we get a frequency of 500 Hz
	 * PeT=360000 -> 100Hz
	 * PeT=1800 -> 20kHz
	 */
	Timer_1234_Init_ff( TIM4, Periode_en_Tck );
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 2 est la priorité, timer_callback est l'adresse de cette fonction, a créér en asm,
	// cette fonction doit être conforme à l'AAPCS
	Active_IT_Debordement_Timer( TIM4, 2, timer_callback );
	// lancement du timer
	Run_Timer( TIM4 );
	
	while	(1)
	{
	}
}
