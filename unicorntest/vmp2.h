#pragma once
#include<iostream>
#include<Windows.h>

/*
vRip -> opcode stream opcodeһ���ֽڣ���Ϊ�õļĴ�����al

opcode stream :1 2 3 4 5 6 7 8 end
								|
							  vRip


*/

/*
* 
rsi = vRip


*/

inline char opcode;

//
//.vmp0:0000000140008900                 lea     r12, vmp_dispatch_handler_table
//
inline uint64_t* vmp_dispatch_table = (uint64_t*)0x14000644B;

//��x64.asm��ʵ�ֵĺ���
extern "C"
{
	//
	//2021.11.22
	//�˺�����������Ҫʹ��
	//
	uint8_t decrypt_opcode(uint64_t vRip);
}
