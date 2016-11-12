#include "twowaysprite.h"
#include "clock.h"
#include "gamedata.h"
#include "sprite.h"
#include "explodingSprite.h"

TwoWaySprite::TwoWaySprite( const std::string& name) : MultiSprite(name),isJumping(0),idleFrames(Gamedata::getInstance().getXmlInt(getName()+"/idleframe")),idleTime(0),idleTimeLimit(Gamedata::getInstance().getXmlInt("idleTimeLimit")),explosion(NULL)
{
  setVelocity(Vector2f(0,0));
} 

TwoWaySprite::TwoWaySprite( const TwoWaySprite& t) : MultiSprite(t),isJumping(t.isJumping), idleFrames(Gamedata::getInstance().getXmlInt(getName()+"/idleframe")),idleTime(0),idleTimeLimit(Gamedata::getInstance().getXmlInt("idleTimeLimit")), explosion(NULL) {} 

TwoWaySprite::~TwoWaySprite()
{
	delete explosion;
}
void TwoWaySprite::explode() {
  if( explosion ) return;
  else{
  Sprite sprite(getName(),getPosition(),getVelocity(),frames[currentFrame]);	  
  explosion = new ExplodingSprite(sprite);
  }	
}
void TwoWaySprite::draw() const { 
  if( explosion ){
     explosion->draw();
     return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}
void TwoWaySprite::advanceFrame(Uint32 ticks) 
{
   timeSinceLastFrame += ticks;
   Vector2f currVelocity = getVelocity();
   unsigned int numFrames = numberOfFrames - idleFrames;

   if(currVelocity[0]==0 && currVelocity[1]==0)
   {
	idleTime++;
	
	if(idleTime > idleTimeLimit)
	{
		idleTime--; // To avoid overflow - idleTime does not increase to a very high value!
		if(timeSinceLastFrame > frameInterval)
		{
		// Detect Direction
		int cushion = numFrames;
		if((currentFrame > numFrames/2 && currentFrame < numFrames) || (currentFrame >= (numFrames+(idleFrames/2)))) // Facing left
		{
			cushion = numFrames + idleFrames/2;
		}
			currentFrame = (currentFrame>=numFrames?(cushion+((currentFrame+1)%(idleFrames/2))):cushion);
			if(currentFrame == numFrames+2 || currentFrame == numFrames+3)
				idleTime -= (idleTimeLimit/5); // To let the eyes remain closed for sometime
			timeSinceLastFrame = 0;
		}
		}
	return;
	
   }
   idleTime = 0;
   if(currVelocity[0] == 0 ) {
   return; }
   //idleTime = 0; // Reset idle time.
   if(timeSinceLastFrame > frameInterval) {
	
        if(currVelocity[0] >= 0 ) 
	{
	    currentFrame = (currentFrame + 1) % (numFrames/2);
	    timeSinceLastFrame = 0;
	}
	else if(currVelocity[0] < 0 ) 
	{
	    currentFrame = (numFrames/2) + ((currentFrame +1)%(numFrames/2));
	    timeSinceLastFrame = 0;
	}
   }
}

//void TwoWaySprite::update(Uint32 ticks) {}

void TwoWaySprite::update(Uint32 ticks) { 
  
  if(explosion){
	  explosion->update(ticks);
	  if(explosion->chunkCount() == 0){
	     delete explosion;
	     explosion = NULL;
	  }
	  return;
  }
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < (worldHeight-frameHeight)/2) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > Gamedata::getInstance().getXmlInt(getName()+"/startLoc/y")) {
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
