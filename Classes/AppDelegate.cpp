#include "AppDelegate.h"
#include "SplashScene.h"

// is the game landscape or portrait (true for landscape and false for portrait)
#define IS_LANDSCAPE true

USING_NS_CC;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("Demo", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		glview = GLViewImpl::create("Demo");
#endif
		director->setOpenGLView(glview);
	}

    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    auto fileUtils = FileUtils::getInstance( );
    auto screenSize = glview->getFrameSize( );
    std::vector<std::string> resDirOrders;
    

    

	Animation* an = Animation::create();
	an->addSpriteFrameWithFileName("bird_hero.png");
	an->addSpriteFrameWithFileName("bird_hero2.png");
	an->addSpriteFrameWithFileName("bird_hero3.png");
	an->setDelayPerUnit(0.5f / 3.0f);
	an->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(an, "flying_bird");


    // create a scene. it's an autorelease object
    auto scene = SplashScene::createScene();
    
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
