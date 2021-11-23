

.CODE


;
;
;从opcode解密到索引
;
decrypt_opcode PROC
	push rsi
	push rbx
	
	mov rsi,rcx
	mov rbx,rcx
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


opcode_to_reg_index PROC
	mov eax,eax
	mov rax,rcx
	not al 
	add al,7Ch
	neg al
	and al,0F8h
	ret
opcode_to_reg_index ENDP














END