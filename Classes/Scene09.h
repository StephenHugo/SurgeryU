#ifndef __SCENE_09_H__
#define __SCENE_09_H__

#include "ResourceDefinitions.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

class Scene09 : public Layer {
public:
	
	static Scene* createScene();
	virtual bool init();
    Menu* menu;
    FrameNav* frameNav;
    void ispyCallBack(Ref* pSender, int object);
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    void enableMenu(float dt);
    void toggleIcon(float dt);
    
    void waitNextScene(float dt);
    
    void textAppears(float dt);
    Json* script;
    
    Label* sceneLabel;
    Label* tempLabel;
    void replaceLabel(const char* name, float dt);
    void pulseDelay(float dt);
    
	CREATE_FUNC(Scene09);
};
#endif // __SCENE_ONE_H__
