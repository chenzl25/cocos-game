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

	auto flappyBody = PhysicsBody::createCircle(15);
	//flappyBody->setDynamic(false);
	flappyBody->setCategoryBitmask(0x01);
	flappyBody->setCollisionBitmask(0x03);
	flappyBody->setContactTestBitmask(0x03);
	flappyBody->setRotationEnable(false);
	flappyBody->setAngularVelocityLimit(0);

	setAnchorPoint(Vec2(1, 1));
	setPhysicsBody(flappyBody);

	runAction(Animate::create(AnimationCache::getInstance()->getAnimation("flying_bird")));

	isFalling = true;
	speed = 0;
	accelerate = -0.0002;

	return true;
}

void Player::Fall()
{
	speed += accelerate;

	setPositionX(visibleSize.width / 2 + origin.x);
	setPositionY(getPositionY() + (speed * visibleSize.height));
}

void Player::Fly()
{
	speed = 0.005;
	getPhysicsBody()->setVelocity(Vec2(0, 250));
}
