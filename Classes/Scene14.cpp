#include "Scene14.h"
#include "Scene15.h"
#include "Scene13.h"
#include "FrameNav.h"
#include "PopsicleScene.h"
#include "editor-support/spine/Json.h"

Scene* Scene14::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene14 class that inherits from Layer class
	auto layer = Scene14::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene14::init() {

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
    
	auto bkgd = Sprite::create(POSTOPBKGD);
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);
	
	auto doc = Sprite::create(postdoc);
    doc->setPosition(Vec2(origin.x + w * 0.16,
                          origin.y + h * 0.37)
                     );
    doc->setScale(0.8*h / doc->getContentSize().height,
                  0.8*h / doc->getContentSize().height);
	this->addChild(doc, 1);
	
	auto iv = Sprite::create(postIV);
    iv->setPosition(Vec2(origin.x + w * 0.67,
                         origin.y + h * 0.55)
                    );
    iv->setScale(0.56*h / iv->getContentSize().height,
                 0.56*h / iv->getContentSize().height);
	this->addChild(iv, 1);
	
	auto chair = Sprite::create(postchair);
	
    chair->setPosition(Vec2(origin.x + w * 0.83,
                            origin.y + h * 0.35)
                       );
	chair->setScale(0.35*h / chair->getContentSize().height,
                    0.35*h / chair->getContentSize().height);
	this->addChild(chair, 2);
	
	auto mom = Sprite::create(postmom);
	
    mom->setPosition(Vec2(origin.x + w * 0.8,
                          origin.y + h * 0.35)
                     );
	mom->setScale(0.65*h / mom->getContentSize().height,
                  0.65*h / mom->getContentSize().height);
	this->addChild(mom, 3);
	
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
    frameNav.bkgdMusic(4);

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene14::gotoNextScene, this)
	);
    nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene14::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

    this->scheduleOnce(schedule_selector(Scene14::popsicleCallBack), 3);
    
	return true;
}

// Callback function to move on to the next scene
void Scene14::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene15::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void Scene14::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene13::createScene();
	Director::getInstance()->pushScene(nextScene);
}

void Scene14::popsicleCallBack(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto clipboard = MenuItemImage::create(
                                           TRYPOPBUTTON,
                                           TRYPOPBUTTON,
                                           CC_CALLBACK_1(Scene14::gotoPopsicleCallback, this));
    clipboard->setScale(0.24*visibleSize.width / clipboard->getContentSize().width,
                        0.2*visibleSize.height / clipboard->getContentSize().height);
    clipboard->setPosition(Vec2(0.5*visibleSize.width,
                                0.45*visibleSize.height));
    
    auto braceletMenu = Menu::create(clipboard, NULL);
    braceletMenu->setOpacityModifyRGB(0);
    braceletMenu->setPosition(origin.x, origin.y);
    
    this->addChild(braceletMenu, 2); // Please note that the one must be there
    
    braceletMenu->runAction(Spawn::create(FadeIn::create(0.2),
                                          ScaleBy::create(0.2, 1.1),
                                          EaseBounceOut::create(MoveBy::create(0.6,Vec2(0,-0.05*visibleSize.height))), nullptr));
    
};

// Callback function to move to the popsicle scene
void Scene14::gotoPopsicleCallback(Ref* pSender) {
    auto nextScene = Popsicle::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.8, nextScene));
};
