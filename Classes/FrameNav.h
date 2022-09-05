#ifndef __FRAME_NAV_H__
#define __FRAME_NAV_H__

#include "ResourceDefinitions.h"

class FrameNav : public Scene {
private:
	int iconsFound = 0;

public:
	FrameNav();
	virtual ~FrameNav();
	Vector<Sprite*> icons;
	void addFrameNav(Scene* layer); // Fades in over 0.2 seconds
	void gotoMainMenu(Ref* pSender);
	void tapScreen(cocos2d::Scene *chapterLayer);
	void toggleBorder(int tag, Scene *frameLayer);
	void createIconBar(Scene* frameLayer);
	void toggleIconBar(int tag, Scene* frameLayer);
	void setIconFound();
	int getIconFound();
    
    void toggleSound(cocos2d::Ref* pSender, cocos2d::Scene *chapterLayer); // volume controls
    bool onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event,
                      cocos2d::DrawNode *node); // ugly code for volume controls
    Label* createText(const char *textString, Scene *chapterLayer);
    
    void bkgdMusic(int currentChapter);
};

#endif // __FRAME_NAV_H__
