#pragma once

struct Globals {
	static Globals* Get() {
		static Globals* c = new Globals();
		return c;
	}

	________________________1264_o* LocalPlayer;
};