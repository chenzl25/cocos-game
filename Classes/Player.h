#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class Player : public Sprite
{
public:
	CREATE_FUNC(Player);
	virtual bool init();

    void Fall( );
    void Fly( );
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    bool isFalling;
	float speed;
	float accelerate;
    
};

#endif // __PLAYER_H__
