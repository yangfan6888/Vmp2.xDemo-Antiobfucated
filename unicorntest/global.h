#pragma once
#include<Windows.h>
#include<iostream>



//
//����Ҫ�������ļ��������ڸ��ļ�Ŀ¼��
//
inline const char* packed_file = "vmp2/Vmpptest.vmp.exe";
inline const wchar_t* wpacked_file = L"vmp2/Vmpptest.vmp.exe";

//
//�����������ǽ�ʵ�ʵ�vaת��Ϊ��LoadLibraryΪ��ַ��va
//���LoadLibrary���صĻ���ַ��0x140000000�Ļ��Ͳ��������
//
#define translate(base,va) ((unsigned __int64)va-0x140000000))+(unsigned __int64)base)  


//
//x64����ģ�����
//MOV RAX, QWORD PTR DS:[0x0000000140000000]
//48 A1 00 00 00 40 01 00 00 00
//
#define x64_test_emu "\x48\xA1\x00\x00\x00\x40\x01\x00\x00\x00"

inline CONTEXT emu_ctx;

inline std::ostream& operator<<(std::ostream& os,const CONTEXT& ctx)
{
	using std::endl;
	os << "RAX " << ctx.Rax << endl;
	os << "RBX " << ctx.Rbx << endl;
	os << "RCX " << ctx.Rcx << endl;
	os << "RDX " << ctx.Rdx << endl;
	os << "RBP " << ctx.Rbp << endl;
	os << "RSP " << ctx.Rsp << endl;
	os << "RSI " << ctx.Rsi << endl;
	os << "RDi " << ctx.Rdi << endl;

	os << "R8 " << ctx.R8 << endl;
	os << "R9 " << ctx.R9 << endl;
	os << "R10 " << ctx.R10 << endl;
	os << "R11 " << ctx.R11 << endl;
	os << "R12 " << ctx.R12 << endl;
	os << "R13 " << ctx.R13 << endl;
	os << "R14 " << ctx.R14 << endl;
	os << "R15 " << ctx.R15 << endl;
	return os;
}