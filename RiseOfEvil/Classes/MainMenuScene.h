#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
class MainMenuScene : public cocos2d::Scene
{
private:
	//bool checkTouch;
	ui::Button * btnNewGame;
	ui::Button * btnLoadGame;
	ui::Button * btnCredits;
	ui::Button * btnCompaign;
	ui::Button * btnSurvival;
	ui::Button * btnBack;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void GoToChooseMode();
	void GoToWorldMap();
	void GoToMenu();
	void ActionMode();
	void ActionMenu();
	void BackMenu();
	CREATE_FUNC(MainMenuScene);
};
