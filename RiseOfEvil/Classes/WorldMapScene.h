#pragma once
#pragma once
#pragma once
#include "cocos2d.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;
USING_NS_CC;

class WorldMapScene : public Scene
{
private:
	SimpleAudioEngine *touchMusic;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WorldMapScene);
	void add_star(Vec2 vec);
	void GoToMainMenu();
	void GoToUpgrade();
	void GoToStage(Ref*,int);
};