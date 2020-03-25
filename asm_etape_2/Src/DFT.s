	thumb
		
	area moncode, code, readonly
	import TabCos
	import TabSin
	; import Signal
	export dft_sum
		
dft_rl	proc
	push	{lr}
	push	{r4}
	push	{r5}
	push	{r6}
	; value of k in r0
	
	; initialize
	; r1 = N - 1 = 64-1 = 63
	mov	r1, #63
	ldr	r2, =Signal
	ldr	r3, =TabCos
	mov	r4, #0 ; output
	
loop
	cbz	r1, done
	and	r5, r0, r1 ; k % 63
	mul	r6, [r2, r1], [r3, r5] ;  x(i) * cos(ik)
	add	r4, r4, r6
	sub	r1, r1, #1
	b loop
	
done
	ldr	r0, r4
	pop	{r6}
	pop	{r5}
	pop	{r4}
	pop	{pc}
	endp
		
dft_im	proc
	push	{lr}

	pop	{pc}
	endp
		
dft_sum	proc
	push	{lr}

	pop	{pc}
	endp
		
	end