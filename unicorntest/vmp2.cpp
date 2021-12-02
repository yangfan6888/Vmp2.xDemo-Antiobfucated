#include"include/unicorn/unicorn.h"
#include"vmp2.h"
#include<intrin.h>
#include<assert.h>
#include"global.h"

#include<unordered_map>

extern uc_engine* uc;

std::unordered_map<uint32_t, const char*> umap
{
	{0x14FE10,"unknow"} ,{0x14FE18,"RAX"},{0x14FE20,"RDX"},
	{0x14FE28,"R12"},{0x14FE30,"R9"},{0x14FE38,"R15"},{0x14FE40,"R11"},{0x14FE48,"RBX"},
	{0x14FE50,"RCX"},{0x14FE58,"RBP"},{0x14FE60,"R14"},{0x14FE68,"R8"},{0x14FE70,"RBP"},
	{0x14FE78,"RSI"},{0x14FE80,"RDI"},{0x14FE88,"R13"},{0x14FE90,"RDX"},{0x14FE98,"R10"},
	{0x14FEA0,"RAX"},{0x14FEA8,"RFALGS"},{0x14FEB0,"RIP"},{0x14FEB8,"VKEY"}
};

void vm::vpop(uint64_t offset)
{
	//8字节对齐,不是的话可能就有问题
	assert(!(offset % 8));
	
	//换成十进制方便看
	std::cout << std::dec;
	std::cout << "vPop vR" << offset / 8 << std::endl;
	std::cout << std::hex;
}

void vm::vpop_to_physical_reg()
{
	vmp_stack* vs = nullptr;
	uint64_t rip = -1;

	std::cout << "pop all virtual regs to physical regs(vm exited) ";

	vs = (decltype(vs))emu_ctx.Rbp;
	uc_mem_read(uc, (uint64_t) & (vs->RIP), &rip, sizeof(void*));

	std::cout << "Physical RIP " << rip << std::endl;

	//
	//根据我们的rip指向的代码需要什么寄存器，恢复代码的时候也要把需要的恢复
	//第一次的rip只需要恢复RCX
	//
	uc_mem_read(uc, (uint64_t) & (vs->RCX), &rip, sizeof(void*));
	std::cout << "Physical RCX " << rip << std::endl;

}

void vm::vpush(uint64_t offset)
{
	assert(!(offset % 8));

	//换成十进制方便看
	std::cout << std::dec;
	std::cout << "vPush vR" << offset / 8 << std::endl;
	std::cout << std::hex;
}

void vm::vpushImm(uint32_t imm)
{
	std::cout << "vPush imm32\n";
}

void vm::vpushImm(uint64_t imm)
{
	std::cout << "vPush imm64\n";
}

void vm::vadd()
{
	std::cout << "vAdd imm\n";
}

