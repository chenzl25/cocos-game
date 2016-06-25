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

	auto flappyBody = PhysicsBody::createCircle(this->getContentSize().width / 2);
	//flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBody->setContactTestBitmask(true);

	Sprite::setPhysicsBody(flappyBody);

	Animation* an = Animation::create();
	an->addSpriteFrameWithFileName("bird_hero.png");
	an->addSpriteFrameWithFileName("bird_hero2.png");
	an->addSpriteFrameWithFileName("bird_hero3.png");
	an->setDelayPerUnit(0.5f / 3.0f);
	an->setLoops(-1);
	Animate* anim = Animate::create(an);
	runAction(anim);
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
}
