#pragma 
#include <cstdint>
#include "..\ElementsCheatsBase\Addons\Minhook\MinHook.h"

namespace HookManager {
    template<typename TFunc>
    void HookFunction(uintptr_t address, TFunc detour, TFunc& original) {
        MH_CreateHook(reinterpret_cast<LPVOID>(address), reinterpret_cast<LPVOID>(detour), reinterpret_cast<void**>(&original));
        MH_EnableHook(reinterpret_cast<LPVOID*>(address));
    }
}