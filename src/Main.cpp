#include "JsonFile.hpp"

int main() {
	JsonFile testFile = JsonFile("content/engine.json");
	int windowScaleX = testFile.Get<int>("engine.window.scalar.x");
	int keyX = testFile.Get<int>("engine.key bindings.1.binding.key value");

	return 0;
}