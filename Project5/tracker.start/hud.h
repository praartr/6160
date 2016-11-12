#include "ioManager.h"
#include "aaline.h"
#include "clock.h"

class Hud {

public:
  Hud();
  void draw() const;
private:
  Uint32 width;
  Uint32 height;
  Uint32 startX;
  Uint32 startY;
  const IOManager& io;
  SDL_Surface* screen;
  Clock& clock;
  Hud(const Hud&);
  Hud& operator=(const Hud&);

};

