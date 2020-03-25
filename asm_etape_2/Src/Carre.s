	thumb
		
	area moncode, code, readonly
	import TabCos
	import TabSin
	export squares
	
	
squares	proc
	push	{lr}
	; angle i is in r0
	
	ldr	r1, =TabCos
	
	; retrieve cos(i) into r2
	ldrsh	r2, [r1, r0, LSL #1]
	; calculate cos^2
	mul 	r2, r2, r2
	
	ldr	r1, =TabSin
	
	; retrieve sin(i) into r3
	ldrsh	r3, [r1, r0, LSL #1]
	; calculate sin^2 + cos^2 into return register r0
	mla	r0, r3, r3, r2
	
	pop	{pc}
	endp
	
	end