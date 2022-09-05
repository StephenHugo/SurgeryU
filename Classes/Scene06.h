#ifndef __SCENE_06_H__
#define __SCENE_06_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

class Scene06 : public Layer {
public:
	static Scene* createScene();
	virtual bool init();
    bool _actionComplete = true;
    Menu* menu;
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    
    void careButtonCallBack(Ref* pSender);
    
    void waitNextScene(float dt);
    
    void textAppears(float dt);
    Json* script;
    
	CREATE_FUNC(Scene06);
};
#endif // __SCENE_ONE_H__
