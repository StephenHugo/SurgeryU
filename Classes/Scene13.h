#ifndef __SCENE_13_H__
#define __SCENE_13_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

class Scene13 : public Layer {
public:
	Json* script;
	static Scene* createScene();
	virtual bool init();
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    void waitNextScene(float dt);
	CREATE_FUNC(Scene13);
};
#endif // __SCENE_ONE_H__
