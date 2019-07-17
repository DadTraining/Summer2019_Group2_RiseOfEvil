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
	MenuItemImage *cancelMenu;
	Menu *menu;
	Sprite* canBuild;
	Sprite* cannotBuild;
	Vec2 touchLocation;
	bool checkClick = false;
	Tower * TowerBefore;
	Tower * towerChoosing;
	Vec2 point;
	bool touchOut = false;
	bool touchIn = false;
public:
	static Scene* createScene();
	virtual bool init() override;
	void update(float deltaTime) override;
	Tower * tower;
	void FadeInPause();
	void FadeOutPause();
	void returnToMainMenu();
	void BuildTower(int);
	void createmenu(Vec2 point);
	void createMenuTower(Vec2 Point, bool check);
	void moveFlag(Vec2 Pos);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch * touch, Event * event);
	void onTouchEnded(Touch * touch, Event * event);
	bool checkLocationBuildTower(Vec2 newPoint);
	void StatusMenu(bool);
	CREATE_FUNC(WorldScene1);
};