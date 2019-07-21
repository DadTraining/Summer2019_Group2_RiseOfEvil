#include "Wave.h"

Wave::Wave()
{
	Load();
}

Wave::~Wave()
{
}

void Wave::Load()
{
	auto content = FileUtils::getInstance()->getStringFromFile("Stage1Info.bin");
	istringstream f(content);
	int size;
	int type;
	f >> size;
	for (int i = 0; i < size; i++) {
		f >> type;
		Wave1.push_back(type);
	}
	f >> size;
	for (int i = 0; i < size; i++) {
		f >> type;
		Wave2.push_back(type);
	}
	f >> size;
	for (int i = 0; i < size; i++) {
		f >> type;
		Wave3.push_back(type);
	}
	f >> size;
	for (int i = 0; i < size; i++) {
		f >> type;
		Wave4.push_back(type);
	}
}

vector<int> Wave::getWave(int numOfWave)
{
	switch (numOfWave)
	{
	case 1:
		return Wave1;
		break;
	case 2:
		return Wave2;
		break;
	case 3:
		return Wave3;
		break;
	case 4:
		return Wave4;
		break;
	default:
		break;
	}
}
