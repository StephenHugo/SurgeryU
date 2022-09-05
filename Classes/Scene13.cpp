#include "Scene13.h"
#include "Scene14.h"
#include "Scene12.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

Scene* Scene13::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene13 class that inherits from Layer class
	auto layer = Scene13::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene13::init() {

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

	auto bkgd = Sprite::create(FLAVORBKGD);
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);
    
    auto mask = Sprite::create(ANESMASK);
    
    mask->setPosition(Vec2(origin.x + visibleSize.width * 0.18,
                           origin.y + visibleSize.height * 0.62));
    mask->setScale(0.45 * h / mask->getContentSize().height,
                   0.45 * h / mask->getContentSize().height);
    mask->setRotation(15);
    this->addChild(mask, 1);
    
    auto buttonSize = 0.15f;
    
    auto melon = Sprite::create(ANESMELON);
    
    melon->setPosition(Vec2(origin.x + visibleSize.width * 0.16,
                            origin.y + visibleSize.height * 0.61));
    melon->setScale(buttonSize * h / melon->getContentSize().height,
                    buttonSize * h / melon->getContentSize().height);
    this->addChild(melon, 2);
    
    auto gum = Sprite::create(ANESGUM);
    
    gum->setPosition(Vec2(origin.x + visibleSize.width * 0.16,
                          origin.y + visibleSize.height * 0.45));
    gum->setScale(buttonSize * h / gum->getContentSize().height,
                  buttonSize * h / gum->getContentSize().height);
    this->addChild(gum, 2);
    
    auto berry = Sprite::create(ANESBERRY);
    
    berry->setPosition(Vec2(origin.x + visibleSize.width * 0.16,
                            origin.y + visibleSize.height * 0.29));
    berry->setScale(buttonSize * h / berry->getContentSize().height,
                    buttonSize * h / berry->getContentSize().height);
    this->addChild(berry, 2);

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
    frameNav.bkgdMusic(3);

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene13::gotoNextScene, this)
	);
    nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene13::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto grow = ScaleBy::create(4, 1.6, 1.6);
        auto rotate = MoveBy::create(5, Vec2(0.4*visibleSize.width, 0.1*visibleSize.height));
        auto selected = Spawn::create(grow, rotate, nullptr);
        auto pos = touch->getLocation();
        auto x = (pos.x - origin.x)/visibleSize.width;
        auto y = (pos.y - origin.y)/visibleSize.height;
        
        if (std::abs(x-0.16)<0.1){
            if (std::abs(y-0.41)<0.08){
                gum->runAction(selected);
                return true;
            } else if (std::abs(y-0.61)<0.08) {
                melon->runAction(selected);
                return true;
            } else if (std::abs(y-0.3)<0.08) {
                berry->runAction(selected);
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
        return false;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event) {
        
        this->scheduleOnce(schedule_selector(Scene13::waitNextScene), 1);
        return true;
    };
        
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
    return true;
}

// Callback function to move on to the next scene
void Scene13::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene14::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void Scene13::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene12::createScene();
	Director::getInstance()->pushScene(nextScene);
}

void Scene13::waitNextScene(float dt){
    auto nextScene = Scene14::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(5, nextScene));
};
