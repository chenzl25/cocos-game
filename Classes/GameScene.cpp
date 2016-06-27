#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics( );
    //scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -WORLD_GRAVITY));
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

	//添加关节
	Sprite * last_sp = NULL;
	PhysicsBody * last_bd = NULL;
	last_sp = Sprite::create();
	last_sp->setTextureRect(Rect(0, 0, 10, 10));
	last_bd = PhysicsBody::createCircle(last_sp->getContentSize().width / 2, PhysicsMaterial(1.0f, 0.0f, 0.0f));
	last_bd->setRotationEnable(false);
	last_bd->setMass(1);
	last_sp->setPhysicsBody(last_bd);
	last_sp->setPosition(layer->player->getPositionX(), layer->player->getPositionY() - 20);
	layer->addChild(last_sp);

	auto first_joint = PhysicsJointDistance::construct(layer->player->getPhysicsBody(), last_sp->getPhysicsBody(), Point::ZERO, Point::ZERO);
	layer->sceneWorld->addJoint(first_joint);

	// 循环添加关节
	Sprite * new_sp = NULL;
	PhysicsBody * new_bd = NULL;
	for (int i = 0; i < 6; i++)
	{
		new_sp = Sprite::create();
		new_sp->setTextureRect(Rect(0, 0, 10, 10));
		new_bd = PhysicsBody::createCircle(new_sp->getContentSize().width / 2, PhysicsMaterial(1.0f, 0.0f, 0.0f));
		new_bd->setRotationEnable(false);
		new_bd->setMass(1);
		new_sp->setPhysicsBody(new_bd);
		new_sp->setPosition(last_sp->getPositionX(), last_sp->getPositionY() - 10);
		layer->addChild(new_sp);

		auto joint = PhysicsJointDistance::construct(last_sp->getPhysicsBody(), new_sp->getPhysicsBody(), Point::ZERO, Point::ZERO);
		layer->sceneWorld->addJoint(joint);
		last_sp = new_sp;
	}

	auto last_joint = PhysicsJointDistance::construct(last_sp->getPhysicsBody(), layer->package->getPhysicsBody(), Point::ZERO, Point::ZERO);
	layer->sceneWorld->addJoint(last_joint);

	// 通过PhysicsJointGroove限制小鸟运动，考虑到游戏性，否决
	/*auto origin = Sprite::create("package.png");
	origin->setPosition(layer->visibleSize.width/2, layer->visibleSize.height/2);
	origin->setPhysicsBody(PhysicsBody::createCircle(10));
	origin->getPhysicsBody()->setDynamic(false);
	origin->getPhysicsBody()->setCollisionBitmask(0x00);
	origin->getPhysicsBody()->setContactTestBitmask(0x00);
	layer->addChild(origin);
	auto joint = PhysicsJointGroove::construct(origin->getPhysicsBody(), layer->player->getPhysicsBody(), Vec2(0, -layer->visibleSize.height / 2), Vec2(0, layer->visibleSize.height / 2), Vec2::ZERO);
	joint->setCollisionEnable(false);
	layer->sceneWorld->addJoint(joint);*/

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	
	//音乐
	preloadMusic();
	playBgm();

    auto backgroundSprite = Sprite::create( "bg.jpg" );
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Size size = Director::getInstance()->getWinSize();
	backgroundSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	float winw = size.width; //获取屏幕宽度
	float winh = size.height;//获取屏幕高度

	float spx = backgroundSprite->getTextureRect().getMaxX();
	float spy = backgroundSprite->getTextureRect().getMaxY();

	backgroundSprite->setScaleX(winw / spx); //设置精灵宽度缩放比例
	backgroundSprite->setScaleY(winh / spy);

    this->addChild( backgroundSprite );
    
    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    edgeBody->setCollisionBitmask(ENEMY_SPAWN_FREQUENCY);
    edgeBody->setContactTestBitmask( true );
    
	// 屏幕边界
    auto edgeNode = Node::create();
    edgeNode->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    edgeNode->setPhysicsBody( edgeBody );
    
    this->addChild( edgeNode );
    
	// 准备
	scheduleOnce(schedule_selector(GameScene::ready), 5.0f);
	readyLabel = Label::createWithTTF("Ready", "fonts/Marker Felt.ttf", 50);
	readyLabel->setPosition(-100, visibleSize.height - 100);
	addChild(readyLabel);
	readyLabel->runAction(MoveTo::create(1.0f, Vec2(visibleSize.width / 2, visibleSize.height - 100)));

	//来一只大鸟
    player = Player::create();
	addChild(player);

	//大鸟要快递的包裹
	package = Sprite::create("package.png");
	package->setPosition(player->getPosition()-Vec2(15, 112));
	package->setPhysicsBody(PhysicsBody::createBox(package->getContentSize()));
	package->getPhysicsBody()->setMass(PACKAGE_MASS);
	package->getPhysicsBody()->setRotationEnable(false);
	package->setScale(0.5);
	// bitmask
	package->getPhysicsBody()->setCategoryBitmask(0x05);
	package->getPhysicsBody()->setCollisionBitmask(0x06);
	package->getPhysicsBody()->setContactTestBitmask(0x00);

	// 初始化受力
	player->getPhysicsBody()->applyForce(Vec2(INTERACTION_FORCE, (PLAYER_MASS + PACKAGE_MASS)*WORLD_GRAVITY + 5000));
	package->getPhysicsBody()->applyForce(Vec2(-INTERACTION_FORCE, 0));

	addChild(package);

	//大鸟的持久时间
    score = 0;
	scoreLock = 10;
    
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/Marker Felt.ttf";
	ttfConfig.fontSize = 36;
    
    scoreLabel = Label::createWithTTF(ttfConfig, "0");
    scoreLabel->setColor( Color3B::WHITE );
    scoreLabel->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height * 0.9 + origin.y ) );
    
    this->addChild( scoreLabel, 10000 );
    
	//大鸟捡到的钱数
	moneyCount = 0;
	MoneyLabel = Label::createWithTTF(ttfConfig, "0");
	MoneyLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 + 100, visibleSize.height * 0.9 + origin.y));
	addChild(MoneyLabel, 10000);

    this->scheduleUpdate( );
    
    return true;
}

//预加载游戏需要的音乐
void GameScene::preloadMusic() {
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/Point.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/Wing.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/Hit.mp3");
}

//播放背景音乐
void GameScene::playBgm() {
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3", true);
}

// 准备阶段
void GameScene::ready(float dt) {
	player->getPhysicsBody()->applyForce(Vec2(0, -(PLAYER_MASS + PACKAGE_MASS)*WORLD_GRAVITY + 5000));
	readyLabel->setString(Value("Go").asString());
	readyLabel->setPosition(Vec2(visibleSize.width / 2, readyLabel->getPositionY()+50));
	readyLabel->runAction(Sequence::create(MoveBy::create(0.2f, Vec2(0, - 50)), FadeOut::create(2.0f), NULL));

	//监听器注册
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	//随机出现各种阻碍物
	this->schedule(schedule_selector(GameScene::newEnemy), ENEMY_SPAWN_FREQUENCY * visibleSize.width);

	//每隔3秒随机出现金币
	this->schedule(schedule_selector(GameScene::newMoney), MONEY_SPAWN_FREQUENCY);

}

//每隔3秒随机出现金币
void GameScene::newMoney(float dt) {
	Vector<Node*> moneys = MoneyGenerator::getInstance()->GenerateMoney();
	for (int i = 0; i < moneys.size(); i++) {
		this->addChild(moneys.at(i));
	}
}

//随机出现障碍物
void GameScene::newEnemy( float dt )
{
	this->addChild(EnemyGenerator::getInstance()->GenerateEnemy());
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
	Node * a = contact.getShapeA()->getBody()->getNode();
    Node * b = contact.getShapeB()->getBody()->getNode();
    
    if (a->getTag() == ENEMY_TAG && b->getTag() == PLAYER_TAG || b->getTag() == ENEMY_TAG && a->getTag() == PLAYER_TAG)
    {         //大鸟被障碍物撞死
		SimpleAudioEngine::getInstance()->playEffect("music/Hit.mp3");
		this->unscheduleAllSelectors();
		delete MoneyGenerator::getInstance();
		delete EnemyGenerator::getInstance();
		auto scene = GameOverScene::createScene( score, moneyCount );
        Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
	} else if (a->getTag() == MONEY_TAG && b->getTag() == PLAYER_TAG) { //大鸟捡到钱
		SimpleAudioEngine::getInstance()->playEffect("music/Point.mp3");
		auto ps = ParticleSystemQuad::create("explode.plist");
		ps->setPosition(b->getPosition());
		this->addChild(ps);
		MoneyGenerator::getInstance()->obtainMoney(a);
		moneyCount++;
		MoneyLabel->setString(Value(moneyCount).asString());
	} else if (b->getTag() == MONEY_TAG && a->getTag() == PLAYER_TAG) { //大鸟捡到钱
		SimpleAudioEngine::getInstance()->playEffect("music/Point.mp3");
		auto ps = ParticleSystemQuad::create("explode.plist");
		ps->setPosition(b->getPosition());
		this->addChild(ps);
		MoneyGenerator::getInstance()->obtainMoney(b);
		moneyCount++;
		MoneyLabel->setString(Value(moneyCount).asString());
	}
    
    return true;
}

bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
	SimpleAudioEngine::getInstance()->playEffect("music/Wing.mp3");
	player->Fly();
    return true;
}

//空格，回车，上箭头，都可以控制大鸟向上飞
void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW
		|| keyCode == EventKeyboard::KeyCode::KEY_ENTER
		|| keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		SimpleAudioEngine::getInstance()->playEffect("music/Wing.mp3");
		player->Fly();
	}
}

//定时器来每帧进行控制
void GameScene::update( float dt )
{
	//定时器来每帧进行计时 考虑dt保证以时间作为度量而非帧数
	if (scoreLock <= 0) {
		scoreLock = 10;
		score += 1;
		scoreLabel->setString(String::createWithFormat("%i", score)->_string);
	}
	else {
		scoreLock -= dt*100;
	}
	CCLOG("time %d", dt);
	//每帧判断障碍物和金币 是否移动到屏幕之外，是就移除
	EnemyGenerator::getInstance()->removeEnemys();
	MoneyGenerator::getInstance()->removeMoney();

	// 自动修正鸟儿位置
	if (player->getPositionX() < visibleSize.width / 2 - 10) {
		player->setPositionX(player->getPositionX()+0.5);
	}
	else if (player->getPositionX() > visibleSize.width / 2 + 10) {
		player->setPositionX(player->getPositionX() - 0.5);
	}

	// 快递包裹位置修复
	if (package->getPositionY() > player->getPositionY()) {
		package->setPositionX(package->getPositionX() - 1);
	}

	//如果大鸟位置在屏幕边缘之外，也就是掉地，就要挂
	if (player->getPosition().y < -10 || player->getPosition().y > visibleSize.height + 50) {
		this->unscheduleAllSelectors();
		delete MoneyGenerator::getInstance();
		delete EnemyGenerator::getInstance();
		auto scene = GameOverScene::createScene(score, moneyCount);
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}

}
