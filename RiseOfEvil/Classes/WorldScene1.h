#pragma once
#include "cocos2d.h"
#include "Tower.h"
#include "Monster.h"
#include "ui/CocosGUI.h"
#include "Tower.h"
#include "Wave.h"
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
	Wave* wave;
	TMXTiledMap* mTileMap;
	vector<Monster*> listMonster;
	vector<Monster*>listTemp;
	vector<Monster*> Wave1;
	vector<Monster*> Wave2;
	vector<Vec2> listPoint;
	vector<Vec2> listPoint2;
	vector<Vec2> listLocationTower;
	vector<Tower*>listTower;
	PhysicsBody *body;
	float time;
	int currentGold;
	int numOfWave;
	Menu *menu;
	MenuItemImage *archerIcon;
	MenuItemImage *magicIcon;
	MenuItemImage *slowIcon;
	MenuItemImage *barrackIcon;
	MenuItemImage *boombardIcon;
	MenuItemImage *cancelMenu;
	Sprite *pause_bg;
	Sprite* canBuild;
	Sprite* cannotBuild;
	Vec2 touchLocation;	
	Vec2 point;
	Tower * TowerBefore;
	Tower * towerChoosing;
	Label* goldLabel;
	Label* startLabel;
	Sprite * towerArcherDetails;
	Sprite * towerMagicDetails;
	Sprite * towerSlowDetails;
	Sprite * towerBoombardDetails;
	Sprite * towerBarrackDetails;
	Sprite * Flag;
	ui::Button *resumeBtn;
	ui::Button *restartBtn;
	ui::Button *mainmenuBtn;
	ui::Button *buyTower;
	ui::Button *startBTN;
	bool releaseMonster = false;
	bool touchOut = false;
	bool touchIn = false;
	bool start = false;
	bool pause = false;
	bool checkClick = false;
public:
	static Scene* createScene();
	virtual bool init() override;
	void update(float deltaTime) override;
	Tower * tower;
	void ClickPauseButton();
	void ExitPauseMenu();
	void restart();
	void returnToMainMenu();
	void BuildTower(Ref*,int);
	void createmenu(Vec2 point);
	void moveFlag(Vec2 Pos);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch * touch, Event * event);
	void onTouchEnded(Touch * touch, Event * event);
	bool checkLocationBuildTower(Vec2 newPoint);
	void StatusMenu(bool);
	void GetTowerDetails(int);
	void Warning();
	void startGame();
	void startWave();
	CREATE_FUNC(WorldScene1);
};