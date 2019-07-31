#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Objects.h"
#include "Monster.h"
#include "Soldier.h"
#include "Skill.h"
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
	Layer *layer;
	vector <Bullet*> listBullet;
	vector <Soldier*> listSoldier;
	vector <Monster*> listMonsterInRange;
	vector <Monster*> listMonsterNeighbor;
	Menu * circleMenu;
	MenuItemImage * flagIcon;
	MenuItemImage * circleIcon;
	MenuItemImage * upgradeIcon;
	MenuItemImage * sellIcon;
	MenuItemImage * confirmIcon;
	MenuItemImage * skillIcon;
	float m_range = 250;
	float timeDelay = 0;
	float countTimeToDealDamage;
	float m_attackSpeed;
	float m_minimumAttackSpeed;
	int m_gold;
	int m_level;
	bool checkTowerShoot = false;
	bool checkTouchFlag = false;
	bool checkTypeTowerBarrack = false;
	bool isSell = false;
	bool requestUpdate = false;
	Sprite * rangeBarrackTower;
	Point posBullet;
	int numberOfSoldier;
	Monster *target = nullptr;
	Skill * towerSkill;
	float countTimeToReduceHPForBurnSkill = 0;
	float countTimeToIncreaseHP = 0;
	Label *priceUpgradeLabel;
	bool checkIncreaseAttackSpeedSkill = false;
	bool checkIncreaseAttackDamageSkill = false;
	bool checkBurnSkill = false;
	bool checkSlowSkill = false;
	Sprite * skillDetail;
	// to reset Tower after buff
	int baseMinnimumAtk;
	int baseMaximumAtk;
	float baseAttackSpeed;
public:
	void Init();
	Tower(Layer* layer, int, Vec2);
	~Tower();
	Sprite * GetSprite();
	void Shoot(vector<Monster*>);
	void Update(float deltaTime, vector<Monster*>);
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
	Label * getPriceUpgradeLabel();
	Monster * getTarget();
	void setTarget(Monster*);
	bool getStatusOfTarget();
	bool getIncreaseAttackSpeedSkill();
	bool getIncreaseAttackDamageSkill();
	void setIncreaseAttackSpeedSkill(bool);
	void setIncreaseAttackDamageSkill(bool);
	void slowSkill(vector<Monster*> listMonster);
	void burnSkill(vector<Monster*> listMonster, float deltaTime);
	void bossSkill(Monster * boss, vector<Monster *>listMonster, float deltaTime);
	void clickSellIcon();
	void confirmSell();
	float getMinimumAttackSpeed();
	Skill *getTowerSkill();
	void showDetailSkill();
	void resetTower(int);
	Sprite* getSkillDetails();
};