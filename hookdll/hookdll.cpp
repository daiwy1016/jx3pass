// hookdll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdlib.h>
//BYTE Write[5]={0};//定义 5个字节
DWORD address,*temp;//最后四个字节是地址
BYTE Write[5]={0xE9,0,0,0,0};//第一个字节放jmp机器码

void Ro_hookBlood()
{
 //MessageBoxA(0,"HOOK test","11",MB_YESNO);
 //AfxMessageBox(_T("HOOK test"));
 __asm
 {
 pop edi
 pop esi
 pop ebx
 add esp,0x40
 mov esp,ebp
 pop ebp
 mov ecx,0x401065
 mov dword ptr ss:[ebp-0x4],0x6
 jmp ecx
 }
}


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch(ul_reason_for_call){
	case DLL_PROCESS_ATTACH:
		MessageBoxA(0,"进程开始","11",MB_YESNO);
		__asm
		{
			mov ecx,offset Ro_hookBlood	//把函数的地址传到exc
				mov address,ecx             //把函数地址传递给address
				sub address,0x401063		//计算偏移，因为是jmp相对偏移，这里address（跳到地址）-开始跳的地址-跳转指令大小 一般为5
				//add esp,4				//跳过压站防止堆栈不平衡
				
				
		}
		


		temp=(DWORD*)&Write[1];//从write[1]位置开始写入
	
		*temp=address; //把address 写入Write[1]
		::WriteProcessMemory(
			::GetCurrentProcess(),
			(LPVOID)0x40105E,
			Write,
			sizeof(Write),//返回对象或类型所占的内存字节数
					 NULL);
		break;
	case DLL_PROCESS_DETACH:
		MessageBoxA(0,"关闭进程","22",MB_YESNO);
		break;
	}

    return TRUE;
}

