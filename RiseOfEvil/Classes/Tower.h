#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Objects.h"
#include "Monster.h"
#include "Soldier.h"
#include <iostream>

#define ARROW_TOWER 1
#define MAGIC_TOWER 2
#define SLOW_TOWER 3
#define BOMBARD_TOWER 4
#define BARRACKS_TOWER 5

using namespace cocos2d;
using namespace std;
class Tower : public Objects
{
private:
	vector <Bullet*> listBullet;
	vector <Soldier*> listSoldier;
	vector <Monster*> listMonsterInRange;
	vector <Monster*> listMonsterNeighbor;
	Menu * circleMenu;
	MenuItemImage * flagIcon;
	MenuItemImage * circleIcon;
	MenuItemImage * upgradeIcon;
	MenuItemImage * sellIcon;
	float m_range = 250;
	float timeDelay = 0;
	float m_attackSpeed;
	int m_gold;
	int m_level;
	bool checkTowerShoot = false;
	bool checkTouchFlag = false;
	bool checkTypeTowerBarrack = false;
	bool isSell = false;
	bool requestUpdate = false;
	Sprite * rangeBarrackTower;
	Sprite * bufferBarrackTower;
	Point posBullet;
	int numberOfSoldier;
public:
	void Init();
	Tower(Layer* layer, int, Vec2);
	~Tower();
	Sprite * GetSprite();
	void Shoot(Monster*);
	void Update(float deltaTime, Monster*);
	float GetRange();
	float GetAttackSpeed();
	void SetAttackSpeed(float);
	int GetGold();
	void SetGold(int);
	int GetDamage();
	void ShowCircleMenu();
	void HideCircleMenu();
	bool GetCheckTouchFlag();
	int GetType();
	void SetCheckTouchFlag(bool);
	Sprite * GetRangeBarrackTower();
	bool GetCheckTypeTowerBarrack();
	vector<Soldier *> GetListSoldier();
	int GetTypeTower();
	bool GetCheckTowerShoot();
	void SetCheckTowerShoot(bool);
	vector<Monster*> GetlistMonsterInRange();
	vector<Monster*> GetListMonsterNeighbor();
	bool getIsSell();
	int getLevel();
	void upgrade();
	bool getRequestUpdate();
	void acceptUpdate(bool);
	MenuItemImage * getUpgradeIcon();
};