#include "GameLayer.h"
#include <random>

USING_NS_CC;

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameLayer::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(_origin.x + _visibleSize.width - closeItem->getContentSize().width/2 ,
                                _origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, kMiddleground);

    /////////////////////////////

	_running = false;
	_leftSpriteMoving = false;
	_centerSpriteMoving = false;
	_rightSpriteMoving = false;
	_leftSpriteFalling = false;
	_centerSpriteFalling = false;
	_rightSpriteFalling = false;
	
	
	this->createGameSprites();
	this->createPools();
	this->createActions();

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(GameLayer::update));

    return true;
}


void GameLayer::createGameSprites(void) {
	auto bgSprite = Sprite::create("background-8.png");
    bgSprite->setPosition(Vec2(_visibleSize.width/2 + _origin.x, _visibleSize.height/2 + _origin.y));
    this->addChild(bgSprite, kBackground);

	_scissorsSprite = Sprite::create("two_fingers-50.png");
	_scissorsSprite->setVisible(false);
    this->addChild(_scissorsSprite, kMiddleground, kSpriteScissors);

	_rockSprite = Sprite::create("no_fingers-50.png");
	_rockSprite->setVisible(false);
    this->addChild(_rockSprite, kMiddleground, kSpriteRock);

	_paperSprite = Sprite::create("whole_hand-50.png");
	_paperSprite->setVisible(false);
    this->addChild(_paperSprite, kMiddleground, kSpritePaper);

	_scoreLabel = Label::createWithTTF("0", "fonts/Oval Single.otf", 80, Size::ZERO, TextHAlignment::LEFT);
	_scoreLabel->setAnchorPoint(Vec2(0,1));
	_scoreLabel->setPosition(Vec2(10,_origin.y + _visibleSize.height - 10));
	this->addChild(_scoreLabel,kMiddleground);

	_lifeLabel = Label::createWithTTF("1", "fonts/Oval Single.otf", 80, Size::ZERO, TextHAlignment::RIGHT);
	_lifeLabel->setAnchorPoint(Vec2(1,1));
	_lifeLabel->setPosition(Vec2(_origin.x + _visibleSize.width - 10,_origin.y + _visibleSize.height - 10));
	this->addChild(_lifeLabel,kMiddleground);
}

void GameLayer::createPools(void) {
	Sprite * sprite;
	int i;

	//create scissors pool
	_scissorsPool = __Array::createWithCapacity(50);
	_scissorsPool->retain();
	_scissorsPoolIndex = 0;
	for(i = 0; i < 50; i++) {
		sprite = Sprite::create("two_fingers-50.png");
		sprite->setVisible(false);
		this->addChild(sprite, kMiddleground, kSpriteScissors);
		_scissorsPool->addObject(sprite);
	}


	//create rock pool
	_rockPool = __Array::createWithCapacity(50);
	_rockPool->retain();
	_rockPoolIndex = 0;
	for(i = 0; i < 50; i++) {
		sprite = Sprite::create("no_fingers-50.png");
		sprite->setVisible(false);
		this->addChild(sprite, kMiddleground, kSpriteRock);
		_rockPool->addObject(sprite);
	}

	//create scissors pool
	_paperPool = __Array::createWithCapacity(50);
	_paperPool->retain();
	_paperPoolIndex = 0;
	for(i = 0; i < 50; i++) {
		sprite = Sprite::create("whole_hand-50.png");
		sprite->setVisible(false);
		this->addChild(sprite, kMiddleground, kSpritePaper);
		_paperPool->addObject(sprite);
	}


	_fallingLeft = __Array::createWithCapacity(20);
	_fallingLeft->retain();

	_fallingCenter = __Array::createWithCapacity(20);
	_fallingCenter->retain();

	_fallingRight = __Array::createWithCapacity(20);
	_fallingRight->retain();
}

void GameLayer::createActions(void) {
	
	//_stepDown = MoveBy::create(10, Vec2(0, -_visibleSize.height - 200));
	_stepDown = Sequence::create(
			MoveBy::create(5, Vec2(0, -_visibleSize.height - 200)),
			CallFuncN::create(CC_CALLBACK_1(GameLayer::fallDownDone,this)),
			nullptr);
	_stepDown->retain();

	_fireLeft = Sequence::create(
			MoveTo::create(0.1f, Vec2(_visibleSize.width/6, _visibleSize.height)),
			CallFunc::create(CC_CALLBACK_0(GameLayer::fireLeftSpriteDone,this)),
			MoveTo::create(0.1f, Vec2(_visibleSize.width/6, 0)),
			nullptr);
	_fireLeft->retain();

	_fireCenter = Sequence::create(
			MoveTo::create(0.1f, Vec2(_visibleSize.width/6*3, _visibleSize.height)),
			CallFunc::create(CC_CALLBACK_0(GameLayer::fireCenterSpriteDone,this)),
			MoveTo::create(0.1f, Vec2(_visibleSize.width/6*3, 0)),
			nullptr);
	_fireCenter->retain();

	_fireRight = Sequence::create(
			MoveTo::create(0.1f, Vec2(_visibleSize.width/6*5, _visibleSize.height)),
			CallFunc::create(CC_CALLBACK_0(GameLayer::fireRightSpriteDone,this)),
			MoveTo::create(0.1f, Vec2(_visibleSize.width/6*5, 0)),
			nullptr);
	_fireRight->retain();

	_comeBackLeft = Sequence::create(
			CallFunc::create(CC_CALLBACK_0(GameLayer::fireLeftSpriteDone,this)),
			MoveTo::create(0.3f, Vec2(_visibleSize.width/6, 0)),
			nullptr);
	_comeBackLeft->retain();

	_comeBackCenter = Sequence::create(
			CallFunc::create(CC_CALLBACK_0(GameLayer::fireCenterSpriteDone,this)),
			MoveTo::create(0.3f, Vec2(_visibleSize.width/6*3, 0)),
			nullptr);
	_comeBackCenter->retain();

	_comeBackRight = Sequence::create(
			CallFunc::create(CC_CALLBACK_0(GameLayer::fireRightSpriteDone,this)),
			MoveTo::create(0.3f, Vec2(_visibleSize.width/6*5, 0)),
			nullptr);
	_comeBackRight->retain();



	_fallBackLeft = Sequence::create(
			Spawn::create(
				MoveTo::create(0.5f, Vec2(_visibleSize.width/6, 0)),
				RotateBy::create(1, 360),
				nullptr),
			CallFunc::create(CC_CALLBACK_0(GameLayer::fireLeftSpriteDone,this)),
			nullptr);
	_fallBackLeft->retain();

	_fallBackCenter = Sequence::create(
			Spawn::create(
				MoveTo::create(0.5f, Vec2(_visibleSize.width/6*3, 0)),
				RotateBy::create(1, 360),
				nullptr),
			CallFunc::create(CC_CALLBACK_0(GameLayer::fireCenterSpriteDone,this)),
			nullptr);
	_fallBackCenter->retain();

	_fallBackRight = Sequence::create(
			Spawn::create(
				MoveTo::create(0.5f, Vec2(_visibleSize.width/6*5, 0)),
				RotateBy::create(1, 360),
				nullptr),
			CallFunc::create(CC_CALLBACK_0(GameLayer::fireRightSpriteDone,this)),
			nullptr);
	_fallBackRight->retain();

	auto breakDownBegin = Sequence::create(
			ScaleBy::create(0.05f, 1.2f),
			Spawn::create(
				ScaleBy::create(0.15f, 0.5f),
				FadeOut::create(0.15f),
				nullptr),
			nullptr);

	auto breakDownEnd = breakDownBegin->reverse();

	_breakDown = Sequence::create(
			breakDownBegin,
			CallFuncN::create(CC_CALLBACK_1(GameLayer::breakDownDone, this)),
			breakDownEnd,
			nullptr);
	_breakDown->retain();

	_stayUp = Sequence::create(
			MoveBy::create(0.025f, Vec2(0,20)),
			MoveBy::create(0.025f, Vec2(0,-40)),
			MoveBy::create(0.025f, Vec2(0,30)),
			MoveBy::create(0.025f, Vec2(0,-20)),
			nullptr
		);
	_stayUp->retain();
}

void GameLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	if(!_running) {
		if(!_leftSpriteMoving && !_leftSpriteFalling &&
			!_centerSpriteMoving && !_centerSpriteFalling &&
			!_rightSpriteMoving && !_rightSpriteFalling) {
			GameLayer::resetGame();
		}
		return;
	}

	auto touch = touches[0];
	if(touch) {
		auto tap = touch->getLocationInView();
	
		if(tap.x <= _visibleSize.width/3) {
			if(_leftSpriteMoving==false && _leftSpriteFalling==false) {
				GameLayer::fireLeftSprite();
			}			
		} else if(tap.x <= _visibleSize.width/3*2) {
			if(_centerSpriteMoving==false && _centerSpriteFalling==false) {
				GameLayer::fireCenterSprite();
			}
			
		} else if(tap.x <= _visibleSize.width) {
			if(_rightSpriteMoving==false && _rightSpriteFalling==false) {
				GameLayer::fireRightSprite();
			}
			
		}
	}
	
}
void GameLayer::update(float dt) {
	if(!_running) {
		return;
	}

	_addBlocksTimer += dt;
	if(_addBlocksTimer > _addBlocksInterval) {
		_addBlocksTimer = 0;
		GameLayer::addMoreFallingBlocks();
	}

	float diffy;
	if(_fallingLeft->count() > 0) {
		Sprite * sprite = (Sprite *) _fallingLeft->getObjectAtIndex(0);
		diffy = sprite->getPositionY() - _leftSprite->getPositionY();
		if(diffy <= sprite->getBoundingBox().size.height && _leftSpriteMoving == true && _leftSpriteFalling == false) {
			if(sprite->getTag() == GameLayer::getTargetTypeByType(_leftSprite->getTag())) {
				_leftSprite->stopAllActions();
				_leftSprite->runAction((Action *)_comeBackLeft->clone());
				GameLayer::destroyBlockRow();
				GameLayer::updateScore();
			} else {				
				_leftSprite->stopAllActions();
				_leftSpriteFalling = true;
				//sprite->runAction((Action *)_stayUp->clone());
				_leftSprite->runAction((Action *)_fallBackLeft->clone());				
				GameLayer::updateLife();
			}			
		}
	}
	if(_fallingCenter->count() > 0) {
		Sprite * sprite = (Sprite *) _fallingCenter->getObjectAtIndex(0);
		diffy = sprite->getPositionY() - _centerSprite->getPositionY();
		if(diffy <= sprite->getBoundingBox().size.height && _centerSpriteMoving == true && _centerSpriteFalling == false) {
			if(sprite->getTag() == GameLayer::getTargetTypeByType(_centerSprite->getTag())) {
				_centerSprite->stopAllActions();
				_centerSprite->runAction((Action *)_comeBackCenter->clone());
				GameLayer::destroyBlockRow();
				GameLayer::updateScore();
			} else {
				_centerSprite->stopAllActions();
				_centerSpriteFalling = true;
				//sprite->runAction((Action *)_stayUp->clone());
				_centerSprite->runAction((Action *)_fallBackCenter->clone());				
				GameLayer::updateLife();
			}			
		}
	}
	if(_fallingRight->count() > 0) {
		Sprite * sprite = (Sprite *) _fallingRight->getObjectAtIndex(0);
		diffy = sprite->getPositionY() - _rightSprite->getPositionY();
		if(diffy <= sprite->getBoundingBox().size.height && _rightSpriteMoving == true && _rightSpriteFalling == false) {
			if(sprite->getTag() == GameLayer::getTargetTypeByType(_rightSprite->getTag())) {
				_rightSprite->stopAllActions();
				_rightSprite->runAction((Action *)_comeBackRight->clone());
				GameLayer::destroyBlockRow();
				GameLayer::updateScore();
			} else {
				_rightSprite->stopAllActions();
				_rightSpriteFalling = true;
				//sprite->runAction((Action *)_stayUp->clone());
				_rightSprite->runAction((Action *)_fallBackRight->clone());				
				GameLayer::updateLife();
			}			
		}
	}

}

void GameLayer::addMoreFallingBlocks(void) {
	if(_fallingCenter->count() + _fallingLeft->count() + _fallingRight->count() > 45) {
		return;
	}

	std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 2); // define the range

	int correctLaneNumber, leftBlockType, centerBlockType, rightBlockType;
	Sprite * rightBlockItem, * leftBlockItem, * centerBlockItem;
	int i = 1;

	correctLaneNumber = distr(eng);
	if(correctLaneNumber == kLaneLeft) {
		leftBlockType = GameLayer::getTargetTypeByType(_leftSprite->getTag());
		centerBlockType = distr(eng);
		rightBlockType = distr(eng);
	} else if(correctLaneNumber == kLaneCenter) {
		leftBlockType = distr(eng);
		centerBlockType = GameLayer::getTargetTypeByType(_centerSprite->getTag());
		rightBlockType = distr(eng);
	} else {
		leftBlockType = distr(eng);
		centerBlockType = distr(eng);
		rightBlockType = GameLayer::getTargetTypeByType(_rightSprite->getTag());
	}

	leftBlockItem = GameLayer::makeBlockByType(leftBlockType);
	leftBlockItem->setPosition(Vec2(_visibleSize.width/6, _visibleSize.height + leftBlockItem->getContentSize().height));
	
	centerBlockItem = GameLayer::makeBlockByType(centerBlockType);
	centerBlockItem->setPosition(Vec2(_visibleSize.width/6*3, _visibleSize.height + centerBlockItem->getContentSize().height));
	
	rightBlockItem = GameLayer::makeBlockByType(rightBlockType);
	rightBlockItem->setPosition(Vec2(_visibleSize.width/6*5, _visibleSize.height + rightBlockItem->getContentSize().height));
	
	leftBlockItem->stopAllActions();
	centerBlockItem->stopAllActions();
	rightBlockItem->stopAllActions();

	leftBlockItem->setVisible(true);
	centerBlockItem->setVisible(true);
	rightBlockItem->setVisible(true);

	leftBlockItem->runAction((Action *)_stepDown->clone());
	centerBlockItem->runAction((Action *)_stepDown->clone());
	rightBlockItem->runAction((Action *)_stepDown->clone());

	_fallingLeft->addObject(leftBlockItem);
	_fallingCenter->addObject(centerBlockItem);
	_fallingRight->addObject(rightBlockItem);
}

Sprite * GameLayer::makeBlockByType(int type) {
	Sprite* returnBlock;
	if(type == kSpriteScissors) {		
		returnBlock = (Sprite *) _scissorsPool->getObjectAtIndex(_scissorsPoolIndex);
		_scissorsPoolIndex++;
		if(_scissorsPoolIndex == _scissorsPool->count()) {
			_scissorsPoolIndex = 0;
		}
	} else if(type == kSpriteRock) {
		returnBlock = (Sprite *) _rockPool->getObjectAtIndex(_rockPoolIndex);
		_rockPoolIndex++;
		if(_rockPoolIndex == _rockPool->count()) {
			_rockPoolIndex = 0;
		}
	} else {
		returnBlock = (Sprite *) _paperPool->getObjectAtIndex(_paperPoolIndex);
		_paperPoolIndex++;
		if(_paperPoolIndex == _paperPool->count()) {
			_paperPoolIndex = 0;
		}
	}
	return returnBlock;
}

Sprite * GameLayer::makeSpriteByType(int type) {
	if(type == kSpriteScissors){
		return _scissorsSprite;
	} else if(type == kSpriteRock) {
		return _rockSprite;
	} else {
		return _paperSprite;
	}
}

void GameLayer::updateScore(void) {
	_score++;
	char score_buffer[10];	
	sprintf(score_buffer,"%i", _score);    
	_scoreLabel->setString(score_buffer);
}

void GameLayer::updateLife(void) {
	_life--;
	char life_buffer[10];	
	sprintf(life_buffer,"%i", _life);    
	_lifeLabel->setString(life_buffer);
	if(_life <= 0) {
		GameLayer::stopGame();
	}
}

int GameLayer::getTargetTypeByType(int type) {
	int returnType;
	if(type == kSpriteScissors) {
		returnType = kSpritePaper;
	}
	else if(type == kSpriteRock) {
		returnType = kSpriteScissors;
	} else {
		returnType = kSpriteRock;
	}
	return returnType;
}

void GameLayer::resetGame(void) {

	_score = -1;
	GameLayer::updateScore();
	_life = 1;
	GameLayer::updateLife();

	_addBlocksTimer = 0;
	_addBlocksInterval = 1;

	std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 2); // define the range

	int leftSpriteTypeNumber, centerSpriteTypeNumber, rightSpriteTypeNumber;
	leftSpriteTypeNumber = distr(eng);
	do {
		centerSpriteTypeNumber = distr(eng);
	} while(centerSpriteTypeNumber == leftSpriteTypeNumber);
	do {
		rightSpriteTypeNumber = distr(eng);
	} while(rightSpriteTypeNumber == centerSpriteTypeNumber || rightSpriteTypeNumber == leftSpriteTypeNumber);

	_leftSprite = GameLayer::makeSpriteByType(leftSpriteTypeNumber);
	_centerSprite = GameLayer::makeSpriteByType(centerSpriteTypeNumber);
	_rightSprite = GameLayer::makeSpriteByType(rightSpriteTypeNumber);

	_leftSprite->setPosition(Vec2(_origin.x + _visibleSize.width/6, _origin.y));
    _centerSprite->setPosition(Vec2(_origin.x + _visibleSize.width/6*3, _origin.y));
    _rightSprite->setPosition(Vec2(_origin.x + _visibleSize.width/6*5, _origin.y));

	_leftSprite->setVisible(true);
	_centerSprite->setVisible(true);
	_rightSprite->setVisible(true);

	int i, count;
	Sprite * sprite;
	count = _fallingLeft->count();
	for(i = count-1; i >= 0; i--) {
		sprite = (Sprite *) _fallingLeft->getObjectAtIndex(i);
		sprite->setVisible(false);
		_fallingLeft->removeObjectAtIndex(i);
	}

	for(i = count-1; i >= 0; i--) {
		sprite = (Sprite *) _fallingCenter->getObjectAtIndex(i);
		sprite->setVisible(false);
		_fallingCenter->removeObjectAtIndex(i);
	}

	for(i = count-1; i >= 0; i--) {
		sprite = (Sprite *) _fallingRight->getObjectAtIndex(i);
		sprite->setVisible(false);
		_fallingRight->removeObjectAtIndex(i);
	}

	_running = true;
}

void GameLayer::stopGame(void) {
	_running = false;

	int i, count;
	Sprite * sprite;
	count = _fallingLeft->count();
	for(i = count-1; i >= 0; i--) {
		sprite = (Sprite *) _fallingLeft->getObjectAtIndex(i);
		sprite->stopAllActions();		
	}

	for(i = count-1; i >= 0; i--) {
		sprite = (Sprite *) _fallingCenter->getObjectAtIndex(i);
		sprite->stopAllActions();		
	}

	for(i = count-1; i >= 0; i--) {
		sprite = (Sprite *) _fallingRight->getObjectAtIndex(i);
		sprite->stopAllActions();		
	}
}

void GameLayer::fallDownDone(cocos2d::Node *pSender) {
	GameLayer::stopGame();
}

void GameLayer::breakDownDone(cocos2d::Node *pSender) {
	pSender->setVisible(false);
}

void GameLayer::fireLeftSprite(void) {
	_leftSpriteMoving = true;
	_leftSprite->stopAllActions();
	_leftSprite->runAction((Action * )_fireLeft->clone());
}

void GameLayer::fireCenterSprite(void) {
	_centerSpriteMoving = true;
	_centerSprite->stopAllActions();
	_centerSprite->runAction((Action * )_fireCenter->clone());
}

void GameLayer::fireRightSprite(void) {
	_rightSpriteMoving = true;
	_rightSprite->stopAllActions();
	_rightSprite->runAction((Action * )_fireRight->clone());
}

void GameLayer::fireLeftSpriteDone(void) {
	_leftSpriteMoving = false;
	_leftSpriteFalling = false;
}

void GameLayer::fireCenterSpriteDone(void) {
	_centerSpriteMoving = false;
	_centerSpriteFalling = false;
}

void GameLayer::fireRightSpriteDone(void) {
	_rightSpriteMoving = false;
	_rightSpriteFalling = false;
}

void GameLayer::destroyBlockRow() {
	Sprite * leftBlockItem, * centerBlockItem, * rightBlockItem;

	leftBlockItem = (Sprite *)_fallingLeft->getObjectAtIndex(0);
	centerBlockItem = (Sprite *)_fallingCenter->getObjectAtIndex(0);
	rightBlockItem = (Sprite *)_fallingRight->getObjectAtIndex(0);

	leftBlockItem->stopAllActions();
	centerBlockItem->stopAllActions();
	rightBlockItem->stopAllActions();

	leftBlockItem->runAction((Action *)_breakDown->clone());
	centerBlockItem->runAction((Action *)_breakDown->clone());
	rightBlockItem->runAction((Action *)_breakDown->clone());

	_fallingLeft->removeObjectAtIndex(0);
	_fallingCenter->removeObjectAtIndex(0);
	_fallingRight->removeObjectAtIndex(0);
}

void GameLayer::menuCloseCallback(Ref* pSender)
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
