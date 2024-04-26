#include <Windows.h>
#include <cstdint>
#include <chrono>
#include <functional>
#include <thread>

#include "..\ElementsCheatsBase\Addons\IL2CPPDefinitions\il2cpp.h"
#include "..\ElementsCheatsBase\Addons\lazyimporter\lazyimporter.h"
#include "..\ElementsCheatsBase\Addons\ElementsModSDK\elements.h"

// Globals
#include "..\ElementsCheatsBase\Globals\Config.h"
#include "..\ElementsCheatsBase\Globals\Offsets.h"
#include "..\ElementsCheatsBase\Globals\Globals.h"

#include "..\ElementsCheatsBase\Addons\UnityApi\IL2CPP_Resolver.hpp"
#include "..\ElementsCheatsBase\Addons\Utils\Random.h"
#include "..\ElementsCheatsBase\Addons\Utils\Pattern.h"

#include "..\ElementsCheatsBase\Addons\System\System.h"
#include "..\ElementsCheatsBase\Addons\LoadBalancingClient\LoadBalancingClient.h"
#include "..\ElementsCheatsBase\Addons\HookManager\HookManager.h"

#include "..\ElementsCheatsBase\InternalGUI.h"
#include "..\ElementsCheatsBase\Hooks\PlayerHooks.h"

HWND VRCWindow = nullptr;
static uintptr_t __cdecl I_beginthreadex(void* _Security, unsigned _StackSize, _beginthreadex_proc_type _StartAddress, void* _ArgList, unsigned _InitFlag, unsigned* _ThrdAddr) {
    return iat(_beginthreadex).get()(_Security, _StackSize, _StartAddress, _ArgList, _InitFlag, _ThrdAddr);
}

#define IATHookThread(mainThread, dllhandle) I_beginthreadex(0, 0, (_beginthreadex_proc_type)mainThread, dllhandle, 0, 0);

static void LogHook(uintptr_t address, const char* name) {
    std::stringstream buffer;
    buffer << "[ELEMENTSBASE] " << name << ": 0x" << std::hex << address;
    HANDLE ConHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("[");
    SetConsoleTextAttribute(ConHandle, FOREGROUND_RED);
    printf("ELEMENTSBASE");
    SetConsoleTextAttribute(ConHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("] %s: 0x%llX\n", name, address);
}

static void Log(const char* input) {
    std::stringstream buffer;
    buffer << "[ELEMENTSBASE] " << input;
}


void CreateConsole(std::string txt) {
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    SetConsoleTitle(txt.c_str());
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
}

void GetOffsets() {
    Offsets* offsets = Offsets::Get();

    Unity::il2cppClass* ButtonClass = IL2CPP::Class::Find("UnityEngine.UI.Button");
    offsets->Press = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ButtonClass, "Press");

    Unity::il2cppClass* BufferClass = IL2CPP::Class::Find("System.Buffer");
    offsets->BlockCopy = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(BufferClass, "BlockCopy");

    Unity::il2cppClass* ConvertClass = IL2CPP::Class::Find("System.Convert");
    offsets->FromBase64String = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ConvertClass, "FromBase64String");

    offsets->GetBytes = (uintptr_t)0x407B6C0;
    offsets->OnEvent = (uintptr_t)0x0;
    offsets->OpRaiseEvent = (uintptr_t)0x1626DD0;
    offsets->OnNetworkReady = (uintptr_t)0x16BC940;
    offsets->OnDestroy = (uintptr_t)0x16BC5E0;

    offsets->ObjectInstantinateWithTransform = (uintptr_t)PatternUtils::find_pattern(IL2CPP::Globals.m_GameAssembly, "48 89 5c 24 ? 57 48 83 ec ? 80 3d ? ? ? ? ? 48 8b da 48 8b f9 75 ? 48 8d 0d ? ? ? ? e8 ? ? ? ? c6 05 ? ? ? ? ? 48 8b 0d ? ? ? ? 83 b9 ? ? ? ? ? 75 ? e8 ? ? ? ? 45 33 c9 45 33 c0 48 8b d3 48 8b cf 48 8b 5c 24 ? 48 83 c4 ? 5f e9 ? ? ? ? cc cc cc cc 48 89 5c 24 ? 48 89 6c 24 ? 57");
}

void InitHooks() {
    Offsets* offsets = Offsets::Get();


    HookManager::HookFunction(((uintptr_t)IL2CPP::Globals.m_GameAssembly + offsets->OnNetworkReady), PlayerHooks::OnNetworkReady_h, PlayerHooks::OnNetworkReady);
    LogHook(offsets->OnNetworkReady, "OnNetworkReady");

    HookManager::HookFunction(((uintptr_t)IL2CPP::Globals.m_GameAssembly + offsets->OnDestroy), PlayerHooks::OnDestroy_h, PlayerHooks::OnDestroy);
    LogHook(offsets->OnDestroy, "OnDestroy");
}


void Init() {
    CreateConsole(Random::HexString(50));
    Log("Welcome to ELEMENTSBASE <3\n");
    Log("Have Fun!!!\n");
    Log("<.<\n");

    IL2CPP::Initialize(true);

    IL2CPP::Thread::Attach(IL2CPP::Domain::Get());
    Log("Fetched IL2CPP Domain \n");
    GetOffsets();
    Log("Fetched Offsets\n");
    InitHooks();
    Log("Hooked Functions <.< :steamhappy: \n");
}


/// <summary>
/// VERY IMPORTANT THAT YOU CHECK IF THE CURRENT PROCESS IS REALLY VRC. IF NOT YOU CAN KILL U WINDOWS!!!!!
/// </summary>
void WaitForVRChat() {
    do
    {
        VRCWindow = FindWindowW(nullptr, L"VRChat");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (!VRCWindow);

    Init();
}


/// <summary>
/// DO NOT USE A DEBUG BUILD! 
/// THE LOADER REQUIRED A RELEASE BOULD OR ELSE YOU GET A EAC FLAG!
/// </summary>
BOOL APIENTRY DllMain(HMODULE DllHandle, DWORD CReason,LPVOID lpReserved)
{
    if (CReason == 1) { // Process Attach
        elements ElementsSDK;
        if (ElementsSDK.RunMod(CReason)) {
            // Start Hooks etc
            DisableThreadLibraryCalls(DllHandle);

            // New Thread 
            IATHookThread(WaitForVRChat, DllHandle);
        }
        else {
            // Finish up dll
            return TRUE;
        }
    }
    return TRUE;
}

