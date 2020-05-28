; ce programme est pour l'assembleur RealView (Keil)
	thumb
	
	area moncode, code, readonly
	include etat.inc
	import sound_state
		
	export timer_callback

TIM3_CCR3	equ	0x4000043C	; PWM register
	
timer_callback	proc
	push	{lr}
	
	; Retrieve sound state
	ldr	r0, =sound_state	; r0 = address to sound_state
	ldr r1, [r0, #E_POS]	; r1 = current sample position from first sample
	ldr r2, [r0, #E_TAI]	; r2 = total number of samples
	
	; Check if there are samples left to emit
	cmp	r2, r1
	beq done
	
	; Retrieve sound data
	ldr r3, [r0, #E_RES]	; r3 = PWM resolution
	ldr r2, [r0, #E_SON]	; r2 = address to first sound sample value
	
	; Adapt sound to output
	ldrsh	r2, [r2, r1, LSL #1]	; r2 = sample value at current position
	add		r2, #32768				; add offset so sample value is always positive
	mul		r2, r3					; apply PWM resolution scale factor
	lsr		r2, #16					; normalize to [0:1637] (divide by 65536)
	
	; Output to PWM
	ldr	r3, =TIM3_CCR3	; r3 = address to PWM output register
	str r2, [r3]		; write sample value to PWM output register
	
	; Update current sample position
	add	r1, #1				; increment position to next sample
	str r1, [r0, #E_POS]	; save change into global sound state
	
done	
	pop		{pc}
	endp

	end