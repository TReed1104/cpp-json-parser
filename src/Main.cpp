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
	std::vector<int> getIntArrayTest = testFileForGets.GetVector<int>("array test.int array");
	std::vector<float> getFloatArrayTest = testFileForGets.GetVector<float>("array test.float array");
	std::vector<double> getDoubleArrayTest = testFileForGets.GetVector<double>("array test.double array");
	std::vector<std::string> getStringArrayTest = testFileForGets.GetVector<std::string>("array test.string array");
	std::vector<bool> getBoolArrayTest = testFileForGets.GetVector<bool>("array test.boolean array");
	
	// Load the File
	JsonFile testFileForSets = JsonFile("content/set_test.json");
	testFileForSets.Set<int>("value test.int", 111);
	testFileForSets.Set<float>("value test.float", 101.89f);
	testFileForSets.Set<double>("value test.double", 901.982);
	testFileForSets.Set<std::string>("value test.string", "new value");
	testFileForSets.Set<bool>("value test.boolean", true);

	// Test SetVector<T>()
	std::vector<int> intVector;
	for (size_t i = 0; i < 10; i++) {
		intVector.push_back(i);
	}
	testFileForSets.Set<int>("array test.int array", intVector);
	std::vector<std::string> stringVector;
	stringVector.push_back("one");
	stringVector.push_back("two");
	stringVector.push_back("three");
	testFileForSets.Set<std::string>("array test.string array", stringVector);
	std::vector<bool> boolVector;
	boolVector.push_back(true);
	boolVector.push_back(false);
	testFileForSets.Set<bool>("array test.boolean array", boolVector);

	// Insert tests
	testFileForSets.Insert<int>("", "insert int test", 5);
	testFileForSets.Insert<int>("", "insert int test", 5);					// Checking if we have already added this key, should produce an error output
	testFileForSets.Insert<int>("value test", "insert int test", 5);
	testFileForSets.Insert<int>("value test.int", "insert int test", 5);	// Will fail because value test.int is a value, not an object
	testFileForSets.Insert<float>("", "insert float test", 5.0f);
	testFileForSets.Insert<double>("", "insert double test", 5.0);
	testFileForSets.Insert<std::string>("", "insert string test", "example");
	testFileForSets.Insert<bool>("", "insert bool test", false);

	testFileForSets.Insert<int>("", "insert array int test", intVector);
	testFileForSets.Insert<int>("array test", "insert array int test", intVector);
	testFileForSets.Insert<bool>("", "insert array bool test", boolVector);
	testFileForSets.Insert<std::string>("", "insert array string test", stringVector);

	testFileForSets.Remove("value test.int");
	testFileForSets.Remove("array test.int array.2");

	// Close the program
	return 0;
}