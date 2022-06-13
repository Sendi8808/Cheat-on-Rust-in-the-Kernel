
_FI VOID MemCpy(PVOID Dst, PVOID Src, ULONG Size)
{
	__movsb((PUCHAR)Dst, (const PUCHAR)Src, Size);
}

template <typename StrType, typename StrType2>
_FI bool StrICmp(StrType Str, StrType2 InStr, bool Two) 
{
	
	#define ToLower(Char) ((Char >= 'A' && Char <= 'Z') ? (Char + 32) : Char)

	if (!Str || !InStr) return false;
	wchar_t c1, c2; do {
		c1 = *Str++; c2 = *InStr++;
		c1 = ToLower(c1); c2 = ToLower(c2);
		if (!c1 && (Two ? !c2 : 1)) 
			return true;
	} while (c1 == c2); 
	
	return false;
}

_FI VOID Sleep(LONG64 MSec)
{
	LARGE_INTEGER Delay; Delay.QuadPart = -MSec * 10000;
	KeDelayExecutionThread(KernelMode, false, &Delay);
}

_FI VOID MemZero(PVOID Ptr, SIZE_T Size)
{
	__stosb((PUCHAR)Ptr, 0, Size);
}

_FI PVOID KAlloc(ULONG Size) 
{
	PVOID Buff = ExAllocatePoolWithTag(NonPagedPoolNx, Size, 'KgxD');
	if (Buff) MemZero(Buff, Size); return Buff;
}

_FI VOID KFree(PVOID Ptr)
{
	ExFreePoolWithTag(Ptr, 'KgxD');
}

PVOID PDEBase, PTEBase;

__forceinline PMMPTE GetPTEForVA(PVOID Address)
{
#define PHYSICAL_ADDRESS_BITS 40
#define PTI_SHIFT 12
#define PDI_SHIFT 21
#define PTE_SHIFT 3
	PMMPTE PDE = (PMMPTE)(((((ULONG64)Address >> PDI_SHIFT) << PTE_SHIFT) & 0x3FFFFFF8ull) + (ULONG64)PDEBase);

	if (PDE->u.Hard.LargePage)
		return PDE;

	return (PMMPTE)(((((ULONG64)Address >> PTI_SHIFT) << PTE_SHIFT) & 0x7FFFFFFFF8ull) + (ULONG64)PTEBase);
}
PVOID NQSI(SYSTEM_INFORMATION_CLASS Class)
{
	//get alloc size
	NewTry: ULONG ReqSize = 0; 
	ZwQuerySystemInformation(Class, nullptr, ReqSize, &ReqSize);
	if (!ReqSize) goto NewTry; 
	
	//call QuerySystemInfo
	PVOID pInfo = KAlloc(ReqSize);
	if (!NT_SUCCESS(ZwQuerySystemInformation(Class, pInfo, ReqSize, &ReqSize))) {
		KFree(pInfo); goto NewTry;
	}

	//ret data
	return pInfo;
}

//pe utils
PVOID FindSection(PVOID ModBase, const char* Name, PULONG SectSize)
{
	//get & enum sections
	PIMAGE_NT_HEADERS NT_Header = NT_HEADER(ModBase);
	PIMAGE_SECTION_HEADER Sect = IMAGE_FIRST_SECTION(NT_Header);
	for (PIMAGE_SECTION_HEADER pSect = Sect; pSect < Sect + NT_Header->FileHeader.NumberOfSections; pSect++)
	{
		//fix section name
		char SectName[9]; SectName[8] = 0;
		MemCpy(SectName, pSect->Name, 8);

		//check name
		if (StrICmp(SectName, Name, true))
		{
			//save size
			if (SectSize) {
				ULONG SSize = SizeAlign(max(pSect->Misc.VirtualSize, pSect->SizeOfRawData));
				*SectSize = SSize;
			}

			//ret full sect ptr
			return (PVOID)((ULONG64)ModBase + pSect->VirtualAddress);
		}
	}

	return nullptr;
}

PUCHAR FindPatternSect(PVOID ModBase, const char* SectName, const char* Pattern)
{
	//find pattern utils
	#define InRange(x, a, b) (x >= a && x <= b) 
	#define GetBits(x) (InRange(x, '0', '9') ? (x - '0') : ((x - 'A') + 0xA))
	#define GetByte(x) ((UCHAR)(GetBits(x[0]) << 4 | GetBits(x[1])))

	//get sect range
	ULONG SectSize;
	PUCHAR ModuleStart = (PUCHAR)FindSection(ModBase, SectName, &SectSize);
	PUCHAR ModuleEnd = ModuleStart + SectSize;
	
	//scan pattern main
	PUCHAR FirstMatch = nullptr;
	const char* CurPatt = Pattern;
	for (; ModuleStart < ModuleEnd; ++ModuleStart)
	{
		bool SkipByte = (*CurPatt == '\?');
		if (SkipByte || *ModuleStart == GetByte(CurPatt)) {
			if (!FirstMatch) FirstMatch = ModuleStart;
			SkipByte ? CurPatt += 2 : CurPatt += 3;
			if (CurPatt[-1] == 0) return FirstMatch;
		}

		else if (FirstMatch) 
		{
			ModuleStart = FirstMatch;
			FirstMatch = nullptr;
			CurPatt = Pattern;
		}
	}

	//failed
	return nullptr;
}

PVOID GetProcAdress(PVOID ModBase, const char* Name)
{
	PIMAGE_NT_HEADERS NT_Head = NT_HEADER(ModBase);
	PIMAGE_EXPORT_DIRECTORY ExportDir = (PIMAGE_EXPORT_DIRECTORY)((ULONG64)ModBase + NT_Head->OptionalHeader.DataDirectory[0].VirtualAddress);

	for (ULONG i = 0; i < ExportDir->NumberOfNames; i++)
	{
		USHORT Ordinal = ((USHORT*)((ULONG64)ModBase + ExportDir->AddressOfNameOrdinals))[i];
		const char* ExpName = (const char*)ModBase + ((ULONG*)((ULONG64)ModBase + ExportDir->AddressOfNames))[i];

		if (StrICmp(Name, ExpName, true))
			return (PVOID)((ULONG64)ModBase + ((ULONG*)((ULONG64)ModBase + ExportDir->AddressOfFunctions))[Ordinal]);
	}

	return 0;
}


_FI PEPROCESS AttachToProcess(HANDLE PID)
{

	PEPROCESS Process = nullptr;
	if (PsLookupProcessByProcessId(PID, &Process) || !Process)
		return nullptr;

	if (PsAcquireProcessExitSynchronization(Process))
	{
		ObfDereferenceObject(Process);
		return nullptr;
	}

	KeAttachProcess(Process);
	return Process;
}

_FI VOID DetachFromProcess(PEPROCESS Process)
{
	if (Process != nullptr)
	{
		KeDetachProcess();

		ObfDereferenceObject(Process);
		PsReleaseProcessExitSynchronization(Process);
	}
}
PEPROCESS GetProcess(const char* ProcName)
{
	//get process list
	PEPROCESS EProc = nullptr;
	PSYSTEM_PROCESS_INFO pInfo = (PSYSTEM_PROCESS_INFO)NQSI(SystemProcessInformation), pInfoCur = pInfo;

	while (true)
	{
		//get process name
		const wchar_t* ProcessName = pInfoCur->ImageName.Buffer;
		if (MmIsAddressValid((PVOID)ProcessName))
		{
			//check process name
			if (StrICmp(ProcName, ProcessName, true))
			{
				//attach to process
				PEPROCESS Process = AttachToProcess(pInfoCur->UniqueProcessId);
				if (Process != nullptr) 
				{
					EProc = Process;
					break;
					
					//failed
					DetachFromProcess(Process);
				}
			}
		}

		//goto next process entry
		if (!pInfoCur->NextEntryOffset) break;
		pInfoCur = (PSYSTEM_PROCESS_INFO)((ULONG64)pInfoCur + pInfoCur->NextEntryOffset);
	}

	//cleanup
	KFree(pInfo);
	return EProc;
}