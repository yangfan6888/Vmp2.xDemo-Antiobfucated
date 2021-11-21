#include"unicorn_handler.h"
#include"capstone/capstone.h"
#include"vmp2.h"
#include"global.h"
#include<iostream>

using namespace std;

extern csh cs;

static cs_insn *gpcs_ins;

void hook_mem64(uc_engine* uc, uc_mem_type type,
    uint64_t address, int size, int64_t value, void* user_data)
{
    //
    //�����ܽ��ֵ�type��Ҫ��main��������uc_hook_add����
    //
    switch (type) {
    case UC_MEM_READ:

#if 0
        cout << "MEM READ at address " << address << endl;
#endif 

        break;
    case UC_MEM_WRITE:

#if 0
        cout << "MEM WRITE at address " << address << endl;
#endif 

        break;

    case UC_MEM_WRITE_UNMAPPED:
        cout << "[FATAL ERROR]MEM WRITE UNMAPPED at address 0x" << address << endl;
        break;

    case UC_MEM_READ_UNMAPPED:
        cout << "[FATAL ERROR]MEM READ UNMAPPED at address 0x" << address << endl;
        break;
    case UC_MEM_FETCH_UNMAPPED:
        /*
        * �����漸�ֿ��ܣ�
          1.ִ�е�API���ã����ʵ�����dll����ȥ
          2.
        */
        cout << "[FATAL ERROR]MEM FETCH UNMAPPED at address 0x" << address << endl;
#if 1
        uc_reg_read(uc, X86_REG_RIP, &emu_ctx.Rip);
        cs_disasm(cs, (uint8_t*)emu_ctx.Rip, 15, (uint64_t)0, 0, &gpcs_ins);
        cout << hex << address << " : " << gpcs_ins->mnemonic << "  " << gpcs_ins->op_str << endl;
#endif
        break;
    }
}

// callback for tracing instruction
void hook_code(uc_engine* uc, uint64_t address, uint32_t size, void* user_data)
{
    //
    //��reg���µ�emu_ctx�ڣ���Ȼ���Ĵ���������,���ǿ��ܻ��з���Ч������
    //
    uc_reg_read(uc, X86_REG_RAX, &emu_ctx.Rax);
    uc_reg_read(uc, X86_REG_RBX, &emu_ctx.Rbx);
    uc_reg_read(uc, X86_REG_RCX, &emu_ctx.Rcx);
    uc_reg_read(uc, X86_REG_RDX, &emu_ctx.Rdx);
    uc_reg_read(uc, X86_REG_RBP, &emu_ctx.Rbp);
    uc_reg_read(uc, X86_REG_RSP, &emu_ctx.Rsp);
    uc_reg_read(uc, X86_REG_RSI, &emu_ctx.Rsi);
    uc_reg_read(uc, X86_REG_RDI, &emu_ctx.Rdi);
    uc_reg_read(uc, X86_REG_R8, &emu_ctx.R8);
    uc_reg_read(uc, X86_REG_R9, &emu_ctx.R9);
    uc_reg_read(uc, X86_REG_R10, &emu_ctx.R10);
    uc_reg_read(uc, X86_REG_R11, &emu_ctx.R11);
    uc_reg_read(uc, X86_REG_R12, &emu_ctx.R12);
    uc_reg_read(uc, X86_REG_R13, &emu_ctx.R13);
    uc_reg_read(uc, X86_REG_R14, &emu_ctx.R14);
    uc_reg_read(uc, X86_REG_R15, &emu_ctx.R15);

    //
    //x86һ���һ��ָ��15�ֽ�
    //
    
    cs_disasm(cs, (uint8_t*)address, 15, (uint64_t)0, 0, &gpcs_ins);


#if 0 //�����ʱ�����/��¼ÿ��ָ��
    cout << hex << address << " : " << gpcs_ins->mnemonic << "  " << gpcs_ins->op_str << endl;
#endif

    //
    //ָ����ַ����
    //
#if 0
    if (address == 0x140001354)
    {
        DebugBreak();
    }
#endif

    //
    //ƥ�� 0x14001ff6d "mov     al, [rsi-1]"
    //����ص���vmpѭ����ȡopcode��Ȼ�����opcode�ĵط�
    //
#if 1
    if ((gpcs_ins->detail->x86.operands[0].type == X86_OP_REG)&& 
        (gpcs_ins->detail->x86.operands[0].reg == X86_REG_AL)&& 
        !_stricmp(gpcs_ins->mnemonic,"mov")&&
        (gpcs_ins->detail->x86.operands[1].mem.base == X86_REG_RSI))
    {
        printf("vRip = %llx\n", emu_ctx.Rsi);

        uint8_t op = decrypt_opcode(emu_ctx.Rsi);
        //printf("%x\n", op);

        auto disp_des = vmp_dispatch_table[op];
        printf("vmp dispatch handler at %llx\n", --disp_des);


        uc_emu_stop(uc);     
    }
#endif






}
