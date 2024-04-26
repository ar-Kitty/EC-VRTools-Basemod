
struct Config {
	static Config* Get() {
		static Config* c = new Config();
		return c;
	}

	bool E1Earape;
};