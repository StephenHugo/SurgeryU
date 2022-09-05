#include "Scene06.h"
#include "Scene07.h"
#include "Scene04.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

Scene* Scene06::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene06 class that inherits from Layer class
	auto layer = Scene06::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene06::init() {

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

	auto bkgd = Sprite::create(ELEVATORBKGD);
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);

	auto mom = Sprite::create(MOM05);
	mom->setPosition(0.15*w + origin.x,
                     0.45*h + origin.y);
    mom->setScale(0.65*h/mom->getContentSize().height,
                  0.65*h/mom->getContentSize().height);
    this->addChild(mom, 1);
    
    auto patient = Sprite::create(PATIENT05);
    patient->setPosition(0.35*w + origin.x,
                         0.35*h + origin.y);
    patient->setScale(0.45*h/patient->getContentSize().height,
                      0.45*h/patient->getContentSize().height);
	this->addChild(patient, 2);

	auto nurse = Sprite::create(NURSE05);
    nurse->setPosition(0.6*w + origin.x,
                       0.45*h + origin.y);
    nurse->setScale(0.7*h/nurse->getContentSize().height,
                    0.7*h/nurse->getContentSize().height);
	this->addChild(nurse, 1);

	//add elevator buttons
	auto elevatorup = Sprite::create(ELEVATORBUTTONUP);
    elevatorup->setScale(0.038*w/elevatorup->getContentSize().width,
                         0.038*w/elevatorup->getContentSize().height);
    elevatorup->setPosition(0.93*w,
                            0.68*h);
	this->addChild(elevatorup, 1);
    
    auto elevatordown = Sprite::create(ELEVATORBUTTONDOWN);
    elevatordown->setScale(0.038*w/elevatordown->getContentSize().width,
                         0.038*w/elevatordown->getContentSize().height);
    elevatordown->setPosition(0.93*w,
                            0.68*h-0.045*w);
    this->addChild(elevatordown, 1);

	//add elevator button
	auto elevatorgreen = Sprite::create(GREENELEVATORBUTTON);
    elevatorgreen->setScale(0.038*w/elevatorgreen->getContentSize().width,
                            0.038*w/elevatorgreen->getContentSize().height);
	elevatorgreen->setPosition(0.93*w,
                               0.68*h);
	this->addChild(elevatorgreen, 1);
	elevatorgreen->setVisible(false);

	//add textbox
    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                              0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                      0.2*visibleSize.height / textBox->getContentSize().height);
    this->addChild(textBox, FRAMEDRAW + 1);
    
    auto meetYourNurseButton = MenuItemImage::create(
                                      BUTTON06,
                                      BUTTON06,
                                      CC_CALLBACK_1(Scene06::careButtonCallBack, this)
                                      );
    meetYourNurseButton->setPosition(0.7*w + origin.x,
                                     0.35*h + origin.y);
    meetYourNurseButton->setScale(0.35*w/meetYourNurseButton->getContentSize().width,
                                  0.35*w/meetYourNurseButton->getContentSize().width);
//Actions----------------------------------------------------------------------------------------------------
	// Touch Object 
	auto elevatorlistener = EventListenerTouchOneByOne::create();
	elevatorlistener->onTouchBegan = [elevatorgreen, this](Touch *touch, Event *event) -> bool {
		auto elevatorBox = elevatorgreen->getBoundingBox();
		
        // I like this way of doing it very much, great solution!
		if (elevatorBox.containsPoint(touch->getLocation())) {
			return true;
		}
		return false;
	};

	elevatorlistener->onTouchEnded = [elevatorgreen, this](Touch *touch, Event *event) -> void {
		
		//show green elevator button
		elevatorgreen->setVisible(true);
        
        // go to next scene
        this->scheduleOnce(schedule_selector(Scene06::waitNextScene), 2);
	};

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(elevatorlistener, this);

	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
	FrameNav frameNav;
	frameNav.addFrameNav(this);
    frameNav.bkgdMusic(1);
    
    // Scripts
    UserDefault* def = UserDefault::getInstance();
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene06");

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene06::gotoNextScene, this)
	);
    nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene06::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	this->menu = Menu::create(nextScene, prevScene, meetYourNurseButton, NULL);
	this->menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(this->menu, (FRAMEDRAW + 1)); // Please note that the one must be there

    this->scheduleOnce(schedule_selector(Scene06::textAppears), 2);
    
	return true;
}

void Scene06::careButtonCallBack(Ref* pSender) {
    
    // Disable menu
    this->menu->setEnabled(false);
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto clipboard = Sprite::create(HINURSE);
    auto clip = Sprite::create(CLIPGOTIT);
    clipboard->addChild(clip);
    
    clipboard->setPosition(Vec2(origin.x + (visibleSize.width) * 0.5,
                                origin.y + (visibleSize.height) * 0.5));
    clipboard->setScale(0.65*visibleSize.height / clipboard->getContentSize().height,
                        0.65*visibleSize.height / clipboard->getContentSize().height);
    clipboard->setOpacityModifyRGB(0);
    clip->setPosition(Vec2(clipboard->getContentSize().width * 0.5,
                           clipboard->getContentSize().height * 0.04));
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
        menu->setEnabled(true);
        
    };
    
    // Add listener
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, clipboard);
    this->addChild(clipboard, (FRAMEDRAW + 12345));
};

void Scene06::textAppears(float dt)
{
        
    //// get text from json script object
    
    auto textString1 = Json_getString(script, "6.1", "Go Gators!");
    auto textString2 = Json_getString(script, "6.2", "Go Gators!");
    
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

void Scene06::waitNextScene(float dt) {
    
    /// add audio for elevator ding?
    auto nextScene = Scene07::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, nextScene));
}

// Callback function to move on to the next scene
void Scene06::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene07::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void Scene06::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene04::createScene();
	Director::getInstance()->pushScene(nextScene);
}
