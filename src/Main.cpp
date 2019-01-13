#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void enterObject(const rapidjson::Value &obj, size_t indent = 0) {
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

int main() {
	std::ifstream file;
	file.open("content/engine.json");
	if (!file) {
		std::cout << "Error opening file" << std::endl;
		exit(1);   // call system to stop
	}
	char c;
	std::string fileText;
	while (file >> c) {
		fileText += c;
	}

	// 1. Parse a JSON string into DOM.
	rapidjson::Document document;
	document.Parse(fileText.c_str());



	enterObject(document, 4);



	return 0;
}