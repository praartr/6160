#include "hud.h"

Hud::Hud():io(IOManager::getInstance()), screen(io.getScreen()) {

}

void Hud::draw() const {
Draw_AALine(screen,0.0,20.0,200.0,20.0,3.0,255,0,0,0xFF);
Draw_AALine(screen,0.0,125.0,200.0,125.0,210.0,255,255,255,0x21);
Draw_AALine(screen,0.0,230.0,200.0,230.0,3.0,255,0,0,0xFF);
}
