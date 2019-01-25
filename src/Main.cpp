#include "JsonFile.hpp"

int main() {
	// Load the File
	JsonFile testFileForGets = JsonFile("content/get_test.json");
	
	// Get<T>() Tests
	int getIntTest = testFileForGets.Get<int>("value test.int");
	float getFloatTest = testFileForGets.Get<float>("value test.float");
	double getDoubleTest = testFileForGets.Get<double>("value test.double");
	std::string getStringTest = testFileForGets.Get<std::string>("value test.string");
	bool getBoolTest = testFileForGets.Get<bool>("value test.boolean");

	// GetArray<T>() Tests
	std::vector<int> getIntArrayTest = testFileForGets.GetArray<int>("array test.int array");
	std::vector<float> getFloatArrayTest = testFileForGets.GetArray<float>("array test.float array");
	std::vector<double> getDoubleArrayTest = testFileForGets.GetArray<double>("array test.double array");
	std::vector<std::string> getStringArrayTest = testFileForGets.GetArray<std::string>("array test.string array");
	std::vector<bool> getBoolArrayTest = testFileForGets.GetArray<bool>("array test.boolean array");
	
	// Load the File
	JsonFile testFileForSets = JsonFile("content/set_test.json");



	// Close the program
	return 0;
}