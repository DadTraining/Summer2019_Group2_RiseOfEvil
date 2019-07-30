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
	Monster * neighborMonster;
	float time = 0;
	float countTimeToPause = 0;
	float countTimeToAttack = 0;
	float countTimeToReduceHP = 0;
	float countTimeToBuildTower = 0;
	float countTimeToIncreaseSpeedMonster = 0;
	int currentGold;
	int currentStage;
	int numOfWave;
	int monsterIndex = 0;
	int road1TotalPoint;
	int road2TotalPoint;
	int typeOfTowerPrepairToBuild;
	Menu *menu;
	MenuItemImage *archerIcon;
	MenuItemImage *magicIcon;
	MenuItemImage *slowIcon;
	MenuItemImage *barrackIcon;
	MenuItemImage *boombardIcon;
	MenuItemImage *cancelMenu;
	Sprite *pause_bg;
	Sprite* canBuild;
	Sprite* gameover_bg;
	Sprite* cannotBuild;
	Vec2 touchLocation;	
	Vec2 point;
	Tower * TowerBefore;
	Tower * towerChoosing;
	Label* goldLabel;
	Label* startLabel;
	Label* messageWaveLabel;
	Label* showHowToBuildTower;
	Sprite * towerArcherDetails;
	Sprite * towerMagicDetails;
	Sprite * towerSlowDetails;
	Sprite * towerBoombardDetails;
	Sprite * towerBarrackDetails;
	Sprite * Flag;
	Sprite * goldFrame;
	Sprite* TowerFake;
	Sprite* rangeBullet;
	Sprite* rangeFakeTower;
	Sprite* hpBgSprite;
	ProgressTimer *hpBar;
	ui::Button *moreGoldBtn;
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
	bool checkMonsterAttack = false;
	bool checkTouchBuildTowerFake = false;
	bool checkClickBuildButton = false;
	bool checkgameover = false;
	bool checkFindMonster = false;
	vector<Monster*> m_listMonsterSoldierFound;
public:
	static Scene* createScene();
	virtual bool init() override;
	void update(float deltaTime) override;
	Tower * tower;
	void ClickPauseButton();
	void ExitPauseMenu();
	void restart();
	void returnToMainMenu();
	void BuildTower();
	void createmenu(Vec2 point);
	bool MonsterAttack(Monster*);
	Monster* SoldierFindMonster(Soldier*);
	bool SoldierAttack(Soldier*, Monster*);
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
	void moreGold();
	void BuildTowerFake(int type);
	void LoadingBuildTower();
	CREATE_FUNC(WorldScene1);
};
