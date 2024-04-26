#pragma once

#include "..\ElementsCheatsBase\Addons\Super Simple Button Api\BtnAPI.h"

namespace InternalGUI {
	void Setup() {
		BtnUtils::BtnInstantinator::GetDevToolsButton()->SetActive(true);
		BtnUtils::BtnInstantinator::SetupPanel("Ente");


	}
}