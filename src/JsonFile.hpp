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
	void enterObject(const rapidjson::Value &obj, size_t indent = 0);
	std::vector<std::string> SplitString(const std::string& stringToSplit, const char& splitToken);

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
void JsonFile::enterObject(const rapidjson::Value & obj, size_t indent) {
	if (obj.IsObject()) {
		for (rapidjson::Value::ConstMemberIterator itr = obj.MemberBegin(); itr != obj.MemberEnd(); ++itr) {   //iterate through object   
			const rapidjson::Value& objName = obj[itr->name.GetString()];
			for (size_t i = 0; i != indent; ++i) {
				std::cout << " ";
			}

			std::cout << itr->name.GetString() << ": "; //key name

			if (itr->value.IsNumber()) {
				std::cout << itr->value.GetInt();
			}
			else if (itr->value.IsString()) {
				std::cout << itr->value.GetString();
			}
			else if (itr->value.IsBool()) {
				std::cout << itr->value.GetBool();
			}
			else if (itr->value.IsArray()) {
				bool isFirst = true;
				for (rapidjson::SizeType i = 0; i < itr->value.Size(); i++) {
					if (itr->value[i].IsNumber()) {
						std::cout << itr->value[i].GetInt();
					}
					else if (itr->value[i].IsString()) {
						std::cout << itr->value[i].GetString();
					}
					else if (itr->value[i].IsBool()) {
						std::cout << itr->value[i].GetBool();
					}
					else if (itr->value[i].IsObject()) {

						const rapidjson::Value& m = itr->value[i];
						for (auto& v : m.GetObject()) {
							if (isFirst) {
								std::cout << "\n";
								isFirst = false;
							}
							if (m[v.name.GetString()].IsNumber()) {
								std::cout << v.name.GetString() << ": " << m[v.name.GetString()].GetInt();
							}
							else if (m[v.name.GetString()].IsString()) {
								std::cout << v.name.GetString() << ": " << m[v.name.GetString()].GetString();
							}
							else if (m[v.name.GetString()].IsBool()) {
								std::cout << v.name.GetString() << ": " << m[v.name.GetString()].GetBool();
							}
							else  if (m[v.name.GetString()].IsArray()) {
								std::cout << "Nested Array";
							}
							else  if (m[v.name.GetString()].IsObject()) {
								for (size_t i = 0; i != indent + 4; ++i) {
									std::cout << " ";
								}
								std::cout << v.name.GetString() << ": " << std::endl;
								enterObject(m[v.name.GetString()], indent + 8);
							}
						}
					}
				}
			}
			std::cout << std::endl;
			enterObject(objName, indent + 4);
		}
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
	// this gives us the stack of node names to use to traverse the json file's structure, e.g. root.head.value
	std::vector<std::string> splitString = SplitString(objectName, '.');

	return 0;
}
template<> inline float JsonFile::Get(const std::string& objectName) {
	// this gives us the stack of node names to use to traverse the json file's structure, e.g. root.head.value
	std::vector<std::string> splitString = SplitString(objectName, '.');

	return 0.0f;
}
template<> inline std::string JsonFile::Get(const std::string& objectName) {
	// this gives us the stack of node names to use to traverse the json file's structure, e.g. root.head.value
	std::vector<std::string> splitString = SplitString(objectName, '.');

	return "";
}
template<> inline bool JsonFile::Get(const std::string& objectName) {
	// this gives us the stack of node names to use to traverse the json file's structure, e.g. root.head.value
	std::vector<std::string> splitString = SplitString(objectName, '.');

	return false;
}

// Setters
template<typename T> inline void JsonFile::Set(const std::string & objectName, const T & value) {
	std::cout << "JsonFile.hpp >>>> Default Template for Set, type specific ones should get called instead" << std::endl;
	return 0;
}
template<> inline void JsonFile::Set(const std::string & objectName, const int& value) {

}
template<> inline void JsonFile::Set(const std::string & objectName, const float& value) {

}
template<> inline void JsonFile::Set(const std::string & objectName, const std::string& value) {

}
template<> inline void JsonFile::Set(const std::string & objectName, const bool& value) {

}
#endif