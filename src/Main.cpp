#include "JsonFile.hpp"

int main() {
	// Load the File
	JsonFile testFile = JsonFile("content/engine.json");

	// Get Tests
	int getIntTest = testFile.Get<int>("engine.window.grid size.width");
	float getFloatTest = testFile.Get<float>("engine.game controller.thumb stick dead zone");
	double getDoubleTest = testFile.Get<double>("engine.game controller.trigger dead zone");
	std::string getStringTest = testFile.Get<std::string>("engine.developer");

	// Close the test program
	return 0;
}