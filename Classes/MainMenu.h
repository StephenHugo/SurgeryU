#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "ResourceDefinitions.h"

class MainMenu : public Scene
{
public:

	// Added variable to ensure un-interrupted run actions
	bool _actionComplete = true;
    Menu* menu;
    
	static Scene* createScene();
	virtual bool init();
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
	void exitCallBack(Ref* pSender);
    void careButtonCallBack(Ref* pSender);
    void gameButtonCallBack(Ref* pSender);
    void gotoCredits(Ref* pSender);
    void gotoLaunch(float dt);
	CREATE_FUNC(MainMenu);
};
#endif // __MAINMENU_H__
