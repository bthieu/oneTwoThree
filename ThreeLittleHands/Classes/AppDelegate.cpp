#include "AppDelegate.h"
#include "GameLayer.h"
#include "SplashScene.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        //glview = GLView::create("My Game");
		glview = GLView::createWithRect("Three Little Hands",Rect(200,200,360,480));
        director->setOpenGLView(glview);
    }

	Size screenSize = glview->getFrameSize();
	Size designSize = Size(720,960);
	glview->setDesignResolutionSize(designSize.width,  designSize.height, ResolutionPolicy::EXACT_FIT);


	
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("cover_toggle.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("fail.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("fire_paper.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("fire_rock.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("fire_scissor.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("hit_block.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("hit_shield.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("play.wav");
	//SimpleAudioEngine::getInstance()->preloadEffect("hit_block.wav");

	SimpleAudioEngine::getInstance()->setEffectsVolume(0.4f);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = GameLayer::createScene();
	auto scene = SplashScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
