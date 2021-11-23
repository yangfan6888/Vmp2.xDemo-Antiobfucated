#include"vmp2.h"
#include<intrin.h>


uint64_t de_dispatch_handler(uint64_t disp)
{
	return disp - 0xFFFFFFFF834D51A3;
}