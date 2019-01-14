#ifndef ARKENGINE_ANIMATION_H_
#define ARKENGINE_ANIMATION_H_

#include "rapidjson/document.h"
#include <iostream>
#include <fstream>
#include <string>

class JsonFile {
public:
	bool isFileLoaded = false;
	std::string fileName;

	JsonFile(const std::string& fileName = "NOT GIVEN");
	~JsonFile();
	
	template <typename T> T Get(const std::string& objectName);
	template<typename T> void Set(const std::string& objectName, const T& value);


private:
	std::string rawFileText;

	bool Load(const std::string& fileName);

};

JsonFile::JsonFile(const std::string& fileName) {
	if (fileName != "NOT GIVEN") {
		isFileLoaded = Load(fileName);
	}
	else {
		isFileLoaded = false;
		std::cout << "JsonFile.hpp >>>> File name was not supplied, no file was loaded" << std::endl;
	}
}

JsonFile::~JsonFile() {

}

bool JsonFile::Load(const std::string& fileName) {
	std::ifstream file;
	file.open(fileName);
	if (!file) {
		std::cout << "JsonFile.hpp >>>> Error opening file, Json File was not loaded" << std::endl;
		return false;
	}
	char c;
	while (file >> c) {
		rawFileText += c;
	}


	std::cout << "JsonFile.hpp >>>> File was not loaded" << std::endl;
	return false;
}


// Getters
template<typename T> T JsonFile::Get(const std::string& objectName) {
	std::cout << "JsonFile.hpp >>>> Default Template for Get, type specific ones should get called instead" << std::endl;
	return 0;
}
template<> int JsonFile::Get(const std::string& objectName) {
	return 0;
}
template<> std::string JsonFile::Get(const std::string& objectName) {
	return "";
}
template<> bool JsonFile::Get(const std::string& objectName) {
	return false;
}


// Setters
template<typename T> void JsonFile::Set(const std::string & objectName, const T & value) {
	std::cout << "JsonFile.hpp >>>> Default Template for Set, type specific ones should get called instead" << std::endl;
	return 0;
}
template<> void JsonFile::Set(const std::string & objectName, const std::string& value) {

}
template<> void JsonFile::Set(const std::string & objectName, const int& value) {

}
template<> void JsonFile::Set(const std::string & objectName, const bool& value) {

}
#endif