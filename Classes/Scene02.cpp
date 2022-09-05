#include "Scene02.h"
#include "Scene04.h"
#include "MainMenu.h"
#include "DrawScene.h"
#include "editor-support/spine/Json.h"
#include "FrameNav.h"

Scene* Scene02::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene02 class that inherits from Layer class
	auto layer = Scene02::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene02::init() {

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
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
	script = Json_getItem(chapterScript, "Scene02");

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(Scene02::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Scene02::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Scene02::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Scene02::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;

	auto bkgd = Sprite::create(NAMETAGBKGD);
	bkgd->setAnchorPoint(Vec2(0, 0));
	bkgd->setPosition(Vec2(origin.x, origin.y));
	bkgd->setScale(visibleSize.width / bkgd->getContentSize().width, 
				   visibleSize.height / bkgd->getContentSize().height);
	this->addChild(bkgd);

    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                           0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                   0.2*visibleSize.height / textBox->getContentSize().height);
    this->addChild(textBox, FRAMEDRAW + 1);

	// Create object that should be touched for ISPY game
	auto brace = MenuItemImage::create(
                                BRACELET,
								BRACELET,
                                CC_CALLBACK_1(Scene02::braceletButtonCallBack, this));
	brace->setAnchorPoint(Vec2(0,0));
	brace->setPosition(Vec2(origin.x + (0.39 * visibleSize.width),
							origin.y + (0.32 * visibleSize.height)));
	brace->setScale(0.1 * (visibleSize.width / brace->getContentSize().width),
				    0.1 * (visibleSize.height / brace->getContentSize().height));

	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
	FrameNav temp;
	temp.addFrameNav(this);
	this->frameNav = &temp;
    this->frameNav->bkgdMusic(1);

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene02::gotoNextScene, this)
	);
    nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene02::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	menu = Menu::create(nextScene, prevScene, brace, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

	return true;
}

void Scene02::braceletButtonCallBack(Ref* pSender){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Create star for found icon once touched
    UserDefault * def = UserDefault::getInstance();
    
    auto iSpyName = def->getBoolForKey("ISPYNAMEFOUND", false);
    
    if (!iSpyName) {
        def->setBoolForKey("ISPYNAMEFOUND", true);
        def->flush();
        
        //// get text from json script object
        auto textString3 = Json_getString(script, "2.3", "Go Gators!");
        
        //// set up text
        FrameNav fn;
        auto label3 = fn.createText(textString3, this);
        label3->setColor(cocos2d::Color3B::GREEN);
        
        auto appear = FadeIn::create(0.1);
        auto disappear = FadeOut::create(0.1);
        auto delay = DelayTime::create(6);
        
        label3->runAction(Sequence::create(appear, delay, disappear, nullptr));
        
		// This star shows up for effect once desired icon is clicked
        auto star = Sprite::create(STARSHINE);
        star->setPosition(Vec2(origin.x + (0.43 * visibleSize.width),
                               origin.y + (0.36 * visibleSize.height)));
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
        
        this->scheduleOnce(schedule_selector(Scene02::toggleIcon), 3);
        this->scheduleOnce(schedule_selector(Scene02::waitDrawCallBack), 5);
    } else {
    
    auto clipboard = MenuItemImage::create(
                                       BRACELETCLICKED,
                                       BRACELETCLICKED,
                                       CC_CALLBACK_1(Scene02::gotoDrawCallBack, this));
    clipboard->setScale(0.2*visibleSize.width / clipboard->getContentSize().width,
                        0.2*visibleSize.width / clipboard->getContentSize().width);
    clipboard->setPosition(Vec2(0.62*visibleSize.width,
								0.42*visibleSize.height));
    
    auto braceletMenu = Menu::create(clipboard, NULL);
    braceletMenu->setOpacityModifyRGB(0);
    braceletMenu->setPosition(origin.x, origin.y);
    
    this->addChild(braceletMenu, 25); // Please note that the one must be there
    
    braceletMenu->runAction(Spawn::create(FadeIn::create(0.2), 
							ScaleBy::create(0.2, 1.1), 
							EaseBounceOut::create(MoveBy::create(0.6,Vec2(0,-0.05*visibleSize.height))), nullptr));
    }
};

// Shift to draw scene automatically once icon is found
void Scene02::waitDrawCallBack(float dt) {

	auto nextScene = DrawScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.8, nextScene));

}

bool Scene02::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* click)
{
	//// get text from json script object
	auto textString1 = Json_getString(script, "2.1", "Go Gators!");
	auto textString2 = Json_getString(script, "2.2", "Go Gators!");

	//// set up text
	FrameNav fn;
	auto label1 = fn.createText(textString1, this);
	auto label2 = fn.createText(textString2, this);

	auto appear = FadeIn::create(0.1);
	auto disappear = FadeOut::create(0.1);
	auto delay = DelayTime::create(6);

	label1->runAction(Sequence::create(appear, delay, disappear, nullptr));
	label2->runAction(Sequence::create(delay, appear, delay, disappear, nullptr));
	
	return true;
}

void Scene02::onTouchEnded(cocos2d::Touch*, cocos2d::Event*)
{
}
void Scene02::onTouchMoved(cocos2d::Touch*, cocos2d::Event*)
{
}
void Scene02::onTouchCancelled(cocos2d::Touch*, cocos2d::Event*)
{
}
;

void Scene02::gotoDrawCallBack(Ref* pSender) {

	auto nextScene = DrawScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.8, nextScene));

};

void Scene02::toggleIcon(float dt) {
    // If used to create an icon bar
    this->frameNav->createIconBar(this);
    
}

// Callback function to move on to the next scene
void Scene02::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene04::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void Scene02::gotoPreviousScene(Ref* pSender) {
	auto nextScene = MainMenu::createScene();
	Director::getInstance()->pushScene(nextScene);
}
