#include "JsonFile.hpp"

int main() {
	// Load the File
	JsonFile testFile = JsonFile("content/engine.json");

	// Get Tests
	int getIntTest = testFile.Get<int>("engine.window.grid size.width");
	float getFloatTest = testFile.Get<float>("engine.game controller.thumb stick dead zone");
	double getDoubleTest = testFile.Get<double>("engine.game controller.trigger dead zone");
	std::string getStringTest = testFile.Get<std::string>("engine.developer");
	bool getBoolTest = testFile.Get<bool>("engine.vsync");

	JsonFile arrayTextFile = JsonFile("content/test_level.json");
	std::vector<int> levelData = arrayTextFile.GetArray<int>("level.tile grid");
	

	// Close the test program
	return 0;
}