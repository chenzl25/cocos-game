#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

unsigned int score;
int money;
Scene* GameOverScene::createScene( unsigned int tempScore, int moneyCount)
{
    score = tempScore;
	money = moneyCount;
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("bg.jpg");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	backgroundSprite->setPosition(ccp(size.width / 2, size.height / 2));
	float winw = size.width; //获取屏幕宽度
	float winh = size.height;//获取屏幕高度

	float spx = backgroundSprite->getTextureRect().getMaxX();
	float spy = backgroundSprite->getTextureRect().getMaxY();

	backgroundSprite->setScaleX(winw / spx); //设置精灵宽度缩放比例
	backgroundSprite->setScaleY(winh / spy);
    
    this->addChild( backgroundSprite );

	//重新开始按钮
    auto retryItem = MenuItemImage::create( "Retry Button.png", "Retry Button Clicked.png", CC_CALLBACK_1( GameOverScene::GoToGameScene, this ) );
    retryItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3 ) );

	//回到主界面按钮
    auto mainMenuItem = MenuItemImage::create( "Menu Button.png", "Menu Button Clicked.png", CC_CALLBACK_1( GameOverScene::GoToMainMenuScene, this ) );
    mainMenuItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 ) );
    
    auto menu = Menu::create( retryItem, mainMenuItem, NULL );
    menu->setPosition( Point::ZERO );
    
    this->addChild( menu );

	//本次得分以及捡到的钱数，比本地记录大，就更新本地记录
    UserDefault *def = UserDefault::getInstance( );
    
    auto highScore = def->getIntegerForKey( "HIGHSCORE FLAPPY Score", 0 );
    
    if ( score > highScore )
    {
        highScore = score;
        
        def->setIntegerForKey( "HIGHSCORE FLAPPY Score", highScore );
    }

	auto highMoneyCount = def->getIntegerForKey("HIGHSCORE FLAPPY Money", 0);

	if (money > highMoneyCount) {
		highMoneyCount = money;

		def->setIntegerForKey("HIGHSCORE FLAPPY Money", highMoneyCount);
	}
    
    def->flush( );
    //本次得分
    __String *tempScore = __String::createWithFormat( "score: %i", score );
    
    auto currentScore = LabelTTF::create( tempScore->getCString( ), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
    currentScore->setPosition( Point( visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y + 40) );
    
    this->addChild( currentScore );
	//历史最高得分
    __String *tempHighScore = __String::createWithFormat( "%i", highScore );
    
    auto highScoreLabel = LabelTTF::create( tempHighScore->getCString( ), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
    
    highScoreLabel->setColor( Color3B::YELLOW );
    highScoreLabel->setPosition( Point( visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y + 40) );

    this->addChild( highScoreLabel );
	
	//本次金币
	__String *tempMoney = __String::createWithFormat("money: %i", money);

	auto currentMoney = LabelTTF::create(tempMoney->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
	currentMoney->setPosition(Point(visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y - 40));

	this->addChild(currentMoney);
	//历史最高金币
	__String *tempHighMoney = __String::createWithFormat("%i", highMoneyCount);

	auto highMoneyLabel = LabelTTF::create(tempHighMoney->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);

	highMoneyLabel->setColor(Color3B::YELLOW);
	highMoneyLabel->setPosition(Point(visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y - 40));

	this->addChild(highMoneyLabel);
    
    return true;
}

//回到主界面
void GameOverScene::GoToMainMenuScene( cocos2d::Ref *sender )
{
    auto scene = MainMenuScene::createScene( );
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

//重新开始游戏场景
void GameOverScene::GoToGameScene( cocos2d::Ref *sender )
{
    auto scene = GameScene::createScene( );
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}







