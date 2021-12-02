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
#if 1
        uc_reg_read(uc, X86_REG_RIP, &emu_ctx.Rip);
        cs_disasm(cs, (uint8_t*)emu_ctx.Rip, 15, (uint64_t)0, 0, &gpcs_ins);
        cout << hex << emu_ctx.Rip << " : " << gpcs_ins->mnemonic << "  " << gpcs_ins->op_str << endl;
#endif
        break;

    case UC_MEM_READ_UNMAPPED:
        cout << "[FATAL ERROR]MEM READ UNMAPPED at address 0x" << address << endl;
#if 1
        uc_reg_read(uc, X86_REG_RIP, &emu_ctx.Rip);
        cs_disasm(cs, (uint8_t*)emu_ctx.Rip, 15, (uint64_t)0, 0, &gpcs_ins);
        cout << hex << emu_ctx.Rip << " : " << gpcs_ins->mnemonic << "  " << gpcs_ins->op_str << endl;
#endif
        break;
    case UC_MEM_FETCH_UNMAPPED:
        /*
        * �����漸�ֿ��ܣ�
          1.ִ�е�API���ã����ʵ�����dll����ȥ
          2.
        */
        //cout << "[FATAL ERROR]MEM FETCH UNMAPPED at address 0x" << address << endl;
#if 1
        uc_reg_read(uc, X86_REG_RIP, &emu_ctx.Rip);
    
        //��ִ�е��������ָ��ǰ���Ѿ�������ָ����
        cout << hex << emu_ctx.Rip << " : " << gpcs_ins->mnemonic << "  " << gpcs_ins->op_str << endl;
#endif

        uc_emu_stop(uc);
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

    //dispatch handler��Ŀ�ĵ�
    static uint64_t disp = 0;

    //
    //x86һ���һ��ָ��15�ֽ�
    //
    //�Ե�ǰָ��������࣬����gpcs_ins
    cs_disasm(cs, (uint8_t*)address, 15, (uint64_t)0, 0, &gpcs_ins);


#if 0 //�����ʱ�����/��¼ÿ��ָ��
    cout << hex << address << " : " << gpcs_ins->mnemonic << "  " << gpcs_ins->op_str << endl;
#endif

    //
    //ָ����ַ����
    //
#if 0
    if (address == 0x140008998)
    {
        DebugBreak();
    }
#endif

    //
    //ƥ�� 0x14001ff6d "mov     al, [rsi-1]"
    //����ص���vmpѭ����ȡopcode��Ȼ�����opcode�ĵط�
    //
#if 0 //vmp2
    if ((gpcs_ins->detail->x86.operands[0].type == X86_OP_REG)&& 
        (gpcs_ins->detail->x86.operands[0].reg == X86_REG_AL)&& 
        !_stricmp(gpcs_ins->mnemonic,"mov")&&
        (gpcs_ins->detail->x86.operands[1].mem.base == X86_REG_RSI))
    {
        printf("vRip = %llx\n", emu_ctx.Rsi);
        //uc_emu_stop(uc);     
    }
#endif


#if 1 //vmp2
    //
    //��ȷƥ��MOV RDX, QWORD PTR DS:[R12+RAX*8]��Ѱ�Ҵ˴ε�dispatch hanlder
    //
    if ((gpcs_ins->detail->x86.operands[0].type == X86_OP_REG) &&
        (gpcs_ins->detail->x86.operands[0].reg == X86_REG_RDX) &&
        (gpcs_ins->detail->x86.operands[1].mem.base == X86_REG_R12) &&
        (gpcs_ins->detail->x86.operands[1].mem.index == X86_REG_RAX) &&
        (gpcs_ins->detail->x86.operands[1].mem.scale == 8))
    {

        uc_mem_read(uc, emu_ctx.R12 + emu_ctx.Rax * 8, &disp, 8);
#if 0
        printf(
            "vRip = %llx Opcode(Index) = %llx Dispatch Handler = %llx\n",
            emu_ctx.Rsi,
            emu_ctx.Rax,
            disp);

#endif

        //
        //ƥ��ÿ��handler
        //
        if (0x1400074fc == disp - 1)
        {
            vm::get_instance()->vpop(opcode_to_reg_index(emu_ctx.Rax));
        }
        else if (0x1400072b1 == disp - 1)
        {
            vm::get_instance()->vpushImm((uint32_t)0);
        }
        else if (0x140007eb1 == disp - 1)
        {
            vm::get_instance()->vadd();
        }
        else if (0x140009589 == disp - 1)
        {
            vm::get_instance()->vpushImm((uint64_t)0);
        }
        else if (0x1400077c3 == disp - 1)
        {
            vm::get_instance()->vpush(opcode_to_reg_index(emu_ctx.Rax));
        }
        else if (0x14000784F == disp - 1)
        {
            vm::get_instance()->vpop_to_physical_reg();
            uc_emu_stop(uc);
        }
        else {            //���ƥ�䵽��vmp2��dispatch handler�����ǲ�û�д���
            DebugBreak();
        }


#endif



    }





    
}
