#include "include.h"


void NTAPI MainThread(void*) {
WaitProcess:
	Process = GetProcess("RustClient.exe");

	if (!Process)
	{
		Sleep(200);
		goto WaitProcess;
	}
	GameAssembly = GetModulRust(Process, "GameAssembly.dll");

	DbgPrintEx(0, 0, "\nGameAssembly: 0x%p\n", GameAssembly);

	Func();

	DetachFromProcess(Process);
}



NTSTATUS NTAPI DriverEntry(PVOID pParam1, PVOID pParam2) {
	PVOID KBase = pParam1;

	ULONG64 PTE = (ULONG64)FindPatternSect(KBase, (".text"), ("48 23 C8 48 B8 ? ? ? ? ? ? ? ? 48 03 C1 C3"));
	PTE = *(ULONG64*)(PTE + 5);
	ULONGLONG Mask = (1ll << (PHYSICAL_ADDRESS_BITS - 1)) - 1;
	PDEBase = PVOID((PTE & ~Mask) | ((PTE >> 9) & Mask));
	PTEBase = PVOID(PTE);

	HANDLE thread_handle = nullptr;
	const auto status = PsCreateSystemThread(&thread_handle, GENERIC_ALL, nullptr, nullptr, nullptr, MainThread, nullptr);
	
	return STATUS_SUCCESS;
}


#pragma code_seg(pop)