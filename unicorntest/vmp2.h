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
	//vrsp(����Ĵ���RBP)
	//
	const uint64_t vrsp_limit_low = 0x14FE10;
	const uint64_t vrsp_limit_high = 0x14FEB8;
	
	uint64_t vrsp;//�������ջ  



	
	//
	//0x14FE10 - 0x14FCD0 = 0x28(40)
	//vmp2���28������Ĵ���
	//
	uint64_t vReg[0x28]{};
	
	//
	//		mov     rdx, [rbp+0]
	//		add     rbp, 8
	// 	    mov     [rax+rdi], rdx
	//	    ����ָ��ռ1���ֽ�
	void vpop(uint64_t offset);

	//
	//		mov     rsp, rbp
	//      pop		rax
	//		pop		rdx
	// 	    pop		r12
	// 		pop     ...
	//		ռ1���ֽڣ��Ѷ�ջ�ϵļĴ���ȫ����ԭ������Ĵ����ϣ�Ȼ��������˳�
	void vpop_to_physical_reg();

	//
	void vpush(uint64_t offset);

	//
	// 	    mov     eax, [rsi-4]
	//      xxxxxx����eax
	//      xor     [rsp], eax  ����Ǹ���ģ�
	//      sub     rbp, 8
	// 	    mov     [rbp+0], rax
	// 
	//	    ����ָ��ռ5���ֽ�(rsi->rsi-4)
	void vpushImm(uint32_t imm);


// 
//	    ����ָ��ռ9���ֽ�(rsi->rsi-8)
	void vpushImm(uint64_t imm);

	//
	//      mov     rax, [rbp+0]
	//      add     [rbp+8], rax
	//      pushfq
	// 	    pop     qword ptr [rbp+0]
	//      ռһ���ֽڣ���ջ����ջ����һ������ӷ���ջ����һλ��ջ����rflags
	void vadd();



};

inline vm* vm::m_instance = nullptr;

//��x64.asm��ʵ�ֵĺ���
extern "C"
{
	//
	//��Щhandle�����ʱ����opcode���㣬Ȼ����������ջ�ϵ�����������ֵ
	//
	uint8_t opcode_to_reg_index(uint8_t opcode);


}
