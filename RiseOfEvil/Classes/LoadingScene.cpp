#include "LoadingScene.h"
#include "ui/CocosGUI.h"
#include "MainMenuScene.h"

Scene * LoadingScene::createScene()
{
	return LoadingScene::create();
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//create loadingScene background
	auto loading_bg = Sprite::create("res/Sprites/loading_bg.jpg");
	loading_bg->setScaleX(visibleSize.width / loading_bg->getContentSize().width);
	loading_bg->setScaleY(visibleSize.height / loading_bg->getContentSize().height);
	loading_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(loading_bg, 0);

	//create loadingbar background
	auto loadingBar_bg = Sprite::create("res/LoadingScene/loadingbar_bg.png");
	loadingBar_bg->setScaleX(3);
	loadingBar_bg->setScaleY(0.1);
	loadingBar_bg->setPosition(Vec2(visibleSize.width / 2, 100));
	addChild(loadingBar_bg);

	//create loadingbar
	static auto loadingbar = ui::LoadingBar::create("res/LoadingScene/loadingbar.png");
	loadingbar->setScaleX(3.08);
	loadingbar->setScaleY(0.1);
	loadingbar->setPercent(0);
	loadingbar->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingbar->setPosition(loadingBar_bg->getPosition());
	addChild(loadingbar);

	//update Loading Bar
	auto updateLoadingBar = CallFunc::create([]() {
		if (loadingbar->getPercent() < 100)
		{
			loadingbar->setPercent(loadingbar->getPercent() + 0.4);
		}
	});

	auto sequenceRunUpdateLoadingBar =	Sequence::createWithTwoActions(updateLoadingBar, DelayTime::create(0.05f));

	auto repeat = Repeat::create(sequenceRunUpdateLoadingBar, 333);
	auto sequencedelayupdate = Sequence::create(DelayTime::create(1.5), repeat , nullptr);
	loadingbar->runAction(sequencedelayupdate);

	//replace MainMenuScene
	auto gotoNext = CallFunc::create([]() {
		Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenuScene::create(), Color3B(0, 0, 0)));
	});
	auto sq_replaceScene = Sequence::create(DelayTime::create(14), gotoNext, nullptr);
	runAction(sq_replaceScene);

	return true;
}
