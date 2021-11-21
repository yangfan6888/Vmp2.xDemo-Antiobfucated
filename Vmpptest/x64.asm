;http://vmpsoft.com/support/user-manual/working-with-vmprotect/preparing-a-project/using-markers/
;https://vmpsoft.com/support/user-manual/




.CODE 

Entry PROC
	sub rsp,20h
	mov qword ptr [rcx],2222h
	add rax,1
	sub rax,2
	inc rax
	add rsp,20h
	ret
Entry ENDP




END