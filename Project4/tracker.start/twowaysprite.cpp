#include "twowaysprite.h"
#include "clock.h"
#include "gamedata.h"
TwoWaySprite::TwoWaySprite( const std::string& name) : MultiSprite(name),isJumping(0) {
  setVelocity(Vector2f(0,0));
} 

TwoWaySprite::TwoWaySprite( const TwoWaySprite& t) : MultiSprite(t),isJumping(t.isJumping) {} 

void TwoWaySprite::advanceFrame(Uint32 ticks) {
   timeSinceLastFrame += ticks;
   Vector2f currVelocity = getVelocity();
   if(currVelocity[0] == 0 ) return;   
   if(timeSinceLastFrame > frameInterval) {
        if(currVelocity[0] >= 0 ) {
	    currentFrame = (currentFrame + 1) % (numberOfFrames/2);
	    timeSinceLastFrame = 0;
	}
	else if(currVelocity[0] < 0 ) {
	    currentFrame = (numberOfFrames/2) + ((currentFrame +1)%(numberOfFrames/2));
	    timeSinceLastFrame = 0;
	}
   }
}

//void TwoWaySprite::update(Uint32 ticks) {}

void TwoWaySprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < (worldHeight-frameHeight)/2) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
   if(!isJumping)
   velocityY(0.0); 
   velocityY( -abs( velocityY() ) );
  
 }

  if ( X() <= 0) {
    velocityX(0.0);//abs(velocityX()));
  }
  if ( X() >= worldWidth-frameWidth) {
    velocityX(0.0);//-abs( velocityX()) );
  }  

} 
void TwoWaySprite::left()
{ 
  //advanceFrame(ticks);
  if(X() > 0)//&& X() < worldWidth-frameWidth)
  velocityX(Gamedata::getInstance().getXmlInt(getName()+"/speedX"));
 
}

void TwoWaySprite::right()
{
    if(X() < worldWidth-frameWidth)
    velocityX(-(Gamedata::getInstance().getXmlInt(getName()+"/speedX")));
}

void TwoWaySprite::up()
{
  isJumping = 1;
  velocityY(-Gamedata::getInstance().getXmlInt(getName()+"/speedY"));
  
//  velocityY(-(Gamedata::getInstance().getXmlInt(getName()+"/speedY")));
}
void TwoWaySprite::stopX()
{
  velocityX(0.0); 
}
void TwoWaySprite::stopY()
{
 isJumping  = 0;
}
