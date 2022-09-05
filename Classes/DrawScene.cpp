#include "Scene02.h"
#include "DrawScene.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

Scene* DrawScene::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	// Create an instance of our DrawScene class that inherits from layer class
	auto layer = DrawScene::create();

	// Add layer to our scene
	scene->addChild(layer);

	// Scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool DrawScene::init() {

	// Ensure layer from createScene() was created
	if (!Layer::init()) {
		return false;
	}

	// Scripts
	UserDefault* def = UserDefault::getInstance();
	def->setIntegerForKey("CURRENTCHAPTER", 2);
	auto language = def->getStringForKey("LANGUAGE", "English");
	def->flush();

	auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
	auto fullScript = Json_create(scriptString->getCString());
	auto chapterScript = Json_getItem(fullScript, "English"); // fixed - had funky " marks
	script = Json_getItem(chapterScript, "Scene02");

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;

	auto bkgd = Sprite::create(DRAWBACKGROUND);
	bkgd->setAnchorPoint(Vec2(0, 0));
	bkgd->setPosition(Vec2(origin.x, origin.y));
	bkgd->setScale(visibleSize.width / bkgd->getContentSize().width,
				   visibleSize.height / bkgd->getContentSize().height);
	this->addChild(bkgd);

    // Adds home button and volume control to the scene
    FrameNav frameNav;
    frameNav.addFrameNav(this); // Addling layer to scene
    frameNav.bkgdMusic(1);
    
    auto textBox = Sprite::create(TEXTBOX);
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                              0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                      0.2*visibleSize.height / textBox->getContentSize().height);
    this->addChild(textBox, FRAMEDRAW + 1);

	//// get text from json script object
	auto textString = Json_getString(script, "2.4", "Go Gators!");

	//// set up text
    auto label = frameNav.createText(textString, this);
    label->setScale(1.8);
    label->setAlignment(TextHAlignment::CENTER);
    label->runAction(FadeIn::create(0.4));
                                      
	// ************** Menu Items for Scene **************

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		DONEBUTTON,
		DONEBUTTON,
		CC_CALLBACK_1(DrawScene::gotoNextScene, this)
	);
	nextScene->setPosition(Vec2(visibleSize.width * 0.91 + origin.x,
								visibleSize.height * 0.08 + origin.y));
    nextScene->setScale(0.15*w / nextScene->getContentSize().width,
                        0.15*w / nextScene->getContentSize().width);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		BACKBUTTON,
		BACKBUTTON,
		CC_CALLBACK_1(DrawScene::gotoPreviousScene, this)
	);
	prevScene->setPosition(Vec2(visibleSize.width * 0.09 + origin.x,
								visibleSize.height * 0.08 + origin.y));
    prevScene->setScale(0.15*w / prevScene->getContentSize().width,
                        0.15*w / prevScene->getContentSize().width);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there
    

	// ************** Draw Stuff for Scene **************

	float dotScaleX = 0.14;

	auto orangeDot = Sprite::create(ORANGEDOT);
	orangeDot->setPosition(
		Vec2(
			origin.x + visibleSize.width * dotScaleX,
			origin.y + visibleSize.height * 0.385)
	);
	orangeDot->setScale(w * 1.05 / bkgd->getContentSize().width, w * 1.05 / bkgd->getContentSize().width);
	auto listenOrange = EventListenerTouchOneByOne::create();
	listenOrange->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		auto orangeBox = event->getCurrentTarget()->getBoundingBox();
		if (orangeBox.containsPoint(touch->getLocation())) {
			setInkColor(1); return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenOrange, orangeDot);
	this->addChild(orangeDot, (FRAMEDRAW + 2));
	
	auto yellowDot = Sprite::create(YELLOWDOT);
	yellowDot->setPosition(
		Vec2(
			origin.x + visibleSize.width * dotScaleX,
			origin.y + visibleSize.height * 0.47)
	);
	yellowDot->setScale(w * 1.05 / bkgd->getContentSize().width, w * 1.05 / bkgd->getContentSize().width);
	auto listenYellow = EventListenerTouchOneByOne::create();
	listenYellow->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		auto yellowBox = event->getCurrentTarget()->getBoundingBox();
		if (yellowBox.containsPoint(touch->getLocation())) {
			setInkColor(2); return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenYellow, yellowDot);
	this->addChild(yellowDot, (FRAMEDRAW + 2));
	
	auto blueDot = Sprite::create(BLUEDOT);
	blueDot->setPosition(
		Vec2(
			origin.x + visibleSize.width * dotScaleX,
			origin.y + visibleSize.height * 0.56)
	);
	blueDot->setScale(w * 1.0 / bkgd->getContentSize().width, w * 1.0 / bkgd->getContentSize().width);
	auto listenBlue = EventListenerTouchOneByOne::create();
	listenBlue->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		auto blueBox = event->getCurrentTarget()->getBoundingBox();
		if (blueBox.containsPoint(touch->getLocation())) {
			setInkColor(3); return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenBlue, blueDot);
	this->addChild(blueDot, (FRAMEDRAW + 2));

	auto redDot = Sprite::create(REDDOT);
	redDot->setPosition(
		Vec2(
			origin.x + visibleSize.width * dotScaleX,
			origin.y + visibleSize.height * 0.65)
	);
	redDot->setScale(w * 1.0 / bkgd->getContentSize().width, w * 1.0 / bkgd->getContentSize().width);
	auto listenRed = EventListenerTouchOneByOne::create();
	listenRed->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		auto redBox = event->getCurrentTarget()->getBoundingBox();
		if (redBox.containsPoint(touch->getLocation())) {
			setInkColor(4); return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenRed, redDot);
	this->addChild(redDot, (FRAMEDRAW + 2));

	auto greenDot = Sprite::create(GREENDOT);
	greenDot->setPosition(
		Vec2(
			origin.x + visibleSize.width * dotScaleX,
			origin.y + visibleSize.height * 0.75)
	);
	greenDot->setScale(w * 1.05 / bkgd->getContentSize().width, w * 1.05 / bkgd->getContentSize().width);
	auto listenGreen = EventListenerTouchOneByOne::create();
	listenGreen->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		auto greenBox = event->getCurrentTarget()->getBoundingBox();
		if (greenBox.containsPoint(touch->getLocation())) {
			setInkColor(5); return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenGreen, greenDot);
	this->addChild(greenDot, (FRAMEDRAW + 2));
	
	// Create pen that will be used to draw name 
	// (not actual pen just acts like one)
    auto pen = DrawNode::create();
    this->addChild(pen);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    //listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto pos = touch->getLocation();
        
        auto x = pos.x/visibleSize.width;
        //auto y = pos.y/visibleSize.height;
        
        //// Should probably disallow drawing outside of the nametag...

		// Update color
		if (prevColor != curColor) {
			pen->updateDisplayedColor(Color3B(curColor));
		};

		pen->drawSolidCircle(
			Vec2(pos.x, pos.y),
			DRAWSCENEBRUSHSIZE * visibleSize.width,
			360,
			12,
			curColor);
       
        return true;
    };
    
    listener->onTouchMoved = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        auto pos = touch->getLocation();
        //pen->drawSolidRect(Vec2(pos.x, pos.y), Vec2(pos.x+10, pos.y+10), inkColor);
		/*
		*/
        pen->drawSolidCircle(
			Vec2(pos.x, pos.y),
			DRAWSCENEBRUSHSIZE*visibleSize.width,
			360,
			12,
			curColor);
        
        return true;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event){return true;};
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
	return true;
}

// Callback function to move on to the next scene
void DrawScene::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene02::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void DrawScene::gotoPreviousScene(Ref* pSender) {
	auto nextScene = DrawScene::createScene();
	Director::getInstance()->pushScene(nextScene);
}

void DrawScene::setInkColor(int colorVal) {
	switch (colorVal) {
	// orange
	case 1: { this->prevColor = this->curColor; this->curColor = Color4F::ORANGE; break; }
	// yellow
	case 2: { this->prevColor = this->curColor; this->curColor = Color4F::YELLOW; break; }
	// blue
	case 3: { this->prevColor = this->curColor; this->curColor = Color4F::BLUE; break; }
	// red
	case 4: { this->prevColor = this->curColor; this->curColor = Color4F::RED; break; }
	// green
	case 5: { this->prevColor = this->curColor; this->curColor = Color4F::GREEN; break; }
	}
};
