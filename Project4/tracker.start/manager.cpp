#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "multisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "twowaysprite.h"

class ScaledSpriteCompare {
public:
  bool operator()(const ScaledSprite* lhs, const ScaledSprite* rhs) {
    return lhs->getScale() < rhs->getScale();
  }
};

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
  for (unsigned i = 0; i < fruits.size(); ++i) {
    delete fruits[i];
  }
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  showHud(Gamedata::getInstance().getXmlBool("hud/showHud")),
  screen( io.getScreen() ),
  bananaSurface (io.loadAndSet(Gamedata::getInstance().getXmlStr("banana/file"), 
              Gamedata::getInstance().getXmlBool("banana/transparency")) ),
  pineappleSurface(io.loadAndSet(Gamedata::getInstance().getXmlStr("pineapple/file"), 
              Gamedata::getInstance().getXmlBool("pineapple/transparency")) ),            
  night_sky("night_sky", Gamedata::getInstance().getXmlInt("night_sky/factor") ),
  front_building("front_building", Gamedata::getInstance().getXmlInt("front_building/factor") ),
  platform("platform", Gamedata::getInstance().getXmlInt("platform/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(0),
  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
  hud(),
  health(),
  fruits()
  {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  makeFruits();
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  sprites.reserve(1);
  sprites.push_back( new TwoWaySprite("monkey") );
  viewport.setObjectToTrack(sprites[currentSprite]);
//  printFruits();
}
void Manager::printFruits() const {
  for (unsigned i = 0; i < fruits.size(); ++i) {
    std::cout << fruits[i]->getScale() << std::endl;
  }
}
void Manager::makeFruits() {
  unsigned numberOfFruits = Gamedata::getInstance().getXmlInt("numberOfFruits");
  fruits.reserve( numberOfFruits );
  for (unsigned i = 0; i < numberOfFruits; i+=2) {
    fruits.push_back( new ScaledSprite("banana", bananaSurface) );
    fruits.push_back( new ScaledSprite("pineapple", pineappleSurface));
  }
  sort(fruits.begin(), fruits.end(), ScaledSpriteCompare());
}
void Manager::drawSmall(unsigned int* start_index) const {
	
  while(*start_index < fruits.size() && fruits[*start_index]->getScale() == 0.5) {
    fruits[*start_index]->draw();
    (*start_index)++;
  }
	
}
void Manager::drawMedium(unsigned int* start_index) const {
	
  while( *start_index < fruits.size() && fruits[*start_index]->getScale() == 1.0) {
    fruits[*start_index]->draw();
    (*start_index)++;
  }	
 
}
void Manager::drawLarge(unsigned int* start_index) const {
	
  while( *start_index<fruits.size() && fruits[*start_index]->getScale() == 1.5 ) {
    fruits[*start_index]->draw();
    (*start_index)++;
  }	
}
void Manager::draw() const {
	
  unsigned int start_index = 0;
  night_sky.draw();
  drawSmall(&start_index);
  front_building.draw();
  drawMedium(&start_index);
  platform.draw();
  drawLarge(&start_index);
  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }
  io.printMessageAt(title, 10, 450);
  if(showHud) {
    hud.draw();
  }
  health.draw();
  viewport.draw();
  SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  currentSprite = (currentSprite+1) % sprites.size();
  viewport.setObjectToTrack(sprites[currentSprite]);
}

void Manager::update() {  
  ++(clock);
  Uint32 ticks = clock.getElapsedTicks();
  static unsigned int lastSeconds = clock.getSeconds();
  if ( clock.getSeconds() - lastSeconds == 5 ) {
    lastSeconds = clock.getSeconds();
    //switchSprite();
  }
  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  night_sky.update();
  front_building.update();
  platform.update();
//  health.update(ticks);
  for(unsigned int i=0; i< fruits.size(); i++) 
  {
    fruits[i]->update(ticks);
    bool isCollided = fruits[i]->collidedWith(sprites[0]);
   if(isCollided)
	 health.update(ticks);
    //if(isCollided)
	//reduceHealthMeter();
  }
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;
  bool done = false;

  while ( not done ) {
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
        if ( keystate[SDLK_t] ) {
         // switchSprite();
        }
        if( keystate[SDLK_a] ) {
         static_cast<TwoWaySprite*>(sprites[0])->left();
        }
        if( keystate[SDLK_d] ) {
           static_cast<TwoWaySprite*>(sprites[0])->right();
        }
        if( keystate[SDLK_w] ) {
           static_cast<TwoWaySprite*>(sprites[0])->up();
        }
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
        if(keystate[SDLK_F1]) {
         showHud = !showHud;
       }
      }
     if ( event.type == SDL_KEYUP) {
        if( !keystate[SDLK_w] ) {
           static_cast<TwoWaySprite*>(sprites[0])->stopY();
	    }
        if( !keystate[SDLK_a] && !keystate[SDLK_d] ) {
           static_cast<TwoWaySprite*>(sprites[0])->stopX();
	    }
         
      }  
    }
    if(clock.getSeconds() == 2)
    showHud = 0;
    draw();
    update();
  }
}
