#include <iostream>
#include <cmath>
#include "SDL/SDL_rotozoom.h"
#include "scaledSprite.h"
#include "gamedata.h"

ScaledSprite::ScaledSprite(const std::string& name, 
                           SDL_Surface* surface) :
  Drawable(name,
           Vector2f(rand()% Gamedata::getInstance().getXmlInt("world/width"), 
                    -rand()% Gamedata::getInstance().getXmlInt("world/height")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speed/x"),
                    Gamedata::getInstance().getXmlInt(name+"/speed/y")
                   )
  ), 
  scale(( (rand()% (Gamedata::getInstance().getXmlInt(name+"/scale/max")) )  +1 )     
          * (Gamedata::getInstance().getXmlFloat(name+"/scale/min"))
  ),
 
  scaledSurface( rotozoomSurface(surface, 0, scale, SMOOTHING_ON) ),
  frame( new Frame(scaledSurface, scaledSurface->w, scaledSurface->h,
                   Gamedata::getInstance().getXmlInt(name+"/src/x"), 
                   Gamedata::getInstance().getXmlInt(name+"/src/y"))
  ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
  {  
	  velocityY( velocityY()*scale ); 
  }

ScaledSprite::ScaledSprite(const ScaledSprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()), 
  scale(s.scale),
  scaledSurface(s.scaledSurface),
  frame(s.frame),
  frameWidth(s.frameWidth),
  frameHeight(s.frameHeight),
  worldWidth(s.worldWidth),
  worldHeight(s.worldHeight)
{ }

ScaledSprite& ScaledSprite::operator=(const ScaledSprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  scale = rhs.scale;
  scaledSurface = rhs.scaledSurface;
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

ScaledSprite::~ScaledSprite() {
  SDL_FreeSurface( scaledSurface );
  delete frame;
}

void ScaledSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

unsigned ScaledSprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  Uint32 *pixels = static_cast<Uint32 *>(frame->getSurface()->pixels);
  return pixels[ ( y * frame->getWidth() ) + x ];
}

bool ScaledSprite::collidedWith(const Drawable* obj) const 
{
 	const Frame *monkeyFrame = obj->getFrame();
	if(getScale()<=1 /* || getName()=="banana"*/)
		return false;
	Uint16 x = obj->X();
	Uint16 y = obj->Y();
        Uint16 endx = x + monkeyFrame->getWidth();
	Uint16 endy = y + monkeyFrame->getHeight();	
	if(X() > x && X() < endx && Y() > y && Y() < endy)
		return true;
	return false;    
}
void ScaledSprite::update(Uint32 ticks) 
{ 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
	  setPosition(Vector2f(rand()%worldWidth,0.0));
      velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}

