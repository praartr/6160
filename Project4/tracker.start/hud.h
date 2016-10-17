#include "ioManager.h"
#include "aaline.h"

class Hud {

public:

Hud();
void draw() const;

private:

const IOManager& io;
SDL_Surface* screen;
Uint32 RED = SDL_MapRGB(screen->format,0xff,0,0);
//Transparency =  SDL_MapRGB(screen->format,0xff,0xff,0xff);
Hud(const Hud&);
Hud& operator=(const Hud&);

};
