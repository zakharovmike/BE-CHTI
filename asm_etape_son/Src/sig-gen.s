; ce programme est pour l'assembleur RealView (Keil)
	thumb
	
	area madata, data, readwrite
	export counter
	
counter	dcd	1
		
	area  moncode, code, readonly
	export timer_callback
;
GPIOB_BSRR	equ	0x40010C10	; Bit Set/Reset register
	
timer_callback	proc
	push	{lr}
	
;	load current state
	ldr	r2, =counter
	ldr r0, [r2]

;	if 0, increment
	cbz	r0, increment
	
;	if 1, decrement
	cbnz	r0, decrement	
	
; mise a 1 de PB1
increment	ldr	r3, =GPIOB_BSRR
			mov	r1, #0x00000002
			str	r1, [r3]
;	update counter to 1 and save to memory
			mov r0, #0x00000001
			str r0, [r2]
			b	ending
	
; mise a zero de PB1
decrement	ldr	r3, =GPIOB_BSRR
			mov	r1, #0x00020000
			str	r1, [r3]
;	update counter to 0 and save to memory
			mov r0, #0x00000000
			str r0, [r2]
			b	ending
; N.B. le registre BSRR est write-only, on

ending	pop		{pc}
	endp
;
	end