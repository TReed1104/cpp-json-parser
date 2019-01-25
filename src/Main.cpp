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

	// Get<T>() tests for accessing arrays
	int getIntFromArrayTest = testFileForGets.Get<int>("array test.int array.2");
	float getFloatFromArrayTest = testFileForGets.Get<float>("array test.float array.1");
	double getDoubleFromArrayTest = testFileForGets.Get<double>("array test.double array.4");
	std::string getStringFromArrayTest = testFileForGets.Get<std::string>("array test.string array.3");
	bool getBoolFromArrayTest = testFileForGets.Get<bool>("array test.boolean array.2");

	// GetArray<T>() Tests
	std::vector<int> getIntArrayTest = testFileForGets.GetArray<int>("array test.int array");
	std::vector<float> getFloatArrayTest = testFileForGets.GetArray<float>("array test.float array");
	std::vector<double> getDoubleArrayTest = testFileForGets.GetArray<double>("array test.double array");
	std::vector<std::string> getStringArrayTest = testFileForGets.GetArray<std::string>("array test.string array");
	std::vector<bool> getBoolArrayTest = testFileForGets.GetArray<bool>("array test.boolean array");
	
	// Load the File
	JsonFile testFileForSets = JsonFile("content/set_test.json");
	testFileForSets.Set<int>("value test.int", 111);
	testFileForSets.Set<float>("value test.float", 101.89f);
	testFileForSets.Set<double>("value test.double", 901.982);
	testFileForSets.Set<std::string>("value test.string", "new value");
	testFileForSets.Set<bool>("value test.boolean", true);

	std::vector<int> testIntVector;

	for (size_t i = 0; i < 10; i++) {
		testIntVector.push_back(i);
	}
	testFileForSets.SetArray<int>("array test.string array", testIntVector);

	// Close the program
	return 0;
}