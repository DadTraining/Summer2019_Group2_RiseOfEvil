#pragma once
#include "cocos2d.h"
#include "Tower.h"
#include "ui/CocosGUI.h"
#define E  1
#define W  2
#define S  3
#define N  4
#define SE 5
#define NE 6
#define NW 7
#define SW 8
using namespace cocos2d;
USING_NS_CC;
class WorldScene1 : public Layer
{
private:
	TMXTiledMap* mTileMap;
	PhysicsBody *body;
	ui::Button *resumeBtn;
	ui::Button *restartBtn;
	ui::Button *mainmenuBtn;
	Sprite *pause_bg;
public:
	static Scene* createScene();
	virtual bool init() override;
	void update(float deltaTime) override;
	Sprite * monster;
	Animation *createAnimation(std::string prefixName, int pFrameBegin, int pFrameEnd, float delay);
	Animation *animation;
	int nextPoint;
	Tower * tower;
	void run(Vec2 point);
	void action(int direction, Sprite *);
	void FadeinPause();
	void FadeoutPause();
	CREATE_FUNC(WorldScene1);
};