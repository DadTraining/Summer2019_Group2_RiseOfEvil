#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
class UpgradeScene : public Scene
{
private:
	Sprite *background;
	ui::Button *doneBtn;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(UpgradeScene);
	void BackToWorldMapScene();
};
