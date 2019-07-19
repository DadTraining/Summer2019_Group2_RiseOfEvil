#pragma once
#include "cocos2d.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace cocos2d;
class Wave 
{
private:
	vector<int> Wave1;
	vector<int> Wave2;
public:
	Wave();
	~Wave();
	void Load();
	vector<int> getWave(int);
};