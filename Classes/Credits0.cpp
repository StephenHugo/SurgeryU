#include "LaunchScreen.h"
#include "MainMenu.h"
#include "Credits0.h"
#include "spine/Json.h"
using namespace spine;
#include "FrameNav.h"

Scene* Credits::createScene() {
	return Credits::create();
}

bool Credits::init() {

	// Ensure layer from createScene() was created
	if (!Scene::init()) {
		return false;
	}

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    FrameNav fn;
    fn.bkgdMusic(0);

    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;
    
    auto bkgd = MenuItemImage::create(
                                      S15BKGD,
                                      S15BKGD,
                                      CC_CALLBACK_1(Credits::gotoNextScene, this)
                                      );
    
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
    auto menu = Menu::create(bkgd, NULL);
    menu->setPosition(center);
    this->addChild(menu, -1);

    auto textBox = Sprite::create(TEXTBOX);
    textBox->setPosition(Vec2(origin.x + visibleSize.width/2,
                              origin.y + visibleSize.height/2));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                      0.4*visibleSize.height / textBox->getContentSize().height);
    
    // Script stuff
    auto f = FileUtils::getInstance();
    auto scriptString = f->getStringFromFile("scripts/masterscript.txt");
    
    Json *fullScript;
    fullScript = new(__FILE__, __LINE__) Json( scriptString.c_str() );
    
    //script = Json::getItem( fullScript, "Credits" );
    auto textString = Json::getString(fullScript, "Credits", "Go Gators!");
    
    auto creditsText = Label::createWithTTF(textString, FELTFONT, visibleSize.height * TEXTSIZE*1.2);
    creditsText->setDimensions(0.8*textBox->getContentSize().width,
                               0.8*textBox->getContentSize().height);
    creditsText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.5*textBox->getContentSize().height));
    creditsText->setColor(cocos2d::Color3B::BLACK);
    creditsText->setAlignment(TextHAlignment::CENTER);
    
    textBox->addChild(creditsText, 1);
    this->addChild(textBox, FRAMEDRAW + 5);
    
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(Credits::gotoMenu), 9);
    return true;
}

// Callback function to move on to the next scene
void Credits::gotoNextScene(Ref* pSender) {
	auto nextScene = MainMenu::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME,nextScene));
}

void Credits::gotoMenu(float dt) {
    auto nextScene = MainMenu::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME, nextScene));
    
}
