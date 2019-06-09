#include "BlockData.h"
#include <fstream>

BlockData::BlockData(std::string fileName)
{
	std::ifstream inFile("../Resources/BlockData/" + fileName + ".block");

	if (!inFile.is_open()) {
		throw std::runtime_error("Unable to open block file: " + fileName);
	}

	
	std::string line;
	while (std::getline(inFile, line)) {
		if (line == "TexTop")
		{
			int x, y;
			inFile >> x >> y;
			_data.texTopCoord = { x, y };
		}
		else if (line == "TexSide")
		{
			int x, y;
			inFile >> x >> y;
			_data.texSideCoord = { x, y };
		}
		else if (line == "TexBottom")
		{
			int x, y;
			inFile >> x >> y;
			_data.texBottomCoord = { x, y };
		}
		else if (line == "TexAll")
		{
			int x, y;
			inFile >> x >> y;
			_data.texTopCoord = { x, y };
			_data.texSideCoord = { x, y };
			_data.texBottomCoord = { x, y };
		}
	}
}

const TextureData & BlockData::getTextureData() const
{
	return _data;
}
