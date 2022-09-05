#include "LaunchScreen.h"
#include "audio/include/AudioEngine.h"
#include "FrameNav.h"
#include "MainMenu.h"

Scene* Launch::createScene() {
	return Launch::create();
}

bool Launch::init() {

	// Ensure layer from createScene() was created
	if (!Scene::init()) {
		return false;
	}

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    log("----------");
    FrameNav fn;
    fn.bkgdMusic(0);
    

    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;
    
    auto bkgd = MenuItemImage::create(
                                      LAUNCHIMAGE,
                                      LAUNCHIMAGE,
                                      CC_CALLBACK_1(Launch::gotoNextScene, this)
                                      );
    
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
    auto menu = Menu::create(bkgd, NULL);
    menu->setPosition(center);
    this->addChild(menu, -1);

	// Helicopter Sprite
	auto heli = Sprite::create(HELICOPTER);
	
	heli->setPosition(Vec2(-heli->getContentSize().width + origin.x,
                           0.9*h + origin.y));
	heli->setScale(0.15*w / heli->getContentSize().width,
                   0.15*w / heli->getContentSize().width);
	this->addChild(heli, 1);

    auto moveHeli = MoveBy::create(6, Vec2(1.5*w, 0));
    auto up = MoveBy::create(1, Vec2(0, 0.02*h));
    auto down = MoveBy::create(1, Vec2(0, -0.02*h));
    heli->runAction(Spawn::create(Sequence::create(up,down,up,down,up,down,
                                                   nullptr),
                                  moveHeli,
                                  nullptr)
                    );
    
    //Scooter
	auto scooter = Sprite::create(SCOOTER);
	scooter->setPosition(Vec2(origin.x + w + scooter->getContentSize().width,
                              0.24*h + origin.y));
	scooter->setScale(0.2*w / scooter->getContentSize().width,
                      0.2*w / scooter->getContentSize().width);
	this->addChild(scooter, 1);
    
    auto moveScooter = MoveBy::create(2.5, Vec2(-0.7*w, -0.06*h));
    scooter->runAction(Sequence::create(DelayTime::create(1.5),
                                        moveScooter,
                                        nullptr)
                       );
    
    //this->scheduleOnce(CC_SCHEDULE_SELECTOR(Launch::zoomSound), 1.5);

    
	auto welcomeButton = Sprite::create(WELCOMEBUTTON);
    welcomeButton->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                                    0.8*visibleSize.height + origin.y)
                               );
	welcomeButton->setScale(0.5*w / welcomeButton->getContentSize().width,
                            0.4*w / welcomeButton->getContentSize().width);
	this->addChild(welcomeButton, 1);
    
	auto welcomeText = Sprite::create(WELCOMETEXT);
    welcomeText->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                                  0.8*visibleSize.height + origin.y)
                             );
    welcomeText->setScale(0.45*w / welcomeText->getContentSize().width,
                            0.38*w / welcomeText->getContentSize().width);
	this->addChild(welcomeText, 2);
	

	auto startButton = Sprite::create(STARTBUTTON);
    startButton->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                                  0.67*visibleSize.height + origin.y));
	startButton->setScale(0.15*w / startButton->getContentSize().width,
                          0.13*w / startButton->getContentSize().width);
    this->addChild(startButton, 1);
    
	auto startText = Sprite::create(STARTTEXT);
    startText->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                                0.67*visibleSize.height + origin.y)
                           );
    startText->setScale(0.12*w / startText->getContentSize().width,
                          0.1*w / startText->getContentSize().width);
	this->addChild(startText, 1);
    
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(Launch::gotoCredits), 9);
    return true;
}

// Callback function to move on to the next scene
void Launch::gotoNextScene(Ref* pSender) {
	auto nextScene = MainMenu::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME,nextScene));
}

void Launch::zoomSound(float dt) {
    AudioEngine::preload("audio/dh.wav");
    AudioEngine::play2d("audio/dh.wav", 0 , 1.0f);
    
}

void Launch::gotoCredits(float dt) {
    auto nextScene = MainMenu::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME, nextScene));
    
}
