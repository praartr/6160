#include "hud.h"

Hud::Hud():
	width(Gamedata::getInstance().getXmlInt("hud/hudWidth")),
        height(Gamedata::getInstance().getXmlInt("hud/hudHeight")),
        startX(Gamedata::getInstance().getXmlInt("hud/hudStartX")),
        startY(Gamedata::getInstance().getXmlInt("hud/hudStartY")),
        io(IOManager::getInstance()), 
        screen(io.getScreen()),
        clock(Clock::getInstance()) 
{}

void Hud::draw() const {
//transparent background
Draw_AALine(screen,startX,startY+height/2,startX+width,startY+height/2,height/40,0,0,0,0x50);
//top border
Draw_AALine(screen,startX,startY,startX+width,startY,3.0,255,0,0,0xFF);
//bottom border
Draw_AALine(screen,startX,startY+height/2,startX+width,startY+height/2,3.0,255,0,0,0xFF);
io.printMessageValueAt("Fps:",clock.getAverageFrameRate(),startX+10,startY+30 );
io.printMessageValueAt("Sec:",clock.getSeconds(),startX+10,startY+50);

io.printMessageAt("Left: Key A",startX+10,startY+70);
io.printMessageAt("Right: Key D",startX+10,startY+90);
io.printMessageAt("Jump : Key W",startX+10,startY+110);

}

