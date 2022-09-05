#ifndef __SCENE_08_H__
#define __SCENE_08_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

class Scene08 : public Layer {
public:
	
	static Scene* createScene();
	virtual bool init();
    bool _actionComplete = true;
	void gotoNextScene(Ref* pSender);
    
    void gotoCloserLook(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    void anethesiologistAppears(float dt);
    void closerlookAppears(float dt);
    
    void waitNextScene(float dt);
    
    void textAppears(float dt);
    void anesAppears(float dt);
    Json* script;
    
	CREATE_FUNC(Scene08);
};
#endif // __SCENE_ONE_H__
