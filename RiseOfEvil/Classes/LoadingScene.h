#pragma once
#include "cocos2d.h"
USING_NS_CC;

class LoadingScene : public Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoadingScene);
};