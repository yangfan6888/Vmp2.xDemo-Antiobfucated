#pragma once
#include<iostream>
#include<Windows.h>

/*
vRip -> opcode stream opcode一个字节，因为用的寄存器是al

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

//在x64.asm中实现的函数
extern "C"
{
	//
	//2021.11.22
	//此函数废弃，不要使用
	//
	uint8_t decrypt_opcode(uint64_t vRip);
}
