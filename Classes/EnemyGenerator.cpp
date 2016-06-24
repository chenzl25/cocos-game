
#include "EnemyGenerator.h"
#include "Definitions.h"

USING_NS_CC;


EnemyGenerator * EnemyGenerator::_instance = NULL;
EnemyGenerator * EnemyGenerator::getInstance() {
	if (_instance == NULL) {
		_instance = new EnemyGenerator();
	}
	return _instance;
}

EnemyGenerator::EnemyGenerator()
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
}

Sprite * EnemyGenerator::GenerateEnemy()
{
    CCLOG( "SPAWN MONSTER" );
    
	Sprite* m;
	PhysicsBody* mb;
	MoveBy* mAction;
	int type = random()%3; // 0 云 1 山 2 鸟
	if(type == 0) {
		m = Sprite::create("cloud.png");
		m->setPosition(visibleSize.width + m->getContentSize().width, visibleSize.height-50- random() % 120);
		double rand_size = (random() % 10 + 3)/3;
		m->setScale(rand_size);
		double rand_speed = 2 / (random() % 2 + 2);
		mAction = MoveBy::create(rand_speed* CLOUD_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
	} else if(type == 1) {
		m = Sprite::create("mount.png");
		m->setPosition(visibleSize.width + m->getContentSize().width, 100);
		double rand_size = (random() % 27 + 15) / 3;
		m->setScale(rand_size);
		mAction = MoveBy::create( MOUNT_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
	} else if(type == 2) {
		m = Sprite::create("mbird.png");
		m->setPosition(visibleSize.width+m->getContentSize().width, visibleSize.height -150 - random() % 150);
		int rand_size = random() % 3 + 1;
		m->setScale(rand_size);
		double rand_speed = 2 / (random() % 3 + 2);
		mAction = MoveBy::create(rand_speed* MBIRD_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
	}

	m->setTag(ENEMY_TAG);

	mb = PhysicsBody::createBox(m->getContentSize());
	mb->setDynamic(false);
	//mb->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
	mb->setContactTestBitmask(true);

	m->setPhysicsBody(mb);

	m->runAction(mAction);

	enemys.pushBack(m);

	return m;

}

void EnemyGenerator::removeEnemys() {
	for (int i = 0; i < enemys.size();) {
		if (enemys.at(i)->getPosition().x < 20) {
			enemys.at(i)->removeFromParentAndCleanup(true);
			enemys.erase(i);
		}
		else {
			++i;
		}
	}
}