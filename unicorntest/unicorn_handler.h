#pragma once
#include"include/unicorn/unicorn.h"


void hook_mem64(uc_engine* uc, uc_mem_type type,
    uint64_t address, int size, int64_t value, void* user_data);

void hook_code(uc_engine* uc, uint64_t address, uint32_t size, void* user_data);

inline uc_hook trace1, trace2, trace3, trace4,trace5,trace6,trace7;