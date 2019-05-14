#include "FileUtilities.h"

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

const std::string FileUtil::getContents(std::string filePath) {
	std::ifstream inFile(filePath);
	if (!inFile.is_open()) {
		printf("Unable to open file: ");
	}

	std::stringstream string;

	string << inFile.rdbuf();
	return string.str();
}