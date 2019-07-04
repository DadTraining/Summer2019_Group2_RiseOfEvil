#include "LogoScene.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene * LogoScene::createScene()
{
	return LogoScene::create();
}

bool LogoScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto logo = Sprite::create("logo.png");
	logo->setAnchorPoint(Vec2(0.5, 0.5));
	logo->setScaleX(visibleSize.width / logo->getContentSize().width);
	logo->setScaleY(visibleSize.height / logo->getContentSize().height);
	logo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(logo);

	auto fadein1 = FadeIn::create(1);
	auto fadein2 = FadeIn::create(0.2);
	auto fadeout = FadeOut::create(0.2);
	auto sequencefade = Sequence::create(fadeout, fadein2, fadeout->clone(), fadein1, nullptr);

	logo->runAction(sequencefade);

	auto music_bg = SimpleAudioEngine::getInstance();
	music_bg->playBackgroundMusic("logomusic.mp3", false);

	auto gotoNext = CallFunc::create([]() {
		Director::getInstance()->replaceScene(TransitionFade::create(1.5, LoadingScene::create(), Color3B(0, 888, 888)));
	});
	auto sq_replaceScene = Sequence::create(DelayTime::create(3.5), gotoNext, nullptr);
	runAction(sq_replaceScene);

	return true;
}
