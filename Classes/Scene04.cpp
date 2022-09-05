#include "Scene04.h"
#include "Scene06.h"
#include "Scene02.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"
#include "PuzzleScene.h"

Scene* Scene04::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene04 class that inherits from Layer class
	auto layer = Scene04::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene04::init() {

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

	auto bkgd = Sprite::create(WAITINGBKGD);
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

    // Scripts
    UserDefault* def = UserDefault::getInstance();
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene04");
    
	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
	FrameNav frameNav;
	frameNav.addFrameNav(this);
    frameNav.bkgdMusic(1);

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene04::gotoNextScene, this)
	);
    nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene04::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there
    
    this->scheduleOnce(schedule_selector(Scene04::textAppears), 2);

	return true;
}

void Scene04::gameButtonCallBack(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto clipboard = MenuItemImage::create(
                                           GAMEBUTTON04,
                                           GAMEBUTTON04,
                                           CC_CALLBACK_1(Scene04::gotoGameCallback, this));
    clipboard->setScale(0.2*visibleSize.width / clipboard->getContentSize().width,
                        0.2*visibleSize.width / clipboard->getContentSize().width);
    clipboard->setPosition(Vec2(0.5*visibleSize.width,
                                0.5*visibleSize.height));
    
    auto braceletMenu = Menu::create(clipboard, NULL);
    braceletMenu->setOpacityModifyRGB(0);
    braceletMenu->setPosition(origin.x, origin.y);
    
    this->addChild(braceletMenu, 2); // Please note that the one must be there
    
    braceletMenu->runAction(Spawn::create(FadeIn::create(0.2),
                                          ScaleBy::create(0.2, 1.1),
                                          EaseBounceOut::create(MoveBy::create(0.6,Vec2(0,-0.05*visibleSize.height))), nullptr));
    
};

void Scene04::textAppears(float dt)
{
    
    UserDefault * def = UserDefault::getInstance();
    auto puzzled = def->getBoolForKey("PUZZLED", false);
    
    if (!puzzled) {
        
        //// get text from json script object
        
        auto textString1 = Json_getString(script, "4.1", "Go Gators!");
        auto textString2 = Json_getString(script, "4.2", "Go Gators!");
        
        //// set up text
        
        // Added a framenav function so all text displays the same
        
        FrameNav fn;
        auto label1 = fn.createText(textString1, this);
        auto label2 = fn.createText(textString2, this);
        
        auto appear = FadeIn::create(0.2);
        auto disappear = FadeOut::create(0.2);
        auto delay = DelayTime::create(6);
        
        label1->runAction(Sequence::create(appear, delay, disappear, nullptr));
        label2->runAction(Sequence::create(delay, appear, nullptr));
        this->scheduleOnce(schedule_selector(Scene04::gameButtonCallBack), 3);
        
    } else {
        def->setBoolForKey("PUZZLED", false);
        def->flush();
        
        auto textString3 = Json_getString(script, "4.4", "Go Gators!");
        
        //// set up text
        
        // Added a framenav function so all text displays the same
        
        FrameNav fn;
        auto label3 = fn.createText(textString3, this);
        
        auto appear = FadeIn::create(0.1);
        
        label3->runAction(appear);
        this->scheduleOnce(schedule_selector(Scene04::waitNextScene), 2.5);
        
    }
}

// Callback function to move on to the next scene
void Scene04::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene06::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void Scene04::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene02::createScene();
	Director::getInstance()->pushScene(nextScene);
}

// Callback function to move to the puzzle game scene
void Scene04::gotoGameCallback(Ref* pSender) {
	auto nextScene = PuzzleScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.8, nextScene));
};

void Scene04::waitNextScene(float dt) {
    auto nextScene = Scene06::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, nextScene));
}
