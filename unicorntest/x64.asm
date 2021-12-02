

.CODE

;
;mov     [rax+rdi], rdx
;
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