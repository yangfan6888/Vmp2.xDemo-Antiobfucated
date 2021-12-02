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
rdi = vStack or vContext

*/

struct vmp_stack
{
	uint64_t RAX;
	uint64_t RDX;
	uint64_t R12;
	uint64_t R9;
	uint64_t R15;
	uint64_t R11;
	uint64_t RBX;
	uint64_t RCX;
	uint64_t RBP;
	uint64_t R14;
	uint64_t R8;
	uint64_t RSI;
	uint64_t RSI2;
	uint64_t RDI;
	uint64_t R13;
	uint64_t RDX2;
	uint64_t R10;
	uint64_t RAX2;
	uint64_t RFLAGS;
	uint64_t RIP;
	uint64_t vKEY;
};

class vm
{
public:
	vm() = default;

	static vm* get_instance() {
		if (!m_instance)
			m_instance = new vm;
		return m_instance;
	}

	static vm* m_instance;

	//
	//vrsp(物理寄存器RBP)
	//
	const uint64_t vrsp_limit_low = 0x14FE10;
	const uint64_t vrsp_limit_high = 0x14FEB8;
	
	uint64_t vrsp;//虚拟机的栈  



	
	//
	//0x14FE10 - 0x14FCD0 = 0x28(40)
	//vmp2最多28个虚拟寄存器
	//
	uint64_t vReg[0x28]{};
	
	//
	//		mov     rdx, [rbp+0]
	//		add     rbp, 8
	// 	    mov     [rax+rdi], rdx
	//	    这条指令占1个字节
	void vpop(uint64_t offset);

	//
	//		mov     rsp, rbp
	//      pop		rax
	//		pop		rdx
	// 	    pop		r12
	// 		pop     ...
	//		占1个字节，把堆栈上的寄存器全都还原到物理寄存器上，然后虚拟机退出
	void vpop_to_physical_reg();

	//
	void vpush(uint64_t offset);

	//
	// 	    mov     eax, [rsi-4]
	//      xxxxxx解密eax
	//      xor     [rsp], eax  这个是干嘛的？
	//      sub     rbp, 8
	// 	    mov     [rbp+0], rax
	// 
	//	    这条指令占5个字节(rsi->rsi-4)
	void vpushImm(uint32_t imm);


// 
//	    这条指令占9个字节(rsi->rsi-8)
	void vpushImm(uint64_t imm);

	//
	//      mov     rax, [rbp+0]
	//      add     [rbp+8], rax
	//      pushfq
	// 	    pop     qword ptr [rbp+0]
	//      占一个字节，将栈顶和栈顶下一个数相加放在栈顶下一位，栈顶放rflags
	void vadd();



};

inline vm* vm::m_instance = nullptr;

//在x64.asm中实现的函数
extern "C"
{
	//
	//有些handle进入的时候会对opcode运算，然后获得在虚拟栈上的索引，并赋值
	//
	uint8_t opcode_to_reg_index(uint8_t opcode);


}
