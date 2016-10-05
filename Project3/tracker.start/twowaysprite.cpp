#include "twowaysprite.h"

TwoWaySprite::TwoWaySprite( const std::string& name) : MultiSprite(name) {} 

TwoWaySprite::TwoWaySprite( const TwoWaySprite& t) : MultiSprite(t) {} 

  void TwoWaySprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	Vector2f currVelocity = getVelocity();
//	std::cout << "currVelocity" << currVelocity[0] << std::endl;
     if(timeSinceLastFrame > frameInterval){
        if(currVelocity[0] >= 0 ){
		currentFrame = (currentFrame + 1) % (numberOfFrames/2);
		timeSinceLastFrame = 0;
	}
	else if(currVelocity[0] < 0 ){
		currentFrame = (numberOfFrames/2) + ((currentFrame +1)%(numberOfFrames/2));
		timeSinceLastFrame = 0;
	}
}

}
