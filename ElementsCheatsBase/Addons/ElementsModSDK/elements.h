#include <Windows.h>
#include <cstdint>
#include <chrono>
#include <functional>
#include <thread>


class elements
{
public: 
	/// <summary>
	/// <see href="https://discord.gg/zUKEaj4jpz">Join Discord for Help</see>
	/// To initialize your mod, call this method. it will check if the Current Process is VRChat. 
	/// <para><strong>But you need the Lazyimport Funktion in ur main to get the Mod Running!</strong></para> 
	/// <para>Look at the Basemod. How to Use:</para> 
	/// <para> if(RunMod(CReason)) {</para> 
	/// <para>		DisableThreadLibraryCalls(hinstDLL);</para> 
	/// <para>		IATHookThread(Checkprocess, hinstDLL);</para> 
	/// <para> }</para> 
	/// </summary>
	/// <param name="CReason">DLL Base Adress</param>
	/// <returns>
	/// <list type="bullet">
	/// <item><para><strong>true</strong> -> Current Process is VRChat </para></item>
	/// <item><para><strong>false</strong> -> Current Process is not VRChat </para></item>
	/// </list>
	/// </returns>
	bool RunMod(DWORD CReason);



	// Private methodes
private:
	HWND VRCWindow = nullptr;


	/// <summary>
	/// Is Process = VRChat
	/// </summary>
	/// <returns>true, false</returns>
	bool isCurrentProcessVRChat();

};

