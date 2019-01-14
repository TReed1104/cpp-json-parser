#ifndef PARSEJSON_JSONFILE_H_
#define PARSEJSON_JSONFILE_H_

#include <iostream>
#include <fstream>
#include <string>
#include "rapidjson/document.h"
#include <rapidjson/istreamwrapper.h>

class JsonFile {
public:
	bool isFileLoaded = false;
	std::string fileName;

	JsonFile(const std::string& fileName = "NOT GIVEN");
	~JsonFile();
	
	template <typename T> T Get(const std::string& objectName);
	template<typename T> void Set(const std::string& objectName, const T& value);


private:
	rapidjson::Document* jsonDocument;
	std::string rawFileText;

	bool Load(const std::string& fileName);
	void enterObject(const rapidjson::Value &obj, size_t indent = 0);

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
	
	std::cout << "JsonFile.hpp >>>> File was not loaded" << std::endl;
	return false;
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