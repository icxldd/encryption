#include "baseHead.h"


//v1-> source v2->encryption key v3->enctrption later data
nakedStdCall(void) _xorCore(void *v1, void *v2, void *v3)
{
	__asm
	{
		push ebx

			mov eax, [esp + 0x8]
			mov eax, [eax]
			mov[esp + 0x8], eax
			xor eax, eax
			mov al, byte ptr ds : [esp + 0x8]


			mov ebx, [esp + 0xC]
			mov ebx, [ebx]
			mov[esp + 0xC], ebx
			xor ebx, ebx
			mov  bl, byte ptr ds : [esp + 0xC]
			xor al, bl

			mov ebx, [esp + 0x10]
			mov[ebx], eax

			pop ebx
			ret 0xc
	}

}
//·ÖÅäÄÚ´æ
//v1 -> size
LPVOID _VirtualAlloc(DWORD v1)
{
	return VirtualAlloc(NULL, v1, MEM_COMMIT, PAGE_READWRITE);
}






