#include "JsonFile.hpp"

int main() {
	// Load the File
	JsonFile testFile = JsonFile("content/get_test.json");
	
	// Get<T>() Tests
	int getIntTest = testFile.Get<int>("value test.int");
	float getFloatTest = testFile.Get<float>("value test.float");
	double getDoubleTest = testFile.Get<double>("value test.double");
	std::string getStringTest = testFile.Get<std::string>("value test.string");
	bool getBoolTest = testFile.Get<bool>("value test.boolean");

	// GetArray<T>() Tests
	std::vector<int> getIntArrayTest = testFile.GetArray<int>("array test.int array");
	std::vector<float> getFloatArrayTest = testFile.GetArray<float>("array test.float array");
	std::vector<double> getDoubleArrayTest = testFile.GetArray<double>("array test.double array");
	std::vector<std::string> getStringArrayTest = testFile.GetArray<std::string>("array test.string array");
	std::vector<bool> getBoolArrayTest = testFile.GetArray<bool>("array test.boolean array");
	
	// Close the program
	return 0;
}