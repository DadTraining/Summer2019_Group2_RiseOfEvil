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


using namespace std;
using namespace cocos2d;
class Tower : public Objects
{
private:
	vector <Bullet *> listBullet;
	vector <Soldier *>listSoldier;
	//Sprite * CircleMenu;
	//Sprite * FlagIcon;
	Menu * circleMenu;
	MenuItemImage * flagIcon;
	MenuItemImage * circleIcon;
	float m_range = 250;
	float timeDelay = 0;
	float m_attackSpeed;
	int m_gold;
	bool checkTowerShoot = false;
	float countTimeToDamage = 0;
	bool checkTouchFlag = false;
	bool checkTypeTowerBarrack = false;
	Sprite * rangeBarrackTower;
public:
	void Init();
	Tower(Layer* layer, int, Vec2);
	Sprite * GetSprite();
	void Shoot(Monster * monster);
	void Update(float deltaTime, Monster* monster);
	float GetRange();
	float GetAttackSpeed();
	void SetAttackSpeed(float);
	int GetGold();
	void SetGold(int);
	int GetDamage();
	//Sprite * GetCircleMenu();
	//Sprite * GetFlagIcon();
	void FadeInPause();
	void FadeOutPause();
	bool GetCheckTouchFlag();
	void SetCheckTouchFlag(bool);
	Sprite * GetRangeBarrackTower();
	bool GetCheckTypeTowerBarrack();
	vector<Soldier *> GetListSoldier();
};