#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Objects.h"
#include "Monster.h"
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
	float range = 250;
	float timeDelay = 0;
public:
	void Init();
	Tower(Layer* layer, int, Vec2);
	Sprite * GetSprite();
	void Shoot(Monster * monster);
	void Update(float deltaTime, Monster* monster);
	float GetRange();
};