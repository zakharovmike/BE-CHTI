; ce programme est pour l'assembleur RealView (Keil)
	thumb
	
	area moncode, code, readonly
	include etat.inc
	import sound_state
		
	export timer_callback

TIM3_CCR3	equ	0x4000043C	; PWM register
	
timer_callback	proc
	push	{lr}
	
	add r10, #1
	
	pop		{pc}
	endp

	end