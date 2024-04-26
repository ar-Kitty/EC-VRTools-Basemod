#pragma once

namespace PlayerHooks {
	void(UNITY_CALLING_CONVENTION OnNetworkReady)(________________________1264_o*, DWORD*);
	void OnNetworkReady_h(________________________1264_o* Player, DWORD* MethodInfo) {
		bool IsSelf = ((Unity::CComponent*)Player->fields.apiuser)->CallMethodSafe<bool>("get_IsSelf");
		if (IsSelf) {
			Globals::Get()->LocalPlayer = Player;
			printf("LocalPlayer Joined!");

			static bool hasmadebuttons = false;
			if (!hasmadebuttons) {
				InternalGUI::Setup();
				hasmadebuttons = true;
			}
		}

		printf(("[Joined] " + ((Unity::System_String*)Player->fields.apiuser->fields._username_k__BackingField)->ToString() + "\n").c_str());

		return OnNetworkReady(Player, MethodInfo);
	}

	void (UNITY_CALLING_CONVENTION OnDestroy)(________________________1264_o*, DWORD*);
	void OnDestroy_h(________________________1264_o* Player, DWORD* MethodInfo) {
		bool IsSelf = ((Unity::CComponent*)Player->fields.apiuser)->CallMethodSafe<bool>("get_IsSelf");
		if (IsSelf) {
			Globals::Get()->LocalPlayer = nullptr;
		}

		return OnDestroy(Player, MethodInfo);
	}
}