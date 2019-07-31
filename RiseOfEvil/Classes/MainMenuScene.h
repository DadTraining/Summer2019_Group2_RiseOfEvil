#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;
using namespace cocos2d;
class MainMenuScene : public cocos2d::Scene
{
private:
	//bool checkTouch;
	ui::Button * btnNewGame;
	ui::Button * btnLoadGame;
	ui::Button * btnCredits;
	ui::Button * btnCampaign;
	ui::Button * btnSurvival;
	ui::Button * btnBack;
	SimpleAudioEngine *touchMusic;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float) override;
	void GoToWorldMap();
	void FadeinChoose();
	void FadeoutChoose();
	CREATE_FUNC(MainMenuScene);
};
