#include "JsonFile.hpp"

int main() {
	JsonFile testFile = JsonFile("content/engine.json");
	std::string programId = testFile.Get<std::string>("engine.program id");

	return 0;
}