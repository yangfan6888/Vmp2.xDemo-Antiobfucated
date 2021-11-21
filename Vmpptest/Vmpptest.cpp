#include <iostream>
#include<windows.h>
#include"VMProtectSDK.h"
using namespace std;

#ifdef _WIN64
#pragma comment(lib, "VMProtectSDK64.lib")
#endif

static ULONG64 test;

//声明在x64.asm中的函数
extern "C"
{
    __forceinline ULONG64 Entry(ULONG64* addr);
}

int main()
{
    printf("test at %llx\n", &test);
    VMProtectBegin
    
    Entry(&test);
    
    printf("Is Debugger Present ? %s\n",IsDebuggerPresent() ? "yes" : "no");

    VMProtectEnd
    
    printf("ooooook\n");
    getchar();

}


