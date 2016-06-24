#ifndef __ENEMYGENERATOR_H__
#define __ENEMYGENERATOR_H__

#include "cocos2d.h"

USING_NS_CC;

class EnemyGenerator
{
public:
	static EnemyGenerator * _instance;
	static EnemyGenerator * getInstance();

	cocos2d::Sprite * GenerateEnemy();
	void removeEnemys();
    
private:
	EnemyGenerator();

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
	Vector<Sprite*> enemys;
};

#endif // __ENEMYGENERATOR_H__
