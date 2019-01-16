#include "JsonFile.hpp"

int main() {
	JsonFile testFile = JsonFile("content/engine.json");
	int windowScaleX = testFile.Get<int>("engine.window.grid size.width");
	int keyX = testFile.Get<int>("engine.key bindings.1.binding.key value");

	float versionF = testFile.Get<float>("engine.window.scalar.x");
	double versionD = testFile.Get<double>("engine.window.scalar.y");

	return 0;
}