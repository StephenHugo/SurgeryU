#include "Scene09.h"
#include "Scene10.h"
#include "Scene08.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

enum {PICKCUFF, PICKTHERMO, PICKPULSE, PICKELEC};

Scene* Scene09::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene09 class that inherits from Layer class
	auto layer = Scene09::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene09::init() {

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

	auto bkgd = Sprite::create(CLOSERLOOKBKGD);
	bkgd->setAnchorPoint(Vec2(0, 0));
	bkgd->setPosition(Vec2(origin.x, origin.y));
	bkgd->setScale(visibleSize.width / bkgd->getContentSize().width, visibleSize.height / bkgd->getContentSize().height);
	this->addChild(bkgd);
    
    auto Cuff = MenuItemImage::create(
                                           cuff,
                                           cuff,
                                           CC_CALLBACK_1(Scene09::ispyCallBack, this, PICKCUFF)
                                           );
    
	Cuff->setAnchorPoint(Vec2(0,0));
	Cuff->setPosition(Vec2(origin.x + w * 0.08,
                           origin.y + h * 0.35));
	Cuff->setScale(0.6 * h / bkgd->getContentSize().height,
                   0.6 * h / bkgd->getContentSize().height);
    Cuff->setTag(PICKCUFF);
	
    auto Thermo = MenuItemImage::create(
                                      thermometer,
                                      thermometer,
                                      CC_CALLBACK_1(Scene09::ispyCallBack, this, PICKTHERMO)
                                      );
    
	Thermo->setAnchorPoint(Vec2(0,0));
	Thermo->setPosition(Vec2(origin.x + w * 0.2,
                             origin.y + h * 0.49));
	Thermo->setScale(0.6*h / bkgd->getContentSize().height,
                     0.6*h / bkgd->getContentSize().height);
    Thermo->setTag(PICKTHERMO);

    auto Pulse = MenuItemImage::create(
                                      pulseox,
                                      pulseox,
                                      CC_CALLBACK_1(Scene09::ispyCallBack, this, PICKPULSE)
                                      );
    
	Pulse->setAnchorPoint(Vec2(0,0));
	Pulse->setPosition(Vec2(origin.x + w * 0.38,
                            origin.y + h * 0.26));
    Pulse->setScale(0.6*h / bkgd->getContentSize().height,
                    0.6*h / bkgd->getContentSize().height);
    Pulse->setTag(PICKPULSE);

    auto Elec = MenuItemImage::create(
                                       electrodes,
                                       electrodes,
                                       CC_CALLBACK_1(Scene09::ispyCallBack, this, PICKELEC)
                                       );
    
	Elec->setAnchorPoint(Vec2(0,0));
	Elec->setPosition(Vec2(origin.x + w * 0.22,
                           origin.y + h * 0.28));
    Elec->setScale(0.6*h / bkgd->getContentSize().height,
                   0.6*h / bkgd->getContentSize().height);
    Elec->setTag(PICKELEC);

    this->menu = Menu::create(Cuff, Thermo, Pulse, Elec, NULL);
    this->menu->setPosition(Vec2::ANCHOR_MIDDLE);
    this->menu->setEnabled(false);
    this->addChild(this->menu, (FRAMEDRAW + 1)); // Please note that the one must be there
    
	//add textbox
    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                              0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                      0.2*visibleSize.height / textBox->getContentSize().height);
    this->addChild(textBox, FRAMEDRAW + 1);

	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
    FrameNav temp;
    temp.addFrameNav(this);
    this->frameNav = &temp;
    this->frameNav->bkgdMusic(2);
    
    // Scripts
    UserDefault* def = UserDefault::getInstance();
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene09");

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene09::gotoNextScene, this)
	);
    nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene09::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	auto menu2 = Menu::create(nextScene, prevScene, NULL);
	menu2->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu2, (FRAMEDRAW + 1)); // Please note that the one must be there
    
    this->scheduleOnce(schedule_selector(Scene09::textAppears), 2);

	return true;
}

void Scene09::ispyCallBack(Ref* pSender, int object){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->menu->setEnabled(false);
    
    UserDefault * def = UserDefault::getInstance();
    
    auto iSpyName = 0;
    switch (object) {
        case PICKCUFF:
            iSpyName = def->getBoolForKey("ISPYBPFOUND", false);
            break;
            
        case PICKTHERMO:
            iSpyName = def->getBoolForKey("ISPYTHERMOFOUND", false);
            break;
    
        case PICKPULSE:
            iSpyName = def->getBoolForKey("ISPYPULSEOXFOUND", false);
            break;
    
        case PICKELEC:
            iSpyName = def->getBoolForKey("ISPYELECFOUND", false);
            break;
    
        default:
            break;
    }
    
    if (!iSpyName) {
        
        auto star = Sprite::create(STARSHINE);
        
        switch (object) {
            case PICKCUFF:
                def->setBoolForKey("ISPYBPFOUND", true);
                def->flush();
                
                Scene09::replaceLabel("9.2", 3);
                
                star->setPosition(Vec2(origin.x + (0.15 * visibleSize.width),
                                       origin.y + (0.4 * visibleSize.height)));
                break;
                
            case PICKTHERMO:
                def->setBoolForKey("ISPYTHERMOFOUND", true);
                def->flush();
                
                Scene09::replaceLabel("9.6", 3);
                
                star->setPosition(Vec2(origin.x + (0.25 * visibleSize.width),
                                       origin.y + (0.5 * visibleSize.height)));
                break;
                
            case PICKPULSE:
                def->setBoolForKey("ISPYPULSEOXFOUND", true);
                def->flush();
                
                Scene09::replaceLabel("9.4", 3);
                
                star->setPosition(Vec2(origin.x + (0.42 * visibleSize.width),
                                       origin.y + (0.35 * visibleSize.height)));
                break;
                
            case PICKELEC:
                def->setBoolForKey("ISPYELECFOUND", true);
                def->flush();
                
                Scene09::replaceLabel("9.8", 3);
                
                star->setPosition(Vec2(origin.x + (0.27 * visibleSize.width),
                                       origin.y + (0.37 * visibleSize.height)));
                break;
                
            default:
                break;
        }
        
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
        
        this->scheduleOnce(schedule_selector(Scene09::toggleIcon), 3);
        this->scheduleOnce(schedule_selector(Scene09::enableMenu), 4);
    } else {
        this->menu->setEnabled(false);
        auto sprite = this->menu->getChildByTag(object);
        auto sclx = sprite->getScaleX();
        auto scly = sprite->getScaleY();
        auto pos = sprite->getPosition();
        
        auto listener = EventListenerTouchOneByOne::create();
        
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
            
            return true;
            
        };
        
        listener->onTouchMoved = [=](cocos2d::Touch *touch, cocos2d::Event *event){
            
            //// move the object around
            auto temppos = touch->getLocation();
            
            sprite->setPosition(temppos);
            
            return true;
        };
        
        listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event){
            
            sprite->runAction(Spawn::create(ScaleTo::create(0.4, sclx, scly),
                                            MoveTo::create(0.4, pos),
                                            RotateTo::create(0.4, 0),
                                            nullptr));
            Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
            this->scheduleOnce(schedule_selector(Scene09::enableMenu), 0.4);
            return true;
        };
        
        auto pulseExtended = Sprite::create(pulseoxclicked); // files mislabeled
        auto elecExtended = Sprite::create(electrodesclicked); // files mislabeled
        
        switch (object) {
            case PICKCUFF:
                sprite->runAction(Sequence::create(Spawn::create(MoveTo::create(0.6, Vec2(origin.x + 0.475 * visibleSize.width, origin.y + 0.32 * visibleSize.height)),
                                                                 RotateBy::create(0.6, 360),
                                                                 ScaleBy::create(0.6, 1.45),
                                                                 nullptr),
                                                   DelayTime::create(4),
                                                   FadeOut::create(0.2),
                                                   MoveTo::create(0.08, pos),
                                                   ScaleTo::create(0.1, sclx, scly),
                                                   FadeIn::create(0.4),
                                                   nullptr));
                
                Scene09::replaceLabel("9.1", 5);
                this->scheduleOnce(schedule_selector(Scene09::enableMenu), 5.4);
                break;
                
            case PICKTHERMO:
                
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
                
                sprite->runAction(Spawn::create(ScaleBy::create(0.4, 1.4, 1.4),
                                                RotateBy::create(0.4, -60),
                                                nullptr));
                
                Scene09::replaceLabel("9.5", 4);
                break;
                
            case PICKPULSE:
                
                sprite->runAction(Sequence::create(FadeOut::create(0.4),
                                                   DelayTime::create(5.5),
                                                   FadeIn::create(0.4),
                                                   nullptr));
                pulseExtended->setOpacity(0);
                pulseExtended->setPosition(Vec2(origin.x + 0.49 * visibleSize.width, origin.y + 0.35 * visibleSize.height));
                pulseExtended->setScale(sclx/1, scly/1);
                this->addChild(pulseExtended, FRAMEDRAW);
                pulseExtended->runAction(Sequence::create(DelayTime::create(0.6),
                                                          FadeIn::create(0.4),
                                                          DelayTime::create(4.7),
                                                          FadeOut::create(0.4),
                                                          RemoveSelf::create(),
                                                          nullptr));
                
                Scene09::replaceLabel("9.31", 3);
                this->scheduleOnce(schedule_selector(Scene09::pulseDelay), 3);
                this->scheduleOnce(schedule_selector(Scene09::enableMenu), 6.4);
                
                break;
                
            case PICKELEC:
                
                sprite->runAction(Sequence::create(FadeOut::create(0.4),
                                                   DelayTime::create(2.5),
                                                   FadeIn::create(0.4),
                                                   nullptr));
                elecExtended->setOpacity(0);
                elecExtended->setPosition(Vec2(origin.x + 0.49 * visibleSize.width, origin.y + 0.38 * visibleSize.height));
                elecExtended->setScale(sclx*1.2, scly*1.2);
                elecExtended->setRotation(-5);
                this->addChild(elecExtended, FRAMEDRAW);
                elecExtended->runAction(Sequence::create(DelayTime::create(0.6),
                                                          FadeIn::create(0.4),
                                                          DelayTime::create(1.7),
                                                          FadeOut::create(0.4),
                                                          RemoveSelf::create(),
                                                          nullptr));
                
                Scene09::replaceLabel("9.7", 3);
                this->scheduleOnce(schedule_selector(Scene09::enableMenu), 3.4);
                break;
                
            default:
                break;
        }
    }
};

void Scene09::toggleIcon(float dt) {
    // If used to create an icon bar
    this->frameNav->createIconBar(this);

}

void Scene09::pulseDelay(float dt) {
    
    Scene09::replaceLabel("9.32", 3);
}

// Callback function to move on to the next scene
void Scene09::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene08::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void Scene09::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene08::createScene();
	Director::getInstance()->pushScene(nextScene);
}

void Scene09::enableMenu(float dt) {
    
    this->menu->setEnabled(true);
}

void Scene09::textAppears(float dt)
{
    
    this->menu->setEnabled(true);
    //// get text from json script object
    
    auto textString = Json_getString(script, "9.0", "Go Gators!");
    ;
    //// set up text
    
    // Added a framenav function so all text displays the same
    
    FrameNav fn;
    this->sceneLabel = fn.createText(textString, this);
    
    auto appear = FadeIn::create(0.2);
    
    
    this->sceneLabel->runAction(appear);
    
}

void Scene09::replaceLabel(const char* name, float dt)
{
    
    this->sceneLabel->stopAllActions();
    
    FrameNav fn;
    auto textString = Json_getString(script, name, "Go Gators!");
    this->tempLabel = fn.createText(textString, this);
    
        
    this->sceneLabel->runAction(Sequence::create(FadeOut::create(0.4),
                                                 DelayTime::create( dt ),
                                                 FadeIn::create(0.2),
                                                 nullptr));
    
    this->tempLabel->runAction(Sequence::create(DelayTime::create(0.4),
                                                FadeIn::create(0.2),
                                                DelayTime::create( dt - 0.6),
                                                FadeOut::create(0.4),
                                                nullptr));
}
