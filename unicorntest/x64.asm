

.CODE


decrypt_opcode PROC
	push rsi
	push rbx
	
	mov rsi,rcx
	mov rbx,rsi
	mov al,[rsi-1]
	xor al,bl
	inc al
	xor al,0E5h
	ror al,3
	movzx rax, al
	
	pop rbx
	pop rsi
	
	ret
decrypt_opcode ENDP














END