#include "MainMenu.h"
//#include "Scene02.h"
#include "LaunchScreen.h"
#include "audio/include/AudioEngine.h"
//#include "Scene15.h"
#include "FrameNav.h"
#include "Credits0.h"

Scene* MainMenu::createScene() {
	return MainMenu::create();
}

bool MainMenu::init() {

	// Ensure layer from createScene() was created
	if (!Scene::init()) {
		return false;
	}
    
    // only for debug purposes
    UserDefault * def = UserDefault::getInstance();
    
    def->setBoolForKey("ISPYBPFOUND", false);
    def->setBoolForKey("ISPYNAMEFOUND", false);
    def->setBoolForKey("ISPYMASKFOUND", false);
    def->setBoolForKey("ISPYPULSEOXFOUND", false);
    def->setBoolForKey("ISPYELECFOUND", false);
    def->setBoolForKey("ISPYSMOCKFOUND", false);
    def->setBoolForKey("ISPYTHERMOFOUND", false);
    
    def->flush();
    //
    
	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;

	auto bkgd = Sprite::create(MENUBKGD);
	
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
				   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);

	auto welcomeButton = Sprite::create(WELCOMEBUTTON01);
	welcomeButton->setPosition(Vec2(0.65*w + origin.x,
									0.5*h + origin.y)
                               );
	welcomeButton->setScale(0.5 * w / welcomeButton->getContentSize().width,
							0.5 * w / welcomeButton->getContentSize().width);
	this->addChild(welcomeButton, 1);

	auto exitButton = MenuItemImage::create(
		EXITBUTTONON,
		EXITBUTTONOFF,
		CC_CALLBACK_1(MainMenu::exitCallBack, this)
	);
	exitButton->setPosition(Vec2(w * SCALEX1 + origin.x,
								 h * SCALEY2 + origin.y));
	exitButton->setScale(0.07 * w / exitButton->getContentSize().width,
						 0.07 * h / exitButton->getContentSize().width);

    auto care = MenuItemImage::create(
		CAREGIVERBUTTON01,
		CAREGIVERBUTTON01,
		CC_CALLBACK_1(MainMenu::careButtonCallBack, this)
	);
    care->setPosition(Vec2(origin.x + visibleSize.width * 0.535,
						   origin.y + visibleSize.height * 0.445));
    care->setScale(0.22 * w / care->getContentSize().width,
				   0.22 * w / care->getContentSize().width);

	auto game = MenuItemImage::create(
		GAMEBUTTON01,
		GAMEBUTTON01,
		CC_CALLBACK_1(MainMenu::gameButtonCallBack, this)
	);
	game->setPosition(Vec2(origin.x + visibleSize.width * 0.76,
						   origin.y + visibleSize.height * 0.445));
    game->setScale(0.22 * w / game->getContentSize().width,
                   0.22 * w / game->getContentSize().width);

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(MainMenu::gotoNextScene, this)
	);
	nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
								visibleSize.height* SCALEY1 + origin.y));
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
						0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(MainMenu::gotoPreviousScene, this)
	);
	prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
								visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
						0.1*h / prevScene->getContentSize().height);
    
    auto label = Label::createWithTTF("Credits", FELTFONT, visibleSize.height * TEXTSIZE);
    label->setColor(cocos2d::Color3B::BLACK);
    auto credits = MenuItemLabel::create(label, CC_CALLBACK_1(MainMenu::gotoCredits, this));
    credits->setPosition(Vec2(SCALEX2*w + origin.x,
                              SCALEY2*h + origin.y));

	// Create the menu
	this->menu = Menu::create(exitButton, nextScene, prevScene, care, game, credits, NULL);
	this->menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(this->menu, (FRAMEDRAW + 1)); // Please note that the one must be there

    FrameNav fn;
    fn.bkgdMusic(0);
    
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(MainMenu::gotoLaunch), 15);
	return true;
}

void MainMenu::careButtonCallBack(Ref* pSender) {

	// Disable menu
	menu->setEnabled(false);

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto clipboard = Sprite::create(CLIPBOARD);
	clipboard->setPosition(Vec2(origin.x + (visibleSize.width) * 0.5,
								origin.y + (visibleSize.height) * 0.5));
	clipboard->setScale((visibleSize.height / clipboard->getContentSize().height) * 0.95,
						 visibleSize.height / clipboard->getContentSize().height * 0.95);
	clipboard->setOpacityModifyRGB(0);
    
    auto clip = Sprite::create(CLIPGOTIT);
	clip->setPosition(Vec2(clipboard->getContentSize().width * 0.5,
		clipboard->getContentSize().height * 0.07));
    clip->setScale((visibleSize.width / clip->getContentSize().width) * 0.2,
                   (visibleSize.width / clip->getContentSize().width) * 0.2);
    
    clipboard->addChild(clip);
    this->addChild(clipboard, (FRAMEDRAW + 2));
    
	clipboard->runAction(FadeIn::create(0.2));

	auto listen = EventListenerTouchOneByOne::create();

	listen->onTouchBegan = [=](Touch *touch, Event *event)-> bool {
		auto gtBox = event->getCurrentTarget()->getBoundingBox();
		if (clipboard->getNumberOfRunningActions() == 0.0) {
			this->_actionComplete = true;
		}

		if (gtBox.containsPoint(touch->getLocation()) && this->_actionComplete) {
			return true;
		}
		return false;
	};

	listen->onTouchEnded = [=](Touch *touch, Event *event)-> void {
		this->_actionComplete = false;
        clipboard->runAction(RemoveSelf::create());
		menu->setEnabled(true);
	};
	// Add listener
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, clipboard);

};

void MainMenu::gameButtonCallBack(Ref* pSender) {

	// Disable menu
	menu->setEnabled(false);

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto gameIcon = Sprite::create(ICONGAME);
	gameIcon->setPosition(Vec2(origin.x + (visibleSize.width) * 0.5,
							   origin.y + (visibleSize.height) * 0.5));
	gameIcon->setScale((visibleSize.height / gameIcon->getContentSize().height) * 0.7,
					   (visibleSize.height / gameIcon->getContentSize().height) * 0.7);
	gameIcon->setOpacityModifyRGB(0);
    
    auto gameButton = Sprite::create(GAMEGOTIT);
	gameButton->setPosition(Vec2(gameIcon->getContentSize().width * 0.475,
								 gameIcon->getContentSize().height * 0.2));
    gameButton->setScale((visibleSize.width / gameButton->getContentSize().width) * 0.3,
                       (visibleSize.width / gameButton->getContentSize().width) * 0.3);
	
    gameIcon->addChild(gameButton);
	this->addChild(gameIcon, (FRAMEDRAW + 2));
    
    gameIcon->runAction(FadeIn::create(0.2));
    
    auto listen = EventListenerTouchOneByOne::create();
    
    //listen->setSwallowTouches(true);
    listen->onTouchBegan = [gameIcon, this](Touch * touch, Event * event)-> bool {
        auto gtBox = event->getCurrentTarget()->getBoundingBox();
        if (gameIcon->getNumberOfRunningActions() == 0.0) {
            this->_actionComplete = true;
        }
        
        if (gtBox.containsPoint(touch->getLocation()) && this->_actionComplete) {
            return true;
        }
        return false;
    };
    
    listen->onTouchEnded = [gameButton, gameIcon, this](Touch * touch, Event * event)-> void {
        this->_actionComplete = false;
        gameIcon->runAction(RemoveSelf::create());
        menu->setEnabled(true);
    };
    // Add listener
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, gameIcon);
};

// Callback function to exit the application
void MainMenu::exitCallBack(Ref* pSender) {
    
    AudioEngine::stopAll();
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    exit(0);
#endif
    
}

// Callback function to move on to the next scene
void MainMenu::gotoNextScene(Ref* pSender) {
    
    //auto nextScene = Scene02::createScene();
    //Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void MainMenu::gotoPreviousScene(Ref* pSender) {
    //auto nextScene = Scene15::createScene();
    //Director::getInstance()->pushScene(nextScene);
}

void MainMenu::gotoLaunch(float dt) {
    auto nextScene = Launch::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME, nextScene));
    
}

void MainMenu::gotoCredits(Ref* pSender) {
    auto nextScene = Credits::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME, nextScene));
}
