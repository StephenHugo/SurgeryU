#ifndef __SCENE_04_H__
#define __SCENE_04_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

class Scene04 : public Layer {
public:
	
	static Scene* createScene();
	virtual bool init();
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
	void gotoGameCallback(Ref* pSender);
    void gameButtonCallBack(float dt);
    void waitNextScene(float dt);
    
    void textAppears(float dt);
    Json* script;
    
	CREATE_FUNC(Scene04);
};
#endif // __SCENE_ONE_H__
