#pragma once

namespace LoadBalancingClient {
	typedef bool (__fastcall* OpRaiseEventFunc)(uint8_t, Il2CppObject*, ________________________1201_o* raiseEventOptions, ExitGames_Client_Photon_SendOptions_o);

	bool OpRaiseEvent(uint8_t eventCode, Il2CppObject* customEventContent, ________________________1201_o* raiseEventOptions, ExitGames_Client_Photon_SendOptions_o sendOptions) {
		return ((OpRaiseEventFunc)(IL2CPP::Globals.m_GameAssembly + Offsets::Get()->OpRaiseEvent))(eventCode, customEventContent, raiseEventOptions, sendOptions);
	}
}