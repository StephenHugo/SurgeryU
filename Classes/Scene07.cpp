#include "Scene07.h"
#include "Scene08.h"
#include "Scene06.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

Scene* Scene07::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene07 class that inherits from Layer class
	auto layer = Scene07::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene07::init() {

	// Ensure layer from createScene() was created
	if (!Layer::init()) {
		return false;
	}

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;
	
    UserDefault* def = UserDefault::getInstance();
    def->setBoolForKey("GOWNCLICKED", false);
    def->flush();
    
	auto bkgd = Sprite::create(SCALEBKGD);
	bkgd->setAnchorPoint(Vec2(0, 0));
	bkgd->setPosition(Vec2(origin.x, origin.y));
	bkgd->setScale(visibleSize.width / bkgd->getContentSize().width, visibleSize.height / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);

	// Create Scene Sprites----------------------------------------------------------------------------------------------------------

    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                              0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                      0.2*visibleSize.height / textBox->getContentSize().height);
    this->addChild(textBox, FRAMEDRAW + 1);

	this->gator = Sprite::create(Gator);
	
	gator->setPosition(Vec2(origin.x + visibleSize.width * 0.27,
                            origin.y + visibleSize.height * 0.39));
	gator->setScale(0.85 * visibleSize.width / bkgd->getContentSize().width,
                    0.85 * visibleSize.height / bkgd->getContentSize().height);
	this->addChild(gator);
    
    auto gown = Sprite::create(Gown);
    
    gown->setPosition(Vec2(origin.x + visibleSize.width * 0.87,
                           origin.y + visibleSize.height * 0.4));
    gown->setScale(0.8 * visibleSize.width / bkgd->getContentSize().width,
                   0.8 * visibleSize.height / bkgd->getContentSize().height);
    this->addChild(gown);
    
    auto gownlistener = EventListenerTouchOneByOne::create();
    gownlistener->setSwallowTouches(true);
    gownlistener->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        auto gownBox = gown->getBoundingBox();
        //auto elevatorBox = event->getCurrentTarget()->getBoundingBox();
        if (gownBox.containsPoint(touch->getLocation())) {
            
            auto iSpy = def->getBoolForKey("ISPYSMOCKFOUND", false);
            def->setBoolForKey("GOWNCLICKED", true);
            def->flush();
            
            if (!iSpy) {
                this->scheduleOnce(schedule_selector(Scene07::textAppears), 0.2);
                def->setBoolForKey("ISPYSMOCKFOUND", true);
                def->flush();
                Scene07::ispyCallBack();
                return false;
            } else {
                gown->runAction(ScaleBy::create(0.2, 1.1, 1.1));
                return true;
            }
        }
        return false;
    };
    
    gownlistener->onTouchMoved = [=](Touch *touch, Event *event) -> bool {
        
        auto pos = touch->getLocation();
        gown->setPosition(pos);
        return true;
    };
    
    gownlistener->onTouchEnded = [=](Touch *touch, Event *event) -> void {
        
        auto gatorBox = this->gator->getBoundingBox();
        
        if (gatorBox.containsPoint(touch->getLocation())) {
            
            gown->runAction(Sequence::create(FadeOut::create(0.2), RemoveSelf::create(), nullptr));
            _eventDispatcher->removeEventListener(gownlistener);
            gator->setTexture(DressedGator);
            gator->setScale(0.87 * visibleSize.width / bkgd->getContentSize().width, 0.88 * visibleSize.height / bkgd->getContentSize().height);
            gator->runAction(EaseBounceOut::create(MoveBy::create(0.8, Vec2(0, 0.03*visibleSize.height))));
            
            this->scheduleOnce(schedule_selector(Scene07::createGatorListener), 0.5);
        } else {
            
            gown->runAction(Spawn::create(ScaleTo::create(1.0, 0.8 * visibleSize.width / bkgd->getContentSize().width, 0.8 * visibleSize.height / bkgd->getContentSize().height),
                                          RotateBy::create(1.0, -360),
                                          MoveTo::create(1.0, Vec2(origin.x + visibleSize.width * 0.87, origin.y + visibleSize.height * 0.4)),
                                          nullptr));
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(gownlistener, this);

	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
    FrameNav temp;
    temp.addFrameNav(this);
    this->frameNav = &temp;
    this->frameNav->bkgdMusic(2);
    
    // Scripts
    
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene07");

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene07::gotoNextScene, this)
	);
    nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene07::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

    this->scheduleOnce(schedule_selector(Scene07::textAppears), 2);
    
	return true;
}

void Scene07::createGatorListener(float dt) {
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto gatorlistener = EventListenerTouchOneByOne::create();
    gatorlistener->setSwallowTouches(true);
    
    gatorlistener->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        
        auto gatorBox = this->gator->getBoundingBox();
        
        if (gatorBox.containsPoint(touch->getLocation())) {
            
            return true;
        }
        return false;
    };
    
    gatorlistener->onTouchEnded = [=](Touch *touch, Event *event) -> void {
        
        auto jumpUp = EaseIn::create(MoveTo::create(0.7, Vec2(0.40*visibleSize.width + origin.x, 0.65*visibleSize.height + origin.y)), 0.7);
        auto land = EaseOut::create(MoveTo::create(0.7, Vec2(0.46*visibleSize.width + origin.x, 0.5*visibleSize.height + origin.y)), 0.7);
        this->gator->runAction(Spawn::create(RotateBy::create(1.4, 360),
                                             Sequence::create(jumpUp, land, nullptr),
                                             nullptr));
        
        auto textString3 = Json_getString(script, "7.3", "Go Gators!");
        auto label3 = this->frameNav->createText(textString3, this);
        auto appear = FadeIn::create(0.2);
        label3->runAction(appear);
        
        
        this->scheduleOnce(schedule_selector(Scene07::waitNextScene), 4.0);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(gatorlistener, this);
}

void Scene07::waitNextScene(float dt) {
    auto nextScene = Scene08::createScene();
    Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the next scene
void Scene07::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene08::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void Scene07::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene06::createScene();
	Director::getInstance()->pushScene(nextScene);
}

void Scene07::ispyCallBack(){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto star = Sprite::create(STARSHINE);
    star->setPosition(Vec2(origin.x + (0.87 * visibleSize.width),
                           origin.y + (0.4 * visibleSize.height)));
    star->setScale(0.1 * (visibleSize.width / star->getContentSize().width),
                   0.1 * (visibleSize.width / star->getContentSize().width));
    this->addChild(star, FRAMEDRAW + 2);
    
    star->runAction(Sequence::create(Spawn::create(FadeIn::create(0.6),
                                                   RotateBy::create(0.8, 360),
                                                   MoveBy::create(0.8, Vec2(0.05*visibleSize.height,
                                                                            0.05*visibleSize.height)),
                                                   nullptr),
                                     Spawn::create(RotateBy::create(0.6, 360),
                                                   EaseBounceOut::create(MoveBy::create(0.6, Vec2(0.05*visibleSize.width, -0.05*visibleSize.height))), nullptr),
                                     EaseElasticIn::create(MoveBy::create(1.4, Vec2(-0.05*visibleSize.height,0.2*visibleSize.height))),
                                     RemoveSelf::create(),
                                     nullptr));
    
};

void Scene07::textAppears(float dt)
{
    
    UserDefault * def = UserDefault::getInstance();
    auto gownFound = def->getBoolForKey("GOWNCLICKED", false);
    
    FrameNav fn;
    auto appear = FadeIn::create(0.2);
    auto disappear = FadeOut::create(0.2);
    auto delay = DelayTime::create(6);
    
    if (!gownFound) {
    
        auto textString1 = Json_getString(script, "7.1", "Go Gators!");
        auto label1 = fn.createText(textString1, this);
        label1->runAction(Sequence::create(appear, delay, disappear, nullptr));
        
    } else {
    
        auto textString2 = Json_getString(script, "7.2", "Go Gators!");
        auto label2 = fn.createText(textString2, this);
        label2->runAction(Sequence::create(appear, delay, disappear, nullptr));
        def->setBoolForKey("GOWNCLICKED", false);
        def->flush();
        
    }
}
