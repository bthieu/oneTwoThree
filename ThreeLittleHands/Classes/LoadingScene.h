#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

class LoadingScene : public cocos2d::Layer
{
public:
	//cocos2d::Scene* _gameScene; 
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadingScene);
    
private:
    void GoToGameScene(float dt);
    
};

#endif // __LOADING_SCENE_H__