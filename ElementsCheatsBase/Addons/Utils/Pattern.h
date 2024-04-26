#pragma once
#include <Psapi.h>

#define _PRINT_DEBUG
#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

namespace PatternUtils {


	__int64 find_pattern(const char* Assembly, const char* pattern) {
		const char* pat = pattern;
		__int64 firstMatch = NULL;
		MODULEINFO moduleInfo;
		if (!GetModuleInformation((HANDLE)-1, GetModuleHandle(Assembly), &moduleInfo, sizeof(MODULEINFO)) || !moduleInfo.lpBaseOfDll) {
			return NULL;
		}
		__int64 pCur = (__int64)moduleInfo.lpBaseOfDll;
		__int64 range_end = (__int64)moduleInfo.lpBaseOfDll + moduleInfo.SizeOfImage;
		__int64 region_end;
		MEMORY_BASIC_INFORMATION mbi{};
		while (sizeof(mbi) == VirtualQuery((LPCVOID)pCur, &mbi, sizeof(mbi))) {
			if (pCur >= range_end - strlen(pattern))
				break;
			if (!(mbi.Protect & (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_READWRITE))) {
				pCur += mbi.RegionSize;
				continue;
			}
			region_end = pCur + mbi.RegionSize;
			while (pCur < region_end)
			{
				if (!*pat)
					return firstMatch;
				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
					if (!firstMatch)
						firstMatch = pCur;
					if (!pat[1] || !pat[2])
						return firstMatch;

					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
						pat += 3;
					else
						pat += 2;
				}
				else {
					if (firstMatch)
						pCur = firstMatch;
					pat = pattern;
					firstMatch = 0;
				}
				pCur++;
			}
		}
		return NULL;
	}

	__int64 find_pattern(uintptr_t Assembly, const char* pattern) {
		const char* pat = pattern;
		__int64 firstMatch = NULL;
		MODULEINFO moduleInfo;
		if (!GetModuleInformation((HANDLE)-1, (HMODULE)Assembly, &moduleInfo, sizeof(MODULEINFO)) || !moduleInfo.lpBaseOfDll) {
			return NULL;
		}
		__int64 pCur = (__int64)moduleInfo.lpBaseOfDll;
		__int64 range_end = (__int64)moduleInfo.lpBaseOfDll + moduleInfo.SizeOfImage;
		__int64 region_end;
		MEMORY_BASIC_INFORMATION mbi{};
		while (sizeof(mbi) == VirtualQuery((LPCVOID)pCur, &mbi, sizeof(mbi))) {
			if (pCur >= range_end - strlen(pattern))
				break;
			if (!(mbi.Protect & (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_READWRITE))) {
				pCur += mbi.RegionSize;
				continue;
			}
			region_end = pCur + mbi.RegionSize;
			while (pCur < region_end)
			{
				if (!*pat)
					return firstMatch;
				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
					if (!firstMatch)
						firstMatch = pCur;
					if (!pat[1] || !pat[2])
						return firstMatch;

					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
						pat += 3;
					else
						pat += 2;
				}
				else {
					if (firstMatch)
						pCur = firstMatch;
					pat = pattern;
					firstMatch = 0;
				}
				pCur++;
			}
		}
		return NULL;
	}

	__int64 find_pattern(HMODULE Assembly, const char* pattern) {
		const char* pat = pattern;
		__int64 firstMatch = NULL;
		MODULEINFO moduleInfo;
		if (!GetModuleInformation((HANDLE)-1, Assembly, &moduleInfo, sizeof(MODULEINFO)) || !moduleInfo.lpBaseOfDll) {
			return NULL;
		}
		__int64 pCur = (__int64)moduleInfo.lpBaseOfDll;
		__int64 range_end = (__int64)moduleInfo.lpBaseOfDll + moduleInfo.SizeOfImage;
		__int64 region_end;
		MEMORY_BASIC_INFORMATION mbi{};
		while (sizeof(mbi) == VirtualQuery((LPCVOID)pCur, &mbi, sizeof(mbi))) {
			if (pCur >= range_end - strlen(pattern))
				break;
			if (!(mbi.Protect & (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_READWRITE))) {
				pCur += mbi.RegionSize;
				continue;
			}
			region_end = pCur + mbi.RegionSize;
			while (pCur < region_end)
			{
				if (!*pat)
					return firstMatch;
				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
					if (!firstMatch)
						firstMatch = pCur;
					if (!pat[1] || !pat[2])
						return firstMatch;

					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
						pat += 3;
					else
						pat += 2;
				}
				else {
					if (firstMatch)
						pCur = firstMatch;
					pat = pattern;
					firstMatch = 0;
				}
				pCur++;
			}
		}
		return NULL;
	}

	auto resolve_jmp = [](__int64 addr) -> __int64 {
		return *(int*)(addr + 1) + addr + 5;
		};
	auto resolve_lea = [](__int64 addr) -> __int64 {
		return *(int*)(addr + 3) + addr + 7;
		};
}