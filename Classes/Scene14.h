#ifndef __SCENE_14_H__
#define __SCENE_14_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

class Scene14 : public Layer {
public:
	Json* script;
	static Scene* createScene();
	virtual bool init();
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    
    void gotoPopsicleCallback(Ref* pSender);
    void popsicleCallBack(float dt);
    
	CREATE_FUNC(Scene14);
};
#endif // __SCENE_ONE_H__
