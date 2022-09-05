#include "Scene04.h"
#include "PuzzleScene.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

enum {P1, P2, P3, P4};

Scene* PuzzleScene::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	// Create an instance of our DrawScene class that inherits from layer class
	auto layer = PuzzleScene::create();

	// Add layer to our scene
	scene->addChild(layer);

	// Scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool PuzzleScene::init() {

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
	auto chapterScript = Json_getItem(fullScript, language.c_str()); // fixed - had funky " marks
	script = Json_getItem(chapterScript, "Scene04");

    def->setBoolForKey("PUZZLED", true);
    def->flush();

	auto bkgd = Sprite::create(YELLOWBKGD);
	bkgd->setAnchorPoint(Vec2(0, 0));
	bkgd->setPosition(Vec2(origin.x, origin.y));
	bkgd->setScale(visibleSize.width / bkgd->getContentSize().width,
				   visibleSize.height / bkgd->getContentSize().height);
	this->addChild(bkgd, 0);

    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                              0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                      0.2*visibleSize.height / textBox->getContentSize().height);
    this->addChild(textBox, FRAMEDRAW + 1);

	//// get text from json script object

	auto textString = Json_getString(script, "4.3", "Go Gators!");

	//// set up text

    auto label = frameNav.createText(textString, this);
    label->setScale(1.8);
    label->setAlignment(TextHAlignment::CENTER);
    
    label->runAction(FadeIn::create(0.4));


	// ************** Static Sprites ************** 

	float POSX1 = 0.25f;
	float POSX2 = 0.65f;
	float POSY1 = 0.25f;
	float POSY2 = 0.65f;
    auto puzzleScale = 0.25f;

	auto puzzle1 = Sprite::create(PUZZLESW);
	//puzzle1->setAnchorPoint(Vec2(0, 0));
	puzzle1->setPosition(Vec2(origin.x + (visibleSize.width * (POSX1 + 0.03f)),
							  origin.y + (visibleSize.height * (POSY1 + 0.06f))));
	puzzle1->setScale(puzzleScale*w/puzzle1->getContentSize().width,
                      puzzleScale*w/puzzle1->getContentSize().width);
	this->addChild(puzzle1, 2);

	auto puzzle2 = Sprite::create(PUZZLENE);
	//puzzle2->setAnchorPoint(Vec2(0, 0));
	puzzle2->setPosition(Vec2(origin.x + (visibleSize.width * (POSX1)),
							  origin.y + (visibleSize.height * POSY2)));
    puzzle2->setScale(puzzleScale*w/puzzle2->getContentSize().width,
                      puzzleScale*w/puzzle2->getContentSize().width);
	this->addChild(puzzle2, 2);

	auto puzzle3 = Sprite::create(PUZZLESE);
	//puzzle3->setAnchorPoint(Vec2(0, 0));
	puzzle3->setPosition(Vec2(origin.x + (visibleSize.width * (POSX2 - 0.03f)),
							  origin.y + (visibleSize.height * (POSY1 + 0.1f))));
    puzzle3->setScale(puzzleScale*w/puzzle3->getContentSize().width,
                      puzzleScale*w/puzzle3->getContentSize().width);
	this->addChild(puzzle3, 2);

	auto puzzle4 = Sprite::create(PUZZLENW);
	//puzzle4->setAnchorPoint(Vec2(0, 0));
	puzzle4->setPosition(Vec2(origin.x + (visibleSize.width * (POSX2)),
							  origin.y + (visibleSize.height * (POSY2 + 0.06f))));
    puzzle4->setScale(puzzleScale*w/puzzle4->getContentSize().width,
                      puzzleScale*w/puzzle4->getContentSize().width);
	this->addChild(puzzle4, 2);

    std::vector<Sprite*> _objects;
    _objects.push_back(puzzle1);
    _objects.push_back(puzzle2);
    _objects.push_back(puzzle3);
    _objects.push_back(puzzle4);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto pos = touch->getLocation();
        for(int i = 0;i<4;i++){
            this->obj = i;
            auto puzzlepos = _objects[this->obj]->getPosition();
            if ((std::abs(puzzlepos.x-pos.x)/visibleSize.width < 0.15) && (std::abs(puzzlepos.y-pos.y)/visibleSize.height < 0.15)){
            
                _objects[this->obj]->runAction(Spawn::create(EaseIn::create(MoveTo::create(0.2, pos),0.2), ScaleBy::create(0.04, 1.02, 1.02),nullptr));
                _objects[this->obj]->setLocalZOrder(5);
                return true;
            }
        }
        return false;
        
    };
    
    listener->onTouchMoved = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        //// move the object around
        auto pos = touch->getLocation();
        
        _objects[this->obj]->setPosition(pos);
        
        return true;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto pos = touch->getLocation();
        auto siz = _objects[this->obj]->getContentSize();
        _objects[this->obj]->runAction(ScaleTo::create(0.04,
                                                       puzzleScale*w/_objects[this->obj]->getContentSize().width,
                                                       puzzleScale*w/_objects[this->obj]->getContentSize().width));
        _objects[this->obj]->setLocalZOrder(2);
        // need to move pieces back on screen if they are dropped off screen
        
        //_objects[this->obj]->runAction(MoveTo::create(0.4, Vec2(0.5*visibleSize.width, 0.5*visibleSize.height)));
        
        return true;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
	// ************** Menu Items for Scene **************

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		DONEBUTTON,
		DONEBUTTON,
		CC_CALLBACK_1(PuzzleScene::gotoNextScene, this)
	);
    nextScene->setPosition(Vec2(0.88*w + origin.x,
                                0.25*h + origin.y));
    nextScene->setScale(0.15*w / nextScene->getContentSize().width,
                        0.15*w / nextScene->getContentSize().width);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		BACKBUTTON,
		BACKBUTTON,
		CC_CALLBACK_1(PuzzleScene::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(0.12*w + origin.x,
                                0.25*h + origin.y));
    prevScene->setScale(0.15*w / prevScene->getContentSize().width,
                        0.15*w / prevScene->getContentSize().width);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

	return true;
}

// Callback function to move on to the next scene
void PuzzleScene::gotoNextScene(Ref * pSender) {
	auto nextScene = Scene04::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

// Callback function to move on to the previous scene
void PuzzleScene::gotoPreviousScene(Ref * pSender) {
	auto nextScene = PuzzleScene::createScene();
	Director::getInstance()->pushScene(nextScene);
}
