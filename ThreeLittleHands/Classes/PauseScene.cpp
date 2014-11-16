#include "PauseScene.h"
#include "GameLayer.h"
#include "MenuScene.h"
//#include "LoadingScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* PauseScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PauseScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
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

	/*auto backgroundSprite = Sprite::create( "background_menu_continous.png" );
    backgroundSprite->setPosition( Vec2( origin.x, visibleSize.height / 2 + origin.y) );    
	backgroundSprite->setAnchorPoint(Vec2(0,0.5));
    this->addChild( backgroundSprite , 1);

	auto background2Sprite = Sprite::create( "background_menu_continous.png" );
    background2Sprite->setPosition( Vec2( backgroundSprite->getContentSize().width + origin.x, visibleSize.height / 2 + origin.y) );    
	background2Sprite->setAnchorPoint(Vec2(0,0.5));
    this->addChild( background2Sprite , 1);
	
	backgroundSprite->runAction(RepeatForever::create(
		Sequence::create(
			MoveBy::create(10,Vec2(-backgroundSprite->getContentSize().width,0)),
			MoveBy::create(0,Vec2(backgroundSprite->getContentSize().width *2,0)),
			MoveBy::create(10,Vec2(-backgroundSprite->getContentSize().width,0)),
			nullptr)
		));
	background2Sprite->runAction(RepeatForever::create(
		Sequence::create(
			MoveBy::create(10,Vec2(-background2Sprite->getContentSize().width,0)),
			MoveBy::create(10,Vec2(-background2Sprite->getContentSize().width,0)),
			MoveBy::create(0,Vec2(background2Sprite->getContentSize().width *2,0)),
			nullptr)
		));

	auto titleSprite = Sprite::create( "title.png" );
    titleSprite->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 5*4 + origin.y) );    
    this->addChild( titleSprite , 2);*/

	//auto playBtnSprite = Sprite::create( "play_btn_up.png" );
 //   playBtnSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );    
 //   this->addChild( playBtnSprite , 1);
    
	//auto playItem = MenuItemImage::create(
 //                                          "play_btn_up.png",
 //                                          "play_btn_down.png",
 //                                          CC_CALLBACK_1(GameOverScene::goToLoadingScene, this));
 //   
	//playItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//auto exitItem = MenuItemImage::create(
 //                                          "exit_btn_up.png",
 //                                          "exit_btn_down.png",
 //                                          CC_CALLBACK_1(GameOverScene::exitGame, this));
 //   
	//exitItem->setPosition(Vec2(origin.x + visibleSize.width - exitItem->getContentSize().width/2 - 5,
 //                               origin.y + exitItem->getContentSize().height/2 + 5));


	//auto settingItem = MenuItemImage::create(
 //                                          "setting_btn_up.png",
 //                                          "setting_btn_down.png",
 //                                          CC_CALLBACK_1(GameOverScene::openSetting, this));
 //   
	//settingItem->setPosition(Vec2(origin.x + visibleSize.width - settingItem->getContentSize().width/2 - 125,
 //                               origin.y + settingItem->getContentSize().height/2 + 5));

	//auto infoItem = MenuItemImage::create(
 //                                          "info_btn_up.png",
 //                                          "info_btn_down.png",
 //                                          CC_CALLBACK_1(GameOverScene::openInfo, this));
 //   
	//infoItem->setPosition(Vec2(origin.x + visibleSize.width - infoItem->getContentSize().width/2 - 245,
 //                               origin.y + infoItem->getContentSize().height/2 + 5));

 //   // create menu, it's an autorelease object
 //   auto menu = Menu::create(playItem, exitItem, settingItem, infoItem, NULL);
 //   menu->setPosition(Vec2::ZERO);
 //   this->addChild(menu, 2);	

	////_gameScene = GameLayer::createScene();

	auto backgroundSprite = Sprite::create("game_over_background.png");
	backgroundSprite->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
	this->addChild(backgroundSprite, 0);

	auto playItem = MenuItemImage::create(
						"pause_play_btn_up.png",
						"pause_play_btn_down.png",
						CC_CALLBACK_1(PauseScene::replay, this));
    
	playItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + playItem->getContentSize().height));

	auto menuItem = MenuItemImage::create(
					"pause_menu_btn_up.png",
					"pause_menu_btn_down.png",
					CC_CALLBACK_1(PauseScene::goToMenu, this));
    
	menuItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto exitItem = MenuItemImage::create(
					"pause_exit_btn_up.png",
					"pause_exit_btn_down.png",
					CC_CALLBACK_1(PauseScene::quit, this));
    
	exitItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - exitItem->getContentSize().height));

	    // create menu, it's an autorelease object
    auto menu = Menu::create(playItem, menuItem, exitItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);	

	auto pauseSprite = Sprite::create( "Pause.png" );
    pauseSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + playItem->getContentSize().height * 2));
	//backgroundSprite->setAnchorPoint(Vec2(0,0.5));
    this->addChild( pauseSprite , 1);

    return true;
}

//void MenuScene::GoToGameScene( float dt )
//{
//    auto scene = GameLayer::createScene();
//    
//    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5f, scene ) );//TRANSITION_TIME = 0.5
//}

//void GameOverScene::goToLoadingScene(Ref* pSender)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    //Director::getInstance()->end();
//    auto scene = GameOverScene::createScene();
//    
//    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5f, scene ) );//TRANSITION_TIME = 0.5
//	//Director::getInstance( )->replaceScene( TransitionFade::create( 0.5f, _gameScene ) );//TRANSITION_TIME = 0.5
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//}
//
//void GameOverScene::exitGame(Ref* pSender)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//}
//
//void GameOverScene::openSetting(Ref* pSender) {
//
//}
void PauseScene::replay(Ref* pSender) {
	SimpleAudioEngine::getInstance()->playEffect("play.wav");
	//Director::getInstance( )->popScene( TransitionMoveInT::create( 0.2f, gameOverScene ) );
	Director::getInstance()->popScene();
	
	//auto scene = (GameLayer *) Director::getInstance()->getRunningScene();
	//scene->resume();
	//GameLayer::replay();
}

void PauseScene::quit(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void PauseScene::goToMenu(Ref* pSender) {
	SimpleAudioEngine::getInstance()->playEffect("play.wav");
	auto scene = MenuScene::createScene();    
	Director::getInstance()->popToRootScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5f, scene ) );//TRANSITION_TIME = 0.5
	
}