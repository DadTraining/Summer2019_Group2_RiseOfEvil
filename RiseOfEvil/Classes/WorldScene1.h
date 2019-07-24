#pragma once
#include "cocos2d.h"
#include "Tower.h"
#include "Monster.h"
#include "ui/CocosGUI.h"
#include "Tower.h"
#include "Wave.h"
#include "Soldier.h"
#include "Crystal.h"
#include <algorithm>
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
	//Camera *cam;
	Crystal* crystal;
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
	float delay;
	Monster * nearestMonster;
	float time;
	float countTimeToPause;
	float countTimeToAttack = 0;
	int currentGold;
	int numOfWave;
	int monsterIndex = 0;
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
	Label* messageWaveLabel;
	Sprite * towerArcherDetails;
	Sprite * towerMagicDetails;
	Sprite * towerSlowDetails;
	Sprite * towerBoombardDetails;
	Sprite * towerBarrackDetails;
	Sprite * Flag;
	Sprite * goldFrame;
	ui::Button *resumeBtn;
	ui::Button *restartBtn;
	ui::Button *worldMapBtn;
	ui::Button *buyTower;
	ui::Button *startBTN;
	ui::Button *startWaveBTN;
	ui::Button *startWaveBTN2;
	ui::Button *muteBTN;
	ui::Button *pauseBtn;
	bool releaseMonster = false;
	bool touchOut = false;
	bool touchIn = false;
	bool start = false;
	bool pause = false;
	bool checkClick = false;
	bool clickPause = false;
	bool checkAttack = false;
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
	void MonsterAttack(Monster*, Vec2);
	void MonsterMove(Monster*, int, bool, float, float);
	void moveFlag(Vec2 Pos);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch * touch, Event * event);
	void onTouchEnded(Touch * touch, Event * event);
	bool checkLocationBuildTower(Vec2 newPoint);
	void StatusMenu(bool);
	void GetTowerDetails(int);
	void Warning();
	void startWave();
	void muteSound();
	void exit();
	CREATE_FUNC(WorldScene1);
};
