#include "Scene08.h"
#include "Scene09.h"
#include "Scene11.h"
#include "Scene07.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

Scene* Scene08::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene08 class that inherits from Layer class
	auto layer = Scene08::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene08::init() {

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
    
	auto bkgd = Sprite::create(ROOMBKGD);
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);

    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                              0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                      0.2*visibleSize.height / textBox->getContentSize().height);
    this->addChild(textBox, FRAMEDRAW + 1);
	
    FrameNav frameNav;
    frameNav.addFrameNav(this);
    frameNav.bkgdMusic(2);
    
    UserDefault* def = UserDefault::getInstance();
    auto tookalook = def->getBoolForKey("CLOSERLOOK", false);
    
    // Scripts
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene08");
    
    // Menu Item to go to next scene
    auto nextScene = MenuItemImage::create(
                                           MOVEFWD,
                                           MOVEFWD,
                                           CC_CALLBACK_1(Scene08::gotoNextScene, this)
                                           );
    nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);
    
    // Menu Item to go to previous scene
    auto prevScene = MenuItemImage::create(
                                           MOVEBWD,
                                           MOVEBWD,
                                           CC_CALLBACK_1(Scene08::gotoPreviousScene, this)
                                           );
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);
    
    // Create the menu
    auto menu = Menu::create(nextScene, prevScene, NULL);
    menu->setPosition(Vec2::ANCHOR_MIDDLE);
    this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there
    
    if (!tookalook==true) {
        
        this->scheduleOnce(schedule_selector(Scene08::textAppears), 2);
        this->scheduleOnce(schedule_selector(Scene08::closerlookAppears), 6.0);
        
    } else {
        
        this->scheduleOnce(schedule_selector(Scene08::anesAppears), 1);
        this->scheduleOnce(schedule_selector(Scene08::anethesiologistAppears), 3.0);
    
    }
    
	return true;
}

void Scene08::anethesiologistAppears(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto meetButton = Sprite::create(meetyouranestesiologist);
    
    meetButton->setScaleX((visibleSize.width * 0.3) / meetButton->getContentSize().width);
    meetButton->setScaleY(meetButton->getScaleX());
    meetButton->setPosition(0.5*visibleSize.width + origin.x,
                            0.4*visibleSize.height + origin.y);
    this->addChild(meetButton, 4);
    
    auto meetListener = EventListenerTouchOneByOne::create();
    meetListener->setSwallowTouches(true);
    meetListener->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        auto meetBox = meetButton->getBoundingBox();
        //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
        if (meetBox.containsPoint(touch->getLocation())) {
            
            UserDefault* def = UserDefault::getInstance();
            def->setBoolForKey("CLOSERLOOK", false); // toggle original order
            def->flush();
            
            // Get size of the window being displayed to
            auto visibleSize = Director::getInstance()->getVisibleSize();
            
            // Get drawing origin of screen for sprites
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            
            auto clipboard = Sprite::create(HIANES);
            auto clip = Sprite::create(GAMEGOTIT);
            clipboard->addChild(clip);
            
            clipboard->setPosition(Vec2(origin.x + (visibleSize.width) * 0.5,
                                        origin.y + (visibleSize.height) * 0.5));
            clipboard->setScale(0.65*visibleSize.height / clipboard->getContentSize().height,
                                0.65*visibleSize.height / clipboard->getContentSize().height);
            clipboard->setOpacityModifyRGB(0);
            
            clip->setPosition(Vec2(clipboard->getContentSize().width * 0.5,
                                   clipboard->getContentSize().height * 0.025));
            clip->setScale(0.1*visibleSize.width/clip->getContentSize().width,
                           0.1*visibleSize.width/clip->getContentSize().width);
            clipboard->runAction(FadeIn::create(0.2));
            
            auto listen = EventListenerTouchOneByOne::create();
            
            //listen->setSwallowTouches(true);
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
                clipboard->runAction(Sequence::create(RemoveSelf::create(),
                                                      nullptr));
            };
            // Add listener
            Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, clipboard);
            this->addChild(clipboard, (FRAMEDRAW + 2));
            
            _eventDispatcher->removeEventListener(meetListener);
            meetButton->runAction(RemoveSelf::create());
            this->scheduleOnce(schedule_selector(Scene08::waitNextScene), 6.0);
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(meetListener, this);
}

void Scene08::closerlookAppears(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto takeCloserLookButton = Sprite::create(takeACloserLook);
    
    takeCloserLookButton->setScaleX((visibleSize.width * 0.3) / takeCloserLookButton->getContentSize().width);
    takeCloserLookButton->setScaleY(takeCloserLookButton->getScaleX());
    takeCloserLookButton->setPosition(0.5*visibleSize.width + origin.x,
                                      0.4*visibleSize.height + origin.y
                                      );
    this->addChild(takeCloserLookButton,4);
    
    // Touch Object
    auto takeCloserLookListener = EventListenerTouchOneByOne::create();
    takeCloserLookListener->onTouchBegan = [takeCloserLookButton, this](Touch *touch, Event *event) -> bool {
        auto takeCloserLookBox = takeCloserLookButton->getBoundingBox();
        //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
        if (takeCloserLookBox.containsPoint(touch->getLocation())) {
            return true;
        }
        return false;
    };
    
    takeCloserLookListener->onTouchEnded = [takeCloserLookButton, this](Touch *touch, Event *event) -> void {
        SpriteFrameCache::getInstance()->removeSpriteFrames();
        
        UserDefault* def = UserDefault::getInstance();
        def->setBoolForKey("CLOSERLOOK", true);
        def->flush();
        
        gotoCloserLook(this);
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(takeCloserLookListener, this);
}

// Callback function to move on to the next scene
void Scene08::gotoCloserLook(Ref* pSender) {
	auto nextScene = Scene09::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

void Scene08::gotoNextScene(Ref* pSender) {
    auto nextScene = Scene11::createScene();
    Director::getInstance()->replaceScene(nextScene);
}

void Scene08::waitNextScene(float dt) {
    auto nextScene = Scene11::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, nextScene));
}

// Callback function to move on to the previous scene
void Scene08::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene07::createScene();
	Director::getInstance()->pushScene(nextScene);
}

void Scene08::textAppears(float dt)
{
    
    //// get text from json script object
    
    auto textString1 = Json_getString(script, "8.1", "Go Gators!");
    auto textString2 = Json_getString(script, "8.2", "Go Gators!");
    
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

void Scene08::anesAppears(float dt)
{
    
    //// get text from json script object
    
    auto textString1 = Json_getString(script, "8.3", "Go Gators!");
    
    //// set up text
    
    // Added a framenav function so all text displays the same
    
    FrameNav fn;
    auto label1 = fn.createText(textString1, this);
    
    auto appear = FadeIn::create(0.2);
    
    label1->runAction(appear);
    
}
