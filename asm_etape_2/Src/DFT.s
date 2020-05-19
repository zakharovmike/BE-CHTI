	thumb
		
	area moncode, code, readonly
	import TabCos
	import TabSin
	export dft_sum
		
dft_sum	proc
	push	{lr}
	push	{r4}
	push	{r5}
	push	{r6}
	; value of k in r0
	
	; calculate Re(k)
	ldr	r2, =TabCos
	bl	dft_pt
	mov	r12, r4		; temp store for Re(k)
	
	; calculate Im(k)
	ldr	r2, =TabSin
	bl	dft_pt
	mov	r1, r4		; temp store for Im(k)
	
	mov	r0, #0			; reset r0
	smull	r3, r0, r12, r12	; r0 = MSB(Re^2(k))
	smlal	r3, r0, r1, r1		; r0 += MSB(Im^2(k))
	; r0 = MSB(Re^2(k) + Im^2(k)) = M2(k)
	
	pop	{r6}
	pop	{r5}
	pop	{r4}
	pop	{pc}
	endp
		
dft_pt	proc	
	; initialize values
	mov	r3, #63		; r3 = N-1 = 64-1 = 63
	mov	r4, #0 		; r4 = partial sum
loop
	cmp	r3, #0
	blt	done
	mul	r5, r3, r0	; r5 = i*k
	and	r5, r5, #63 	; r5 = i*k % 63
	ldrsh	r5, [r2, r5, LSL #1]	; r5 = cos(i*k*2*pi/N)
	ldrsh	r6, [r1, r3, LSL #1]	; r6 = x(i)
	mla	r4, r5, r6, r4		; r4 += x(i) * cos(i*k*2*pi/N)
	sub	r3, r3, #1
	b loop
	
done
	bx	lr
	endp
		
	end