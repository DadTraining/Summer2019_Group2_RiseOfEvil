#include "LogoScene.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
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

	//create background logo
	auto logo_bg = ResourceManager::GetInstance()->GetSpriteById(0);
	logo_bg->setAnchorPoint(Vec2(0.5, 0.5));
	logo_bg->setScaleX(visibleSize.width / logo_bg->getContentSize().width);
	logo_bg->setScaleY(visibleSize.height / logo_bg->getContentSize().height);
	logo_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	logo_bg->removeFromParent();
	addChild(logo_bg);

	//create effect
	auto fadein1 = FadeIn::create(1);
	auto fadein2 = FadeIn::create(0.2);
	auto fadeout = FadeOut::create(0.2);
	auto sequencefade = Sequence::create(fadeout, fadein2, fadeout->clone(), fadein1, nullptr);

	logo_bg->runAction(sequencefade);

	//create music background
	auto music_bg = SimpleAudioEngine::getInstance();
	music_bg->playBackgroundMusic("res/Musics/logomusic.mp3", false);

	//replace LoadingScene
	auto gotoNext = CallFunc::create([]() {
		Director::getInstance()->replaceScene(TransitionFade::create(1.5, LoadingScene::create(), Color3B(0, 0, 0)));
	});
	auto sq_replaceScene = Sequence::create(DelayTime::create(4), gotoNext, nullptr);
	runAction(sq_replaceScene);

	return true;
}
