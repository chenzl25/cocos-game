#include "Player.h"
#include "Definitions.h"

USING_NS_CC;

bool Player::init() {
	if (!Sprite::init()) {
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	setTag(PLAYER_TAG);

	setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// 玩家的刚体
	auto flappyBody = PhysicsBody::createCircle(18);
	flappyBody->setPositionOffset(Vec2(15, 12));
	flappyBody->setRotationEnable(false);
	flappyBody->setAngularVelocityLimit(0);
	flappyBody->setMass(PLAYER_MASS);
	// bitmask
	flappyBody->setCategoryBitmask(0x05);
	flappyBody->setCollisionBitmask(0x06);
	flappyBody->setContactTestBitmask(0x02);

	setAnchorPoint(Vec2(1, 1));
	setPhysicsBody(flappyBody);

	runAction(Animate::create(AnimationCache::getInstance()->getAnimation("flying_bird")));

	// 采用物理引擎实现重力后，此变量不需要
	isFalling = true;
	speed = 0;
	accelerate = -0.0002;

	return true;
}
//大鸟往下掉，下掉过程考虑重力的作用 采用物理引擎实现重力后，此函数不需要
void Player::Fall()
{
	speed += accelerate;

	setPositionX(visibleSize.width / 2 + origin.x);
	setPositionY(getPositionY() + (speed * visibleSize.height));
}
//大鸟向上飞
void Player::Fly()
{
	speed = 0.005;  // 采用物理引擎实现重力后，此变量不需要
	getPhysicsBody()->setVelocity(Vec2(0, 400));
	//getPhysicsBody()->applyImpulse(Vec2(0, 100000));
}
