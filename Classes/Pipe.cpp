#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe( )
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
}

void Pipe::SpawnPipe( cocos2d::Layer *layer )
{
    CCLOG( "SPAWN MONSTER" );
    
    
    /*
    auto topPipe = Sprite::create( "obstacle_up.png" );
    auto bottomPipe = Sprite::create( "obstacle_down.png" );
    
    auto topPipeBody = PhysicsBody::createBox( topPipe->getContentSize( ) );
    auto bottomPipeBody = PhysicsBody::createBox( bottomPipe->getContentSize( ) );
    */
    srand(time(NULL));
	Sprite* m;
	int type= rand()%5; // 0 云 1 山 2 鸟
	int randY;
	if(type== 0) {
		auto m = Sprite::create("cloud.png");
		auto mb = PhysicsBody::createBox( m->getContentSize( ) );
		randY= rand()%((int)visibleSize.height-100)+80;
		auto mAction = MoveBy::create( CLOUD_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
	} else if(type== 1) {
		auto m = Sprite::create("mount.png");
		auto mb = PhysicsBody::createBox( m->getContentSize( ) );
		randY= 20;
		auto mAction = MoveBy::create( MOUNT_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
	} else if(type== 2) {
		auto m = Sprite::create("mbird.png");
		auto mb = PhysicsBody::createBox( m->getContentSize( ) );
		randY= rand()%((int)visibleSize.height-100)+50;
		auto mAction = MoveBy::create( MBIRD_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
	} 
	
	
	if(type<3) {
	    m->setPosition(visibleSize.width, randY);
    	mb->setDynamic( false );
    	mb->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
        mb->setContactTestBitmask( true );
        layer->addChild( m );
        m->runAction( mAction );
	}
	
	//monsters.push_back(m);
	//addChild(monsters);
	
    
    
    

    /*
    auto random = CCRANDOM_0_1( );
    
    if ( random < LOWER_SCREEN_PIPE_THRESHOLD )
    {
        random = LOWER_SCREEN_PIPE_THRESHOLD;
    }
    else if ( random > UPPER_SCREEN_PIPE_THRESHOLD )
    {
        random = UPPER_SCREEN_PIPE_THRESHOLD;
    }
    */
    /*
    auto topPipePosition = ( random * visibleSize.height ) + ( topPipe->getContentSize( ).height / 2 );
    
    topPipeBody->setDynamic( false );
    bottomPipeBody->setDynamic( false );
    
    topPipeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
    bottomPipeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
    topPipeBody->setContactTestBitmask( true );
    bottomPipeBody->setContactTestBitmask( true );
    */
    /*
    topPipe->setPhysicsBody( topPipeBody );
    bottomPipe->setPhysicsBody( bottomPipeBody );
    
    topPipe->setPosition( Point( visibleSize.width + topPipe->getContentSize( ).width + origin.x, topPipePosition ) );
    bottomPipe->setPosition( Point( topPipe->getPositionX(), topPipePosition - ( Sprite::create( "Ball.png" )->getContentSize( ).height * PIPE_GAP ) - topPipe->getContentSize().height ) );
    
    layer->addChild( topPipe );
    layer->addChild( bottomPipe );
    */
    
    
    /*
    auto topPipeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    auto bottomPipeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    
    topPipe->runAction( topPipeAction );
    bottomPipe->runAction( bottomPipeAction );
    */

    
    
    
    
    /*
    auto pointNode = Node::create( );
    auto pointBody = PhysicsBody::createBox( Size( 1, Sprite::create( "Ball.png" )->getContentSize( ).height * PIPE_GAP ) );
    
    pointBody->setDynamic( false );
    pointBody->setCollisionBitmask( POINT_COLLISION_BITMASK );
    pointBody->setContactTestBitmask( true );
    
    pointNode->setPhysicsBody( pointBody );
    pointNode->setPosition( Point( topPipe->getPositionX( ), topPipe->getPositionY( ) - ( topPipe->getContentSize( ).height / 2 ) - ( ( Sprite::create( "Ball.png" )->getContentSize( ).height * PIPE_GAP ) / 2 ) ) );
    
    layer->addChild( pointNode );
    
    
    auto pointNodeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    
    pointNode->runAction( pointNodeAction );
    */
}







