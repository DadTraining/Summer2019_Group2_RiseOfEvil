#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
class GameMenuScene : public cocos2d::Scene
{
private:
	//bool checkTouch;
	ui::Button *btnNewGame;
	ui::Button *btnLoadGame;
	ui::Button *btnCredit;
	ui::Button *btnCompaign;
	ui::Button *btnSurvival;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void GoToTableChooseMode();
	CREATE_FUNC(GameMenuScene);
};
