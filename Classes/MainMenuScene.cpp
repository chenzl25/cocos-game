#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
//游戏主界面，通过点击开始按钮可以进入游戏场景
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create( "bg.jpg" );
    backgroundSprite->setPosition(Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
	Size size = Director::getInstance()->getWinSize();
	backgroundSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	float winw = size.width; //获取屏幕宽度
	float winh = size.height;//获取屏幕高度

	float spx = backgroundSprite->getTextureRect().getMaxX();
	float spy = backgroundSprite->getTextureRect().getMaxY();

	backgroundSprite->setScaleX(winw / spx); //设置精灵宽度缩放比例
	backgroundSprite->setScaleY(winh / spy);


    this->addChild( backgroundSprite );
    
    /*auto titleSprite = Sprite::create( "Title.png" );
    titleSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height - titleSprite->getContentSize( ).height ) );
    
    this->addChild( titleSprite );*/
    
    auto playItem = MenuItemImage::create( "Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1( MainMenuScene::GoToGameScene, this ) );
    playItem->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    auto menu = Menu::create( playItem, NULL );
    menu->setPosition(Vec2::ZERO );
    
    this->addChild( menu );
    
    return true;
}

//点击开始按钮可以进入游戏场景
void MainMenuScene::GoToGameScene( cocos2d::Ref *sender )
{
    auto scene = GameScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}



