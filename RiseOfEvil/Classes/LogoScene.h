#pragma once
#include "cocos2d.h"
USING_NS_CC;

class LogoScene : public cocos2d::Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LogoScene);
};