#pragma once
#include "cocos2d.h"
#include "Tower.h"
#include "Monster.h"
#include "ui/CocosGUI.h"
#include "Tower.h"
#define BLOOD_BAR 9
#define E  1
#define W  2
#define S  3
#define N  4
#define SE 5
#define NE 6
#define NW 7
#define SW 8
using namespace cocos2d;
using namespace std;
USING_NS_CC;
class WorldScene1 : public Layer
{
private:
	TMXTiledMap* mTileMap;
	vector<Vec2> listLocationTower;
	vector<Monster*> listMonster;
	vector<Vec2> listPoint;
	vector<Tower*>listTower;
	PhysicsBody *body;
	ui::Button *resumeBtn;
	ui::Button *restartBtn;
	ui::Button *mainmenuBtn;
	Sprite *pause_bg;
	float time;
	MenuItemImage *archerIcon;
	MenuItemImage *magicIcon;
	MenuItemImage *slowIcon;
	MenuItemImage *barrackIcon;
	MenuItemImage *boombardIcon;
	Menu *menu;
	Sprite* canBuild;
	Sprite* cannotBuild;
	Vec2 touchLocation;
public:
	static Scene* createScene();
	virtual bool init() override;
	void update(float deltaTime) override;
	Tower * tower;
	void FadeInPause();
	void FadeOutPause();
	void returnToMainMenu();
	void BuildTower(int);
	bool onTouchBegan(Touch *touch, Event *event);
	bool checkLocationBuildTower(Vec2);
	void createmenu(Vec2 point);
	CREATE_FUNC(WorldScene1);
};