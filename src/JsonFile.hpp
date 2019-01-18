#ifndef PARSEJSON_JSONFILE_H_
#define PARSEJSON_JSONFILE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidjson/document.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/error/en.h>

class JsonFile {
public:
	bool isFileLoaded = false;
	std::string fileName;

	JsonFile(const std::string& fileName = "NOT GIVEN");
	~JsonFile();

	template <typename T> T Get(const std::string& objectName);
	template <typename T> void Set(const std::string& objectName, const T& value);


private:
	rapidjson::Document* jsonDocument;

	bool Load(const std::string& fileName);
	std::vector<std::string> SplitString(const std::string& stringToSplit, const char& splitToken);
	template <typename T> T TraverseJson(const std::string& objectName);
	template <typename T> T GetDefaultValue();
	template <typename T> T GetValue(const rapidjson::Value& object);

};

// Constructors & Deconstructors
JsonFile::JsonFile(const std::string& fileName) {
	this->fileName = fileName;
	if (fileName != "NOT GIVEN") {
		isFileLoaded = Load(fileName);
	}
	else {
		isFileLoaded = false;
		std::cout << "JsonFile.hpp >>>> File name was not supplied, no file was loaded" << std::endl;
	}
}
JsonFile::~JsonFile() {
	delete jsonDocument;
}

// Generl Class Functions
bool JsonFile::Load(const std::string& fileName) {
	std::ifstream fileStream(fileName);
	rapidjson::IStreamWrapper inputStream(fileStream);
	jsonDocument = new rapidjson::Document();
	jsonDocument->ParseStream(inputStream);

	if (jsonDocument->HasParseError()) {
		std::cout << "JsonFile.hpp >>>> File: " << fileName << " was not loaded" << std::endl;
		std::cout << "JsonFile.hpp >>>> Parser Errors: " << rapidjson::GetParseError_En(jsonDocument->GetParseError()) << std::endl;
		return false;
	}
	else {
		std::cout << "JsonFile.hpp >>>> File: " << fileName << " was loaded successfully" << std::endl;
		return true;
	}
}
std::vector<std::string> JsonFile::SplitString(const std::string& stringToSplit, const char& splitToken) {
	// Splits a string using the given splitToken, E.g. ""The.Cat.Sat.On.The.Mat" splits with token '.' into Vector[6] = {The, Cat, Sat, On, The, Mat};

	std::vector<std::string> splitString;	// Stores the split sections of string for the return.
	std::string currentSplit = "";			// Stores the current section being split off.

	size_t sizeOfStringArray = stringToSplit.size();			// .Size() of a const so it never changes and we store it once.
	for (size_t i = 0; i < sizeOfStringArray; i++) {
		char currentChar = stringToSplit.at(i);
		if (currentChar == splitToken) {
			splitString.push_back(currentSplit);
			currentSplit = "";
		}
		else {
			currentSplit += currentChar;
		}

		if (i == sizeOfStringArray - 1 && currentChar != splitToken) {
			// Catches the final section of string as there might not be a follow up split token.
			splitString.push_back(currentSplit);
		}
	}

	return splitString;

}
template<typename T> inline T JsonFile::TraverseJson(const std::string& objectName) {
	T result;
	std::vector<std::string> splitString = SplitString(objectName, '.');	// this gives us the stack of node names to use to traverse the json file's structure, e.g. root.head.value

	rapidjson::Value* value;
	if (jsonDocument->HasMember(splitString.front().c_str())) {
		value = &(*jsonDocument)[splitString.front().c_str()];				// Get the first object we are looking for
	}
	else {
		std::cout << "JsonFile.hpp >>>> Could not find key: " << splitString.front() << std::endl;
		return GetDefaultValue<T>();
	}
	// Iterate through our substrings to traverse the JSON DOM
	const size_t sizeOfSplitString = splitString.size();
	for (size_t i = 1; i < sizeOfSplitString; i++) {
		if (!value->IsArray()) {
			if (value->HasMember(splitString[i].c_str())) {
				value = &(*value)[splitString[i].c_str()];	// Get the first object we are looking for
			}
			else {
				std::cout << "JsonFile.hpp >>>> Could not find key: " << splitString[i] << std::endl;
				return GetDefaultValue<T>();
			}
		}
		else {
			// Point to the object/key/array at the indicated index in the array
			int arraySize = value->Size();
			int indexOfValue = 0;
			// try and convert the substring to an int, if not return default
			try {
				indexOfValue = std::stoi(splitString[i]);	// convert from our substring to our indexer
			}
			catch (...) {
				std::cout << "JsonFile.hpp >>>> " << objectName << " " << splitString[i] << " is invalid as an index value" << std::endl;
				return GetDefaultValue<T>();
			}
			// Check the value is accessible in the bounds of the array
			if (arraySize > 0) {
				if (arraySize > indexOfValue) {
					value = &(*value)[indexOfValue];
				}
				else {
					std::cout << "JsonFile.hpp >>>> " << objectName << " index: " << indexOfValue << " is out of bounds" << std::endl;
					return GetDefaultValue<T>();
				}
			}
			else {
				std::cout << "JsonFile.hpp >>>> " << objectName << " Array is empty" << std::endl;
				return GetDefaultValue<T>();
			}
		}
	}
	// Check we haven't ended up with a JSON object instead of a value
	if (!value->IsObject()) {
		result = GetValue<T>(*value);
	}
	return result;		// Return the found value or default value if not
}

// Get Default value Functions
template<typename T> inline T JsonFile::GetDefaultValue() {
	return 0;
}
template<> inline int JsonFile::GetDefaultValue() {
	return 0;
}
template<> inline float JsonFile::GetDefaultValue() {
	return 0.0f;
}
template<> inline double JsonFile::GetDefaultValue() {
	return 0.0;
}
template<> inline std::string JsonFile::GetDefaultValue() {
	return "";
}
template<> inline bool JsonFile::GetDefaultValue() {
	return false;
}

// Get value functions
template<typename T> inline T JsonFile::GetValue(const rapidjson::Value& object) {
	return GetDefaultValue<T>();
}
template<> inline int JsonFile::GetValue(const rapidjson::Value& object) {
	int result;
	if (object.IsInt()) {
		result = object.GetInt();	// Get the value to return
		return result;
	}
	else {
		std::cout << "JsonFile.hpp >>>> value is not an Int" << std::endl;
		return GetDefaultValue<int>();
	}
}
template<> inline float JsonFile::GetValue(const rapidjson::Value& object) {
	float result;
	if (object.IsFloat()) {
		result = object.GetFloat();	// Get the value to return
		return result;
	}
	else {
		std::cout << "JsonFile.hpp >>>> value is not a float" << std::endl;
		return GetDefaultValue<float>();
	}
}
template<> inline double JsonFile::GetValue(const rapidjson::Value& object) {
	double result;
	if (object.IsDouble()) {
		result = object.GetDouble();	// Get the value to return
		return result;
	}
	else {
		std::cout << "JsonFile.hpp >>>> value is not a double" << std::endl;
		return GetDefaultValue<double>();
	}
}
template<> inline std::string JsonFile::GetValue(const rapidjson::Value& object) {
	std::string result;
	if (object.IsString()) {
		result = object.GetString();	// Get the value to return
		return result;
	}
	else {
		std::cout << "JsonFile.hpp >>>> value is not a std::string" << std::endl;
		return GetDefaultValue<std::string>();
	}
}
template<> inline bool JsonFile::GetValue(const rapidjson::Value& object) {
	bool result;
	if (object.IsBool()) {
		result = object.GetBool();	// Get the value to return
		return result;
	}
	else {
		std::cout << "JsonFile.hpp >>>> value is not a boolean" << std::endl;
		return GetDefaultValue<bool>();
	}
}

// Get Functions
template<typename T> inline T JsonFile::Get(const std::string& objectName) {
	T result;
	if (isFileLoaded) {
		result = TraverseJson<T>(objectName);
	}
	else {
		result = GetDefaultValue<T>();
	}
	return result;
}

// Set Functions
template<typename T> inline void JsonFile::Set(const std::string& objectName, const T & value) {
	std::cout << "JsonFile.hpp >>>> Default Template for Set, type specific ones should get called instead" << std::endl;
	return 0;
}
template<> inline void JsonFile::Set(const std::string& objectName, const int& value) {

}
template<> inline void JsonFile::Set(const std::string& objectName, const float& value) {

}
template<> inline void JsonFile::Set(const std::string& objectName, const double& value) {

}
template<> inline void JsonFile::Set(const std::string& objectName, const std::string& value) {

}
template<> inline void JsonFile::Set(const std::string& objectName, const bool& value) {

}
#endif