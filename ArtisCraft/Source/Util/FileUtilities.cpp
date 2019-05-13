#include "FileUtilities.h"

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string FileUtil::getContents(std::string filePath) {
	std::ifstream inFile(filePath);
	if (!inFile.is_open()) {
		printf("Unable to open file %s", filePath);
	}

	std::stringstream string;

	string << inFile.rdbuf();
	return string.str();
}