// jx3dll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

//定义枚举类型数据结构

typedef enum _THREADINFOCLASS{
	ThreadBasicInformateion,
	ThreadTimes,
	ThreadPriority,
	ThreadBasePriority,
	ThreadAffinityMask,
	ThreadImpersonationToken,
	ThreadDescriptorTableEntry,
	ThreadEnaleAlignmentFaultFixup,
	ThreadEventPair_Reusable,
	ThreadQuerySetWin32StartAddress,
	ThreadZeroTlsCell,
	ThreadPerformanceCount,
	ThreadAmlLastThread,
	ThreadIdealProcessor,
	ThreadPriorityBoost,
	ThreadSetTlsArrayAddress,
	ThreadiSloPending,
	ThreadHideFormDebugger,//这个就是用来将线程对调试器隐藏
	ThreadBreakOnTermination,
	ThreadSwitchLegacyState,
	ThreadIsTerminated,
	MaxThreadInfoClass
}THREADINFOCLASS;

//定义
typedef DWORD(WINAPI *ZWSETINFORMATIONTHREAD)(HANDLE,THREADINFOCLASS,PVOID,DWORD);

ZWSETINFORMATIONTHREAD ZwsetInformationThread =NULL;
BYTE ZwSetInformationThread_Begin[5]={0};
BYTE ZwSetInformationThread_Hook[5]={0xE9,0,0,0,0};
//hook时候自己的要干什么函数
DWORD WINAPI MyZwSetInformationThread(
									  HANDLE ThreadHandle,
									  THREADINFOCLASS ThreadInoformationClass,
									  PVOID ThreadInformation,
									  DWORD ThreadInformationLength
									  )
{
	//先恢复函数头
	::WriteProcessMemory(
						HANDLE(-1),
						ZwsetInformationThread,
						ZwSetInformationThread_Begin,
						5,
						0);
	DWORD Ret= TRUE;
	//判断是否为ThreadHideFormDebugger 然后 返回原始的结过
	if(ThreadInoformationClass != ThreadHideFormDebugger)
	{
		Ret=ZwsetInformationThread(
			ThreadHandle,
			ThreadInoformationClass,
			ThreadInformation,
			ThreadInformationLength
			);

	}
	//如果不是重新hook住 继续下一个
	::WriteProcessMemory(
		HANDLE(-1),
		ZwsetInformationThread,
		ZwSetInformationThread_Hook,
		5,
		0);
	return Ret;

}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		MessageBoxA(
			0,
			"注入程序HOOK",
			"11",
			MB_YESNO);
		//获取api的地址
		ZwsetInformationThread = (ZWSETINFORMATIONTHREAD)::GetProcAddress(
			::GetModuleHandle("NTDLL.DLL"),
			"ZwSetInformationThread"
			);
		//当前自己函数地址减去api地址在减去5 等于HOOK的差值
		*(DWORD*)(ZwSetInformationThread_Hook+1)=
			(DWORD)MyZwSetInformationThread-(DWORD)ZwsetInformationThread-5;
		//读取api地址的默认初始内存地址值
		::ReadProcessMemory(
			HANDLE(-1),
			ZwsetInformationThread,
			ZwSetInformationThread_Begin,
			5,
			0
			);
		//写入前面计算的差值，跳转到 自己的函数MyZwSetInformationThread

		::WriteProcessMemory(
			HANDLE(-1),
			ZwsetInformationThread,
			ZwSetInformationThread_Hook,
			5,
			0);
		MessageBoxA(
			0,
			"注入程序HOOK",
			"11",
			MB_YESNO);
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
    return TRUE;
}

