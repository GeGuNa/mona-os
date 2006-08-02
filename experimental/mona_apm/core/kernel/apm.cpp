#include <sys/types.h>
#include "apm.h"
#include "global.h"
#include "kernel.h"

/* APMの関数群はCPL=0で実行しなければならない */

typedef struct
{
	dword eax;
	dword ebx;
	dword ecx;
	dword edx;
	dword esi;
	dword edi;
}apm_bios_regs;

typedef struct
{
	dword offset;
	word segment __attribute__((packed));
} apm_bios_entry;

extern "C"
{
	apm_bios_entry apm_eip;
	word apm_bios_call(byte fn, apm_bios_regs *regs);
}

void apm_init(void)
{
	apm_eip.offset = g_apmInfo->eip;
	apm_eip.segment = 0x40;

	g_console->printf("apm_eip = %x\n", apm_eip.offset);
	g_console->printf("apm_des = %x\n", apm_eip.segment);
}

dword apm_bios(dword fn, dword ebx, dword ecx, dword edx, dword esi, dword edi)
{
	apm_bios_regs regs;

	regs.eax = 0x5300 | fn;
	regs.ebx = ebx;
	regs.ecx = ecx;
	regs.edx = edx;
	regs.esi = esi;
	regs.edi = edi;

	return apm_bios_call(0x53|fn, &regs);
}

word apm_set_power_state(word did, word state)
{
	apm_bios_regs regs;

	regs.eax = 0x5307;
	regs.ebx = did;
	regs.ecx = state;
	regs.edx = 0;
	regs.edi = 0;
	regs.esi = 0;

	g_console->printf("Calling APM BIOS.\n");
	return apm_bios_call(0x5307, &regs);
}

word apm_get_power_state(word did)
{
	apm_bios_regs regs;

	regs.eax = 0x530C;
	regs.ebx = did;
	regs.ecx = 0;
	regs.edx = 0;
	regs.edi = 0;
	regs.esi = 0;

	g_console->printf("Calling apm function.");
	apm_bios_call(0x530C, &regs);
	return (word)regs.ecx;
}