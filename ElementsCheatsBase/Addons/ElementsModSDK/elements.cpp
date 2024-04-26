#include "elements.h"


bool elements::isCurrentProcessVRChat() {
    char path[MAX_PATH];
    if (GetModuleFileNameA(NULL, path, MAX_PATH) == 0) {
        return false;
    }

    std::string pathStr = path;
    // Suche nach "VRChat.exe" im Pfad
    return pathStr.find("VRChat.exe") != std::string::npos;
}

void elements::Checkprocess() {

    do
    {
        VRCWindow = FindWindowW(nullptr, L"VRChat");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (!VRCWindow);

}


/// <summary>
/// To initialize your mod, call this method
/// </summary>
/// <param name="DllHandle">DLL Base Adress</param>
/// <param name="CReason">DLL Base Adress</param>
/// <returns>true = everything is Fine :)</returns>
bool elements::RunMod(DWORD CReason) {
	bool lReturn = false; // for Return

	if (CReason == 1) {
        if (isCurrentProcessVRChat()) {
            return true;
        }
	}
    return false;

}



