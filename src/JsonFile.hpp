#ifndef PARSEJSON_JSONFILE_H_
#define PARSEJSON_JSONFILE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidjson/document.h"
#include <rapidjson/istreamwrapper.h>

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
	std::string rawFileText;

	bool Load(const std::string& fileName);
	std::vector<std::string> SplitString(const std::string& stringToSplit, const char& splitToken);

};

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

bool JsonFile::Load(const std::string& fileName) {
	std::ifstream fileStream(fileName);
	rapidjson::IStreamWrapper inputStream(fileStream);
	jsonDocument = new rapidjson::Document();
	jsonDocument->ParseStream(inputStream);

	if (jsonDocument->HasParseError()) {
		std::cout << "JsonFile.hpp >>>> File: " << fileName << " was not loaded" << std::endl;
		std::cout << "JsonFile.hpp >>>> Parser Errors: " << rapidjson::GetParseErrorFunc(jsonDocument) << std::endl;
		return false;
	}
	else {
		std::cout << "JsonFile.hpp >>>> File: " << fileName << " was loaded successfully" << std::endl;
		return true;
	}
}
std::vector<std::string> JsonFile::SplitString(const std::string & stringToSplit, const char & splitToken) {
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


// Getters
template<typename T> inline T JsonFile::Get(const std::string& objectName) {
	std::cout << "JsonFile.hpp >>>> Default Template for Get, type specific ones should get called instead" << std::endl;
	return 0;
}
template<> inline int JsonFile::Get(const std::string& objectName) {
	std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<int> - Target: '" << objectName << "'" << std::endl;
	std::vector<std::string> splitString = SplitString(objectName, '.');	// this gives us the stack of node names to use to traverse the json file's structure, e.g. root.head.value
	int returnValue = NULL;

	std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<int> - Accessing object/key: '" << splitString[0] << "'" << std::endl;
	rapidjson::Value* value = &(*jsonDocument)[splitString[0].c_str()];
	const size_t sizeOfSplitString = splitString.size();
	for (size_t i = 1; i < sizeOfSplitString; i++) {
		if (!value->IsArray()) {
			std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<int> - Accessing object/key: '" << splitString[i] << "'" << std::endl;
			value = &(*value)[splitString[i].c_str()];
		}
		else {
			std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<int> - Accessing Array element: '" << splitString[i] << "'" << std::endl;
			value = &(*value)[std::stoi(splitString[i])];
		}
	}
	if (!value->IsObject()) {
		returnValue = value->GetInt();
	}
	else {
		std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<int> tried to return an object" << std::endl;
	}

	return returnValue;
}
template<> inline float JsonFile::Get(const std::string& objectName) {
	std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<float> - Target: '" << objectName << "'" << std::endl;
	std::vector<std::string> splitString = SplitString(objectName, '.');	// this gives us the stack of node names to use to traverse the json file's structure, e.g. root.head.value
	float returnValue = NULL;

	std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<int> - Accessing object/key: '" << splitString[0] << "'" << std::endl;
	rapidjson::Value* value = &(*jsonDocument)[splitString[0].c_str()];
	const size_t sizeOfSplitString = splitString.size();
	for (size_t i = 1; i < sizeOfSplitString; i++) {
		if (!value->IsArray()) {
			std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<float> - Accessing object/key: '" << splitString[i] << "'" << std::endl;
			value = &(*value)[splitString[i].c_str()];
		}
		else {
			std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<float> - Accessing Array element: '" << splitString[i] << "'" << std::endl;
			value = &(*value)[std::stoi(splitString[i])];
		}
	}
	if (!value->IsObject()) {
		returnValue = value->GetFloat();
	}
	else {
		std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<float> tried to return an object" << std::endl;
	}

	return returnValue;
}
template<> inline double JsonFile::Get(const std::string& objectName) {
	std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<double> - Target: '" << objectName << "'" << std::endl;
	std::vector<std::string> splitString = SplitString(objectName, '.');	// this gives us the stack of node names to use to traverse the json file's structure, e.g. root.head.value
	double returnValue = NULL;

	std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<double> - Accessing object/key: '" << splitString[0] << "'" << std::endl;
	rapidjson::Value* value = &(*jsonDocument)[splitString[0].c_str()];
	const size_t sizeOfSplitString = splitString.size();
	for (size_t i = 1; i < sizeOfSplitString; i++) {
		if (!value->IsArray()) {
			std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<double> - Accessing object/key: '" << splitString[i] << "'" << std::endl;
			value = &(*value)[splitString[i].c_str()];
		}
		else {
			std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<double> - Accessing Array element: '" << splitString[i] << "'" << std::endl;
			value = &(*value)[std::stoi(splitString[i])];
		}
	}
	if (!value->IsObject()) {
		returnValue = value->GetDouble();
	}
	else {
		std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<double> tried to return an object" << std::endl;
	}

	return returnValue;
}
template<> inline std::string JsonFile::Get(const std::string& objectName) {
	std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<std::string> - Target: '" << objectName << "'" << std::endl;
	std::vector<std::string> splitString = SplitString(objectName, '.');	// this gives us the stack of node names to use to traverse the json file's structure, e.g. root.head.value
	std::string returnValue = "";

	std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<std::string> - Accessing object/key: '" << splitString[0] << "'" << std::endl;
	rapidjson::Value* value = &(*jsonDocument)[splitString[0].c_str()];
	const size_t sizeOfSplitString = splitString.size();
	for (size_t i = 1; i < sizeOfSplitString; i++) {
		if (!value->IsArray()) {
			std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<std::string> - Accessing object/key: '" << splitString[i] << "'" << std::endl;
			value = &(*value)[splitString[i].c_str()];
		}
		else {
			std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<std::string> - Accessing Array element: '" << splitString[i] << "'" << std::endl;
			value = &(*value)[std::stoi(splitString[i])];
		}
	}
	if (!value->IsObject()) {
		returnValue = value->GetString();
	}
	else {
		std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<std::string> tried to return an object" << std::endl;
	}

	return returnValue;
}
template<> inline bool JsonFile::Get(const std::string& objectName) {
	std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<bool> - Target: '" << objectName << "'" << std::endl;
	std::vector<std::string> splitString = SplitString(objectName, '.');	// this gives us the stack of node names to use to traverse the json file's structure, e.g. root.head.value
	bool returnValue = false;

	std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<bool> - Accessing object/key: '" << splitString[0] << "'" << std::endl;
	rapidjson::Value* value = &(*jsonDocument)[splitString[0].c_str()];
	const size_t sizeOfSplitString = splitString.size();
	for (size_t i = 1; i < sizeOfSplitString; i++) {
		if (!value->IsArray()) {
			std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<bool> - Accessing object/key: '" << splitString[i] << "'" << std::endl;
			value = &(*value)[splitString[i].c_str()];
		}
		else {
			std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<bool> - Accessing Array element: '" << splitString[i] << "'" << std::endl;
			value = &(*value)[std::stoi(splitString[i])];
		}
	}
	if (!value->IsObject()) {
		returnValue = value->GetBool();
	}
	else {
		std::cout << "JsonFile.hpp >>>> File: " << fileName << " Get<bool> tried to return an object" << std::endl;
	}

	return returnValue;
}

// Setters= 
template<typename T> inline void JsonFile::Set(const std::string & objectName, const T & value) {
	std::cout << "JsonFile.hpp >>>> Default Template for Set, type specific ones should get called instead" << std::endl;
	return 0;
}
template<> inline void JsonFile::Set(const std::string & objectName, const int& value) {

}
template<> inline void JsonFile::Set(const std::string & objectName, const float& value) {

}
template<> inline void JsonFile::Set(const std::string & objectName, const double& value) {

}
template<> inline void JsonFile::Set(const std::string & objectName, const std::string& value) {

}
template<> inline void JsonFile::Set(const std::string & objectName, const bool& value) {

}
#endif