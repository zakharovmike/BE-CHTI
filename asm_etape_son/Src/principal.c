#include "gassp72.h"
#include "etat.h"

#define TCK_PER_MICROSEC 72

// sound.s
extern void timer_callback(void);

// bruitverre.asm
extern int LongueurSon;
extern int PeriodeSonMicroSec;
extern int Son;

// Global container for information about the sound
type_etat sound_state;

int main(void)
{
	// Initialize sound state
	sound_state.position = 0;
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
	
	// activation de la PLL qui multiplie la fréquence du quartz par 9
	CLOCK_Configure();
	
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
	
	while	(1)
	{
	}
}
