#pragma once

namespace System {
	typedef System_Byte_array* (__fastcall* FromBase64StringFunc)(Unity::System_String*);
	typedef void (__fastcall* BlockCopyFunc)(System_Array_o*, int32_t, System_Array_o*, int32_t, int32_t);
	typedef System_Byte_array* (__fastcall* GetBytesFunc)(int32_t);


	void BlockCopy(System_Array_o* Source, int32_t Offset, System_Array_o* Destination, int32_t DestinationOffset, int32_t Count){
		return ((BlockCopyFunc)(Offsets::Get()->BlockCopy))(Source, Offset, Destination, DestinationOffset, Count);
	}

	System_Byte_array* FromBase64String(Unity::System_String* String) {
		return ((FromBase64StringFunc)(Offsets::Get()->FromBase64String))(String);
	}

	System_Byte_array* get_bytes(int32_t v) {
		return ((GetBytesFunc)(IL2CPP::Globals.m_GameAssembly + Offsets::Get()->GetBytes))(v);
	}
}