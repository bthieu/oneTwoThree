#include "MenuScene.h"
#include "GameLayer.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
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
    
    //this->scheduleOnce( schedule_selector( SplashScene::GoToMainMenuScene ), 2 );//DISPLAY_TIME_SPLASH_SCENE  = 2
	    
	//auto backgroundSprite = Sprite::create( "splash_screen.png" );
 //   backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
 //   
 //   this->addChild( backgroundSprite );

	auto backgroundSprite = Sprite::create( "background_menu.png" );
    backgroundSprite->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );    
    this->addChild( backgroundSprite , kBackground);

	auto titleSprite = Sprite::create( "title.png" );
    titleSprite->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 6*5 + origin.y) );    
    this->addChild( titleSprite , kMiddleground);

	//auto playBtnSprite = Sprite::create( "play_btn_up.png" );
 //   playBtnSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );    
 //   this->addChild( playBtnSprite , 1);
    
	auto playItem = MenuItemImage::create(
                                           "play_btn_up.png",
                                           "play_btn_down.png",
                                           CC_CALLBACK_1(MenuScene::GoToGameScene, this));
    
	playItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // create menu, it's an autorelease object
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, kMiddleground);

    return true;
}

//void MenuScene::GoToGameScene( float dt )
//{
//    auto scene = GameLayer::createScene();
//    
//    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5f, scene ) );//TRANSITION_TIME = 0.5
//}

void MenuScene::GoToGameScene(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    //Director::getInstance()->end();
    auto scene = GameLayer::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5f, scene ) );//TRANSITION_TIME = 0.5

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

