#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include<string>
#include "MoneyGenerator.h"
#include "SimpleAudioEngine.h"
#include "EnemyGenerator.h"
#include "Definitions.h"
#include "GameOverScene.h"
#include "Player.h"
using namespace CocosDenshion;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    void setPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };
	void preloadMusic();
	void playBgm();

	void ready(float dt);

    void newEnemy( float dt );
	void newMoney(float dt);
    
    bool onContactBegin( cocos2d::PhysicsContact &contact );
    bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event );
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
    
    void update( float dt );
    
    cocos2d::PhysicsWorld *sceneWorld;
    
	Player * player;
	Sprite * package;
    
    unsigned int score;
	int moneyCount;
	float scoreLock;
    
    cocos2d::Label *scoreLabel;
	cocos2d::Label *MoneyLabel;
	cocos2d::Label *readyLabel;

	Size visibleSize;
	Vec2 origin;
};

#endif // __GAME_SCENE_H__
