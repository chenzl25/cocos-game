#include "MoneyGenerator.h"

USING_NS_CC;


MoneyGenerator * MoneyGenerator::_instance = NULL;
MoneyGenerator * MoneyGenerator::getInstance() {
	if (_instance == NULL) {
		_instance = new MoneyGenerator();
	}
	return _instance;
}

MoneyGenerator::~MoneyGenerator() {
	CCLOG("destrocut %d", Money.size());
	for (int i = 0; i < Money.size();) {
		Money.at(i)->removeFromParentAndCleanup(true);
		Money.erase(i);
	}
	_instance = NULL;
}

MoneyGenerator::MoneyGenerator() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

//生成一个金币，加入到vector中
void MoneyGenerator::generMoney(float x, float y) {
	Sprite* m;
	PhysicsBody* mb;
	MoveBy* mAction; 
	m = Sprite::create("money.png");
	m->setPosition(x, y);
	mAction = MoveBy::create(MONEY_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0));
	
	m->setTag(MONEY_TAG);

	mb = PhysicsBody::createCircle(m->getContentSize().width / 2);
	mb->setDynamic(false);
	mb->setCategoryBitmask(0x03);
	mb->setCollisionBitmask(0x00);
	mb->setContactTestBitmask(0x01);
	mb->setRotationEnable(false);
	mb->setAngularVelocityLimit(0);

	m->setPhysicsBody(mb);

	m->runAction(mAction);

	Money.pushBack(m);
}

//随机生成五种不同类型的金币组合图形
Vector<Node*> MoneyGenerator::GenerateMoney() {
	Vector<Node*> temp;
	if (Money.size() > 0) return temp;
	float MoneyWith = 45;
	float MoneyHeight = 45;
	int type = random() % 5;
	if (type == 0) {
		/*
		****
		****
		****
		****
		*/
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				generMoney(visibleSize.width + MoneyWith * (3 - i), visibleSize.height / 2 - MoneyHeight * (2 - j));
			}
		}
	} else if (type == 1) {
		/* 
		  ****
		     ****
			   ****
			     ****
			*/
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				generMoney(visibleSize.width + MoneyWith * (3 - i + 3 - j), visibleSize.height / 2 - MoneyHeight * (2 - j));
			}
		}
	} else if (type == 2) {
		/*
		      ****
		    ****
		  ****
		****
		*/
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				generMoney(visibleSize.width + MoneyWith * (3 - i + j), visibleSize.height / 2 - MoneyHeight * (2 - j));
			}
		}
	} else if (type == 3) {
		/*
		      ****
		    **    **
		  **       **
		**          **
	    */
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				generMoney(visibleSize.width + MoneyWith * (1 - i + 3 - j), visibleSize.height / 2 - MoneyHeight * (2 - j));
			}
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				generMoney(visibleSize.width + MoneyWith * (5 + 1 - i + j), visibleSize.height / 2 - MoneyHeight * (2 - j));
			}
		}
	} else {
		/*
		**      **
		 **    **
		  **  **
		   ****
		*/
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				generMoney(visibleSize.width + MoneyWith * (1 - i + j), visibleSize.height / 2 - MoneyHeight * (2 - j));
			}
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				generMoney(visibleSize.width + MoneyWith * (5 + 1 - i + 3 - j), visibleSize.height / 2 - MoneyHeight * (2 - j));
			}
		}
	}
	return Money;
}

//大鸟捡到钱，金币消失
void MoneyGenerator::obtainMoney(Node* mon) {
	mon->removeFromParentAndCleanup(true);
	Money.eraseObject(mon);
}

//判断金币组合vector是否到了屏幕边缘，是的话就消失
void MoneyGenerator::removeMoney() {
	for (int i = 0; i < Money.size();) {
		if (Money.at(i)->getPosition().x < 20) {
			Money.at(i)->removeFromParentAndCleanup(true);
			Money.erase(i);
		} else {
			++i;
		}
	}
}
