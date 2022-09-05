#include "Scene11.h"
#include "Scene12.h"
#include "Scene10.h"
#include "Scene08.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

Scene* Scene11::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene11 class that inherits from Layer class
	auto layer = Scene11::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene11::init() {

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
    
    auto bkgd = Sprite::create(ORDOORSBKGD);
    
    bkgd->setPosition(center);
    bkgd->setScale(1.1*visibleSize.width / bkgd->getContentSize().width, 1.1*visibleSize.height / bkgd->getContentSize().height);
    this->addChild(bkgd, 1);
    
    auto doors = MenuItemImage::create(
                                           S11DOORS,
                                           S11DOORS,
                                           CC_CALLBACK_1(Scene11::openDoors, this)
                                           );
    doors->setPosition(Vec2(0.5*visibleSize.width, 0.5*visibleSize.height));
    doors->setScale(0.43*visibleSize.width / doors->getContentSize().width,
                    0.54*visibleSize.height / doors->getContentSize().width);
    
    auto doormenu = Menu::create(doors, NULL);
    doormenu->setPosition(origin.x, origin.y);
    this->addChild(doormenu, -1);
    
    //add textbox
    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                              0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                      0.2*visibleSize.height / textBox->getContentSize().height);
    this->addChild(textBox, FRAMEDRAW + 1);
    
	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
	FrameNav frameNav;
	frameNav.addFrameNav(this);
    frameNav.bkgdMusic(2);
    
    UserDefault* def = UserDefault::getInstance();
    
    // Scripts
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene11");

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene11::gotoNextScene, this)
	);
    nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene11::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

    this->scheduleOnce(schedule_selector(Scene11::textAppears), 2);
	return true;
}

void Scene11::openDoors(Ref* pSender) {
    auto ppl = Sprite::create(S11PPL);
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    ppl->setPosition(Vec2(0.5*visibleSize.width + origin.x, 0.5*visibleSize.height + origin.y));
    ppl->setScale(0.43*visibleSize.width / ppl->getContentSize().width,
                    0.54*visibleSize.height / ppl->getContentSize().width);
    ppl->setOpacity(0);
    this->addChild(ppl, 0);
    
    ppl->runAction(Sequence::create(DelayTime::create(1),
                                      FadeIn::create(0.4),
                                      nullptr));
    this->scheduleOnce(schedule_selector(Scene11::waitNextScene), 3.0);
}

// Callback function to move on to the next scene
void Scene11::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene10::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void Scene11::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene08::createScene();
	Director::getInstance()->pushScene(nextScene);
}

void Scene11::waitNextScene(float dt) {
    auto nextScene = Scene10::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, nextScene));
}

void Scene11::textAppears(float dt)
{
    
    //// get text from json script object
    
    auto textString1 = Json_getString(script, "11.1", "Go Gators!");
    auto textString2 = Json_getString(script, "11.2", "Go Gators!");
    
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
    
}
