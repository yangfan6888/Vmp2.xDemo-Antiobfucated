#include "include/unicorn/unicorn.h"
#include "capstone/capstone.h"
#include <iostream>
#include <windows.h>
#include <assert.h>
#include"unicorn_handler.h"
#include"global.h"

using namespace std;

uc_engine* uc;
csh cs;

uint64_t InitRax = 0x00000001401BC77A;
uint64_t InitRbx = 0;
uint64_t InitRcx = 0x00000000002DC000;
uint64_t InitRdx = 0x00000001401BC77A;
uint64_t InitRbp = 0;
uint64_t InitRsp = 0x000000000014FF28;
uint64_t InitRsi = 0;
uint64_t InitRdi = 0;
uint64_t InitR8 = 0x00000000002DC000;
uint64_t InitR9 = 0x00000001401BC77A;
uint64_t InitR10 = 0;
uint64_t InitR11 = 0;
uint64_t InitR12 = 0;
uint64_t InitR13 = 0;
uint64_t InitR14 = 0;
uint64_t InitR15 = 0;

int main()
{
    uc_err err;
    cs_err cs_err;

    DWORD size_of_image = 0;

    //注意entry_point只是一个四字节的偏移
    DWORD entry_point = 0;

    cout << hex;

    err = uc_open(UC_ARCH_X86, UC_MODE_64, &uc);
    if (err) {
        printf("Failed on uc_open() with error returned: %u\n", err);
        return -1;
    }

    cs_err = cs_open(CS_ARCH_X86, CS_MODE_64, &cs);
    if (cs_err) {
        printf("Failed on cs_open() with error returned: %u\n", err);
        return -1;
    }

    cs_option(cs, CS_OPT_DETAIL, CS_OPT_ON);

    auto map_base = LoadLibraryExW(wpacked_file, 0,0);
    assert(map_base == (decltype(map_base))0x140000000);

    //
    //获取映像大小
    //
    for (char* p = (char*)map_base;; p++)
    {
        DWORD* tmp = (DWORD*)p;
        if (*tmp == 0x1000 && *(DWORD*)(++tmp) == 0x200) {
            size_of_image = *(DWORD*)(p + 0x18);
            entry_point = *(DWORD*)(p - 0x10);
            break;
        }
    }

    uc_mem_map(uc, (uint64_t)map_base, size_of_image, UC_PROT_ALL);

    //将我们的这个vmp packed文件全部映射进去，内存状况就像它本身自己在运行一样
    if (err = (uc_mem_write(uc, (uint64_t)map_base, map_base, size_of_image))) {
        printf("Failed to write emulation code to memory with err %u:%s!\n", err, uc_strerror(err));
        return -1;
    }


    //选择此时的Rsp
    uc_reg_write(uc, UC_X86_REG_RSP, &InitRsp);

    //其他初始的寄存器
    uc_reg_write(uc, UC_X86_REG_RAX, &InitRax);
    uc_reg_write(uc, UC_X86_REG_RBX, &InitRbx);
    uc_reg_write(uc, UC_X86_REG_RCX, &InitRcx);
    uc_reg_write(uc, UC_X86_REG_RDX, &InitRdx);
    uc_reg_write(uc, UC_X86_REG_RBP, &InitRbp);
    uc_reg_write(uc, UC_X86_REG_RSI, &InitRsi);
    uc_reg_write(uc, UC_X86_REG_RDI, &InitRdi);
    uc_reg_write(uc, UC_X86_REG_R8, &InitR8);
    uc_reg_write(uc, UC_X86_REG_R9, &InitR9);
    uc_reg_write(uc, UC_X86_REG_R10, &InitR10);
    uc_reg_write(uc, UC_X86_REG_R11, &InitR11);
    uc_reg_write(uc, UC_X86_REG_R12, &InitR12);
    uc_reg_write(uc, UC_X86_REG_R13, &InitR13);
    uc_reg_write(uc, UC_X86_REG_R14, &InitR14);
    uc_reg_write(uc, UC_X86_REG_R15, &InitR15);    
    
 //
 //映射堆栈
 //
 //x64dbg 线程1AD4堆栈
 //地址=0000000000148000 大小 = 0000000000008000
 //
 //
    uc_mem_map(uc, (uint64_t)0x148000, 0x8000, UC_PROT_ALL);

    uc_hook_add(uc, &trace2, UC_HOOK_MEM_WRITE_UNMAPPED, hook_mem64, NULL, 1, 0);
    uc_hook_add(uc, &trace3, UC_HOOK_MEM_WRITE, hook_mem64, NULL, 1, 0);

    uc_hook_add(uc, &trace4, UC_HOOK_MEM_READ, hook_mem64, NULL, 1, 0);
    uc_hook_add(uc, &trace5, UC_HOOK_MEM_READ_UNMAPPED, hook_mem64, NULL, 1, 0);

    uc_hook_add(uc, &trace6, UC_HOOK_MEM_FETCH_UNMAPPED, hook_mem64, NULL, 1, 0);


    uc_hook_add(uc, &trace1, UC_HOOK_CODE, hook_code, NULL, 1, 0);

    
    err = uc_emu_start(uc, /*(uint64_t)map_base + entry_point*/0x1401BC77A, (uint64_t)0xffff7fffffffffff, 0, 0);
    if (err) {
        printf("Failed on uc_emu_start() with error returned %u: %s\n",err, uc_strerror(err));
        return -1;
    }






    return 0;
}

