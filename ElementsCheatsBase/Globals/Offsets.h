
struct Offsets {
	static Offsets* Get() {
		static Offsets* c = new Offsets();
		return c;
	}

public:
	// UnityEngine.UI.Button Offsets
	uintptr_t Press;

	//Photon Offsets
	uintptr_t OnEvent; // Anticrash
	uintptr_t OpRaiseEvent; //E1
	uintptr_t GetBytes;

	uintptr_t BlockCopy;
	uintptr_t FromBase64String;

	// Player Offsets
	uintptr_t OnNetworkReady; // Used For Player Join
	uintptr_t OnDestroy;	  // Used For Player Leave

	// Gameobjects
	uintptr_t ObjectInstantinateWithTransform;
};