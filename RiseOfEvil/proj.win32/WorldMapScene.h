#pragma once
#pragma once
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class WorldMapScene : public Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WorldMapScene);
	void add_star(Vec2 vec, int score);
	void GoToWorldScene1();
	void GoToMainMenu();
};