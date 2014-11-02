#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

enum {
	kBackground = 1,
	kMiddleground,
	kForeground
};

enum {
	kSpriteScissors,
	kSpriteRock,
	kSpritePaper
};

enum {
	kLaneLeft,
	kLaneCenter,
	kLaneRight
};

class GameLayer : public cocos2d::Layer
{
private:
	cocos2d::Size _visibleSize;
	cocos2d::Vec2 _origin;

	float _addBlocksInterval;
	float _addBlocksTimer;

	int _score;
	int _life;
	cocos2d::Label * _scoreLabel;
	cocos2d::Label * _lifeLabel;

	cocos2d::Sprite * _scissorsSprite;
	cocos2d::Sprite * _rockSprite;
	cocos2d::Sprite * _paperSprite;

	cocos2d::Sprite * _leftSprite;
	cocos2d::Sprite * _centerSprite;
	cocos2d::Sprite * _rightSprite;
	
	cocos2d::__Array * _scissorsPool;
	cocos2d::__Array * _rockPool;
	cocos2d::__Array * _paperPool;
	int _scissorsPoolIndex;
	int _rockPoolIndex;
	int _paperPoolIndex;

	bool _leftSpriteMoving;
	bool _centerSpriteMoving;
	bool _rightSpriteMoving;
	bool _leftSpriteFalling;
	bool _centerSpriteFalling;
	bool _rightSpriteFalling;


	cocos2d::__Array * _fallingLeft;
	cocos2d::__Array * _fallingCenter;
	cocos2d::__Array * _fallingRight;

	cocos2d::Action * _stepDown;
	//cocos2d::Action * _fire;
	cocos2d::Action * _fireLeft;
	cocos2d::Action * _fireCenter;
	cocos2d::Action * _fireRight;
	//cocos2d::Action * _comeBack;
	cocos2d::Action * _comeBackLeft;
	cocos2d::Action * _comeBackCenter;
	cocos2d::Action * _comeBackRight;
	//cocos2d::Action * _fallBack;
	cocos2d::Action * _fallBackLeft;
	cocos2d::Action * _fallBackCenter;
	cocos2d::Action * _fallBackRight;

	cocos2d::Action * _beDestroyed;



	bool _running;
	int _lineHeight;

	void resetGame(void);
	void stopGame(void);
	void createGameSprites(void);
	void createPools(void);
	void createActions(void);

	void addMoreFallingBlocks(void);
	cocos2d::Sprite * makeBlockByType(int type);
	cocos2d::Sprite * makeSpriteByType(int type);
	int getTargetTypeByType(int type);
	void destroyBlockRow(void);
	void updateScore(void);
	void updateLife(void);

	void fallDownDone(cocos2d::Node *pSender);

	void fireLeftSprite(void);
	void fireCenterSprite(void);
	void fireRightSprite(void);

	void fireLeftSpriteDone(void);
	void fireCenterSpriteDone(void);
	void fireRightSpriteDone(void);

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	virtual void update(float dt);


};

#endif // __GAME_LAYER_H__
