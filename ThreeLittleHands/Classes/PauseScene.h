#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

class PauseScene : public cocos2d::Layer
{
public:
	//cocos2d::Scene* _gameScene; 
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(PauseScene);
    
private:
    void replay(Ref* pSender);
    void goToMenu(Ref* pSender);
	void quit(Ref* pSender);
};

#endif // __PAUSE_SCENE_H__