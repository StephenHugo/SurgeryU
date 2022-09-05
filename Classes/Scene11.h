#ifndef __SCENE_11_H__
#define __SCENE_11_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

class Scene11 : public Layer {
public:
	
	static Scene* createScene();
	virtual bool init();
	void gotoNextScene(Ref* pSender);
    void openDoors(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    
    void waitNextScene(float dt);
    
    void textAppears(float dt);
    Json* script;
    
	CREATE_FUNC(Scene11);
};
#endif // __SCENE_ONE_H__
