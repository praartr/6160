#include <vector>
#include <list>
#include <SDL.h>
#include "ioManager.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include "health.h"
#include "scaledSprite.h"
class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;
  bool showHud;
  SDL_Surface * const screen;
  SDL_Surface * const bananaSurface;
  SDL_Surface * const pineappleSurface;
  World night_sky;
  World front_building;
  World platform;
  Viewport& viewport;

  std::vector<Drawable*> sprites;
  int currentSprite;

  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;
 
  Hud hud;
  Health health;
  std::list<ScaledSprite*> fruits;
  
  void makeFruits();
  void printFruits() const;
  void drawScaledSprite( std::list<ScaledSprite*>::const_iterator &ptr, float desiredScale) const;
  
  void draw() const;
  void update();
  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
