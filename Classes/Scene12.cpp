#include "Scene12.h"
#include "Scene13.h"
#include "Scene11.h"
#include "Scene10.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

Scene* Scene12::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene12 class that inherits from Layer class
	auto layer = Scene12::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene12::init() {

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

	auto bkgd = Sprite::create(S12BKGD);
	bkgd->setAnchorPoint(Vec2(0, 0));
	bkgd->setPosition(Vec2(origin.x, origin.y));
	bkgd->setScale(visibleSize.width / bkgd->getContentSize().width, visibleSize.height / bkgd->getContentSize().height);
	this->addChild(bkgd);

    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                              0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                      0.2*visibleSize.height / textBox->getContentSize().height);
    this->addChild(textBox, FRAMEDRAW + 1);
	
    auto anes = Sprite::create(Anes);
    anes->setPosition(0.2*w + origin.x,
                      0.4*h + origin.y);
    anes->setScale(0.8*h/anes->getContentSize().height,
                   0.8*h/anes->getContentSize().height);
    this->addChild(anes, 3);
    
    auto mask = MenuItemImage::create(
                                       Mask32,
                                       Mask32,
                                       CC_CALLBACK_1(Scene12::maskButtonCallBack, this));
    
    
    
    mask->setPosition(Vec2(origin.x + w * 0.67,
                           origin.y + h * 0.65)
                      );
    mask->setScale(0.1 * h / mask->getContentSize().height,
                   0.1 * h/ mask->getContentSize().height);
    mask->setRotation(60);
    auto maskmenu = Menu::create(mask, NULL);
    maskmenu->setPosition(Vec2::ANCHOR_MIDDLE);
    this->addChild(maskmenu, 4);
    
    auto sleepmach = Sprite::create(MACHINE);
    sleepmach->setPosition(0.65*w + origin.x,
                           0.5*h + origin.y);
    sleepmach->setScale(0.9*visibleSize.height / sleepmach->getContentSize().height,
                        0.9*visibleSize.height / sleepmach->getContentSize().height
                        );
    this->addChild(sleepmach, 2);

  	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
    FrameNav temp;
    temp.addFrameNav(this);
    this->frameNav = &temp;
    this->frameNav->bkgdMusic(3);

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		DONEBUTTON,
		DONEBUTTON,
		CC_CALLBACK_1(Scene12::gotoNextScene, this)
	);
    nextScene->setPosition(Vec2(0.88*w + origin.x,
                                0.2*h + origin.y));
    nextScene->setScale(0.15*w / nextScene->getContentSize().width,
                        0.15*w / nextScene->getContentSize().width);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		BACKBUTTON,
		BACKBUTTON,
		CC_CALLBACK_1(Scene12::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(0.12*w + origin.x,
                                0.2*h + origin.y));
    prevScene->setScale(0.15*w / prevScene->getContentSize().width,
                        0.15*w / prevScene->getContentSize().width);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

	return true;
}

void Scene12::maskButtonCallBack(Ref* pSender){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // Create star for found icon once touched
    UserDefault * def = UserDefault::getInstance();
    
    auto iSpyName = def->getBoolForKey("ISPYMASKFOUND", false);
    
    if (!iSpyName) {
        def->setBoolForKey("ISPYMASKFOUND", true);
        def->flush();
        
        // This star shows up for effect once desired icon is clicked
        auto star = Sprite::create(STARSHINE);
        star->setPosition(Vec2(origin.x + (0.65 * visibleSize.width),
                               origin.y + (0.68 * visibleSize.height)));
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
        
        this->scheduleOnce(schedule_selector(Scene12::foundStarCallBack), 3);
    } else {
        
        auto clipboard = MenuItemImage::create(
                                               PICKFLAVORBUTTON,
                                               PICKFLAVORBUTTON,
                                               CC_CALLBACK_1(Scene12::gotoNextScene, this));
        clipboard->setScale(0.14*visibleSize.width / clipboard->getContentSize().width,
                            0.12*visibleSize.height / clipboard->getContentSize().height);
        clipboard->setPosition(Vec2(0.8*visibleSize.width,
                                    0.8*visibleSize.height));
        
        auto braceletMenu = Menu::create(clipboard, NULL);
        braceletMenu->setOpacityModifyRGB(0);
        braceletMenu->setPosition(origin.x, origin.y);
        
        this->addChild(braceletMenu, 25); // Please note that the one must be there
        
        braceletMenu->runAction(Spawn::create(FadeIn::create(0.2),
                                              ScaleBy::create(0.2, 1.1),
                                              EaseBounceOut::create(MoveBy::create(0.6,Vec2(0,-0.05*visibleSize.height))), nullptr));
    }
};

void Scene12::foundStarCallBack(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->frameNav->createIconBar(this);
    auto label = Label::createWithTTF("Whoooooooaaaa!!!! You found the mask! Great job. You get a star!", FELTFONT, visibleSize.height * TEXTSIZE);
    label->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.11 + origin.y));
    label->setWidth(0.56 * visibleSize.width);
    label->setHeight(visibleSize.height * 3.0 / 20);
    
    label->setColor(cocos2d::Color3B::BLACK);
    label->setOpacity(0);
    this->addChild(label, FRAMEDRAW+45);
    label->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(4), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    this->scheduleOnce(schedule_selector(Scene12::waitNextScene), 5);
    
};

void Scene12::waitNextScene(float dt) {
    auto nextScene = Scene13::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, nextScene));
}

// Callback function to move on to the next scene
void Scene12::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene13::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void Scene12::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene10::createScene();
	Director::getInstance()->pushScene(nextScene);
}
