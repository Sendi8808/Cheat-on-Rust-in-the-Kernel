PVOID GetModulRust(PEPROCESS Process, const char* ModName)

{
    PPEB PEB = PsGetProcessPeb(Process);
    if (!PEB || !PEB->Ldr) return nullptr;
    for (PLIST_ENTRY pListEntry = PEB->Ldr->InLoadOrderModuleList.Flink;
        pListEntry != &PEB->Ldr->InLoadOrderModuleList;
        pListEntry = pListEntry->Flink)
    {
        if (MmIsAddressValid(pListEntry))
        {
            PLDR_DATA_TABLE_ENTRY pEntry = CONTAINING_RECORD(pListEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
            if (MmIsAddressValid(pEntry) && MmIsAddressValid(pEntry->BaseDllName.Buffer)) {
                if (StrICmp(ModName, pEntry->BaseDllName.Buffer, true))
                    return pEntry->DllBase;
            }
        }
    }
    return nullptr;
}