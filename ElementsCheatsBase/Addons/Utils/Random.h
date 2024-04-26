#pragma once
#include <random>

namespace Random {
	std::string HexString(int length) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 15);

		std::stringstream ss;
		for (int i = 0; i < length; ++i) {
			ss << std::hex << dis(gen);
		}

		return ss.str();
	}
}