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
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

EnemyGenerator::~EnemyGenerator() {
	CCLOG("destrocut enemy %d", enemys.size());
	for (int i = 0; i < enemys.size();) {
		enemys.at(i)->removeFromParentAndCleanup(true);
		enemys.erase(i);
	}
	_instance = NULL;
}

Sprite * EnemyGenerator::GenerateEnemy()
{
    CCLOG( "SPAWN MONSTER" );
    
	Sprite* m;
	PhysicsBody* mb;
	Action* mAction;
	int type = random()%4; // 0 云 1 山 2 鸟 3 飞机
	if(type == 0) {
		m = Sprite::create("cloud.png");
		m->setPosition(visibleSize.width + m->getContentSize().width, visibleSize.height - random() % 50);
		double rand_size = (random() % 10 + 3)/3;
		//m->setScale(rand_size);
		double rand_speed = 2 / (random() % 2 + 2);
		mAction = MoveBy::create(rand_speed* CLOUD_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );

		Vec2 shape0[5];
		shape0[0].setPoint(-70, 0);
		shape0[1].setPoint(0, 70);
		shape0[2].setPoint(70, 0);
		shape0[3].setPoint(70, -20);
		shape0[4].setPoint(20, -20);
		Vec2 shape1[3];
		shape1[0].setPoint(-20, 0);
		shape1[1].setPoint(20, 0);
		shape1[2].setPoint(0, -80);
		mb = PhysicsBody::create();
		mb->addShape(PhysicsShapePolygon::create(shape0, 5));
		mb->addShape(PhysicsShapePolygon::create(shape1, 3));
	} else if(type == 1) {
		double rand_size = random() % 2 + 2;
		m = Sprite::create("mountain.png");
		m->setPosition(visibleSize.width + m->getContentSize().width, m->getContentSize().height*(1/rand_size)/2-20);
		m->setScale(1/rand_size);
		mAction = MoveBy::create( MOUNT_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width - m->getContentSize().width * 2, 0));

		Vec2 shape0[3];
		shape0[0].setPoint(-550, -300);
		shape0[1].setPoint(-50, 200);
		shape0[2].setPoint(450, -300);
		Vec2 shape1[3];
		shape1[0].setPoint(-420, -300);
		shape1[1].setPoint(80, 200);
		shape1[2].setPoint(580, -300);
		mb = PhysicsBody::create();
		mb->addShape(PhysicsShapePolygon::create(shape0, 3));
		mb->addShape(PhysicsShapePolygon::create(shape1, 3));
	} else if(type == 2) {
		m = Sprite::create("mbird.png");
		m->setPosition(visibleSize.width+m->getContentSize().width, random() % (int)visibleSize.height);
		double rand_speed = random() % 4 + 2;

		int rand_case = random() % 2;
		ccBezierConfig bezier;
		bezier.controlPoint_1 = Point(0, m->getPositionY());
		if (rand_case == 0) {
			bezier.controlPoint_2 = Point(visibleSize.width, m->getPositionY() + 200);
			bezier.endPosition = Point(-50, m->getPositionY() + 200);
		}
		else {
			bezier.controlPoint_2 = Point(visibleSize.width, m->getPositionY() - 200);
			bezier.endPosition = Point(-50, m->getPositionY() - 200);
		}	
		mAction = BezierTo::create(rand_speed, bezier);

		mb = PhysicsBody::createBox(m->getContentSize());
	}
	else if (type == 3) {
		m = Sprite::create("plane.png");
		m->setPosition(visibleSize.width + m->getContentSize().width, random() % (int)visibleSize.height);
		double rand_speed = 2 / (random() % 3 + 2);
		mAction = MoveBy::create(rand_speed* MBIRD_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0));

		mb = PhysicsBody::createBox(m->getContentSize());
	}

	m->setTag(ENEMY_TAG);

	mb->setDynamic(false);
	mb->setCategoryBitmask(0x03);
	mb->setCollisionBitmask(0x01);
	mb->setContactTestBitmask(0x01);

	m->setPhysicsBody(mb);

	m->runAction(mAction);

	enemys.pushBack(m);
	CCLOG("enemys %d", enemys.size());
	return m;

}

void EnemyGenerator::removeEnemys() {
	for (int i = 0; i < enemys.size();) {
		if (enemys.at(i)->getPosition().x < -enemys.at(i)->getBoundingBox().size.width/2) {
			enemys.at(i)->removeFromParentAndCleanup(true);
			enemys.erase(i);
		}
		else {
			++i;
		}
	}
	CCLOG("remove enemys %d", enemys.size());
}
