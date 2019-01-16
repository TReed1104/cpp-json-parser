#include "JsonFile.hpp"

int main() {
	// Load the File
	JsonFile testFile = JsonFile("content/engine.json");

	// Get Tests
	int getIntTest = testFile.Get<int>("engine.window.grid size.width");
	float getFloatTest = testFile.Get<float>("engine.window.scalar.x");
	double getDoubleTest = testFile.Get<double>("engine.window.scalar.y");
	std::string getStringTest = testFile.Get<std::string>("engine.developer");

	// Close the test program
	return 0;
}