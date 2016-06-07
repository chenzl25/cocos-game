
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
	PhysicsBody*mb;
	MoveBy *mAction;
	int type= rand()%3; // 0 云 1 山 2 鸟
	double mPos = 0;
	if(type== 0) {
		m = Sprite::create("cloud.png");
		mb = PhysicsBody::createBox( m->getContentSize());
		m->setPosition(visibleSize.width + m->getContentSize().width, visibleSize.height-50-rand() % 120);
		double rand_size = (rand() % 10 + 3)/3;
		m->setScale(rand_size);
		//mPos = rand() % ((int)visibleSize.height - 100) + 80;
		double rand_speed = 2 / (rand() % 2 + 2);
		mAction = MoveBy::create(rand_speed* CLOUD_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
	} else if(type== 1) {
		m = Sprite::create("mount.png");
		double rand_size = (rand() % 27 + 15) / 3;
		m->setScale(rand_size);
		mb = PhysicsBody::createBox( m->getContentSize());
		m->setPosition(visibleSize.width+ m->getContentSize().width, 100);
		//mPos = 20;
		mAction = MoveBy::create( MOUNT_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
	} else if(type== 2) {
		m = Sprite::create("mbird.png");
		mb = PhysicsBody::createBox( m->getContentSize());
		m->setPosition(visibleSize.width+m->getContentSize().width, visibleSize.height -150 - rand() % 150);
		//mPos = rand() % ((int)visibleSize.height - 100) + 50;
		int rand_size = rand() % 3 + 1;
		m->setScale(rand_size);

		double rand_speed = 2 / (rand() % 3 + 2);
		mAction = MoveBy::create(rand_speed* MBIRD_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
	} 
	
	
	///if(type<3) {
	    
    	mb->setDynamic( false );
    	mb->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
        mb->setContactTestBitmask( true );
        layer->addChild( m );
        m->runAction( mAction );
	//}
	
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







