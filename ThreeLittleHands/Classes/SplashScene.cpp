#include "SplashScene.h"
#include "GameLayer.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //CocosDenshion::SimpleAudioEngine::getInstance( )->preloadEffect( "Sounds/Hit.mp3" );
    //CocosDenshion::SimpleAudioEngine::getInstance( )->preloadEffect( "Sounds/Point.mp3" );
    //CocosDenshion::SimpleAudioEngine::getInstance( )->preloadEffect( "Sounds/Wing.mp3" );
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->scheduleOnce( schedule_selector( SplashScene::GoToMainMenuScene ), 2 );//DISPLAY_TIME_SPLASH_SCENE  = 2

    //auto backgroundSprite = Sprite::create( "Splash Screen.png" );
	auto backgroundSprite = Sprite::create( "splash_screen.png" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    
    this->addChild( backgroundSprite );
    
    return true;
}

void SplashScene::GoToMainMenuScene( float dt )
{
    auto scene = GameLayer::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5f, scene ) );//TRANSITION_TIME = 0.5
}



