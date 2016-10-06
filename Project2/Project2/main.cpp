#include <SDL_image.h>
#include <iostream>
#include <string>
#include "generateFrames.h"

class Sprite 
{
	public:		
	    Sprite(){}		
		virtual SDL_Surface* getImage(const std::string& filename, bool setColorKey) = 0;
		virtual void setScreen() =0;
		virtual void Animation() =0;
		virtual void FreeSurface() =0;
		virtual ~Sprite(){}
	private:
		Sprite(const Sprite&);
		Sprite* operator=(const Sprite&);
};

class Image : public Sprite
{
	public:
		Image(unsigned int w, unsigned int h,float x_vel, float y_vel, float icon_vel,unsigned int dt) : screen(NULL), background(NULL), batman(NULL), superman(NULL), icon(NULL), WIDTH(w), HEIGHT(h), X_VELOCITY(x_vel), Y_VELOCITY(y_vel), ICON_VELOCITY(icon_vel), DT(dt), superman_x(5.0),superman_y(600.0), batman_x(1500.0),batman_y(5.0), icon_x(0.0), icon_y(-120.0)	
		{
			
		}
		void init()
		{
			if (SDL_Init(SDL_INIT_VIDEO) != 0) 
			{
			throw(std::string("Unable to initialize SDL: ")+ SDL_GetError());
			}
			atexit(SDL_Quit);
		}
		~Image() 
		{
			
		}	
		virtual SDL_Surface* getImage(const std::string& filename, bool setColorKey)
		{
			SDL_Surface *temp = IMG_Load(filename.c_str());
			if (temp == NULL) 
			{
				throw std::string("Unable to load bitmap")+SDL_GetError();
			}
			if ( setColorKey ) 
			{
				Uint32 colorkey = SDL_MapRGBA(temp->format, 255, 0, 255, 0);
				SDL_SetColorKey(temp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
			}
			SDL_Surface *image1 = SDL_DisplayFormatAlpha(temp);
			SDL_FreeSurface(temp);
			return image1;	
		}
		virtual void setScreen()
		{
			try
			{
				screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_DOUBLEBUF);
				if (screen == NULL) {
				  throw std::string("Unable to set video mode: ")+SDL_GetError();
				}
				background = getImage("images/background.jpg", false);
				superman = getImage("images/superman.png", true);
				batman = getImage("images/batman.png",true);
				icon = getImage("images/batvssuper.png",true);	
			}
			 
			catch(const std::string& msg) 
			{ 
				std::cout << msg << std::endl;  
			}
		}
		bool update(float& super_x, float& super_y, float& bat_y, float& bat_x, float& icon_x) 
		{ 
			try
			{
				static unsigned int remainder = 0u; 
				static unsigned int currentTicks = 0u;
				static unsigned int prevTicks = SDL_GetTicks();
				currentTicks = SDL_GetTicks();
				unsigned int elapsedTicks = currentTicks - prevTicks + remainder; 
				
				if( elapsedTicks < DT ) 
				return false; 
				
				float incr_x = X_VELOCITY * DT * 0.001;
				float incr_y = Y_VELOCITY * DT * 0.001;
				float incr_icon = ICON_VELOCITY * DT * 0.001;
				
				super_x += incr_x;
				super_y -= incr_y;
				bat_y += incr_y;
				bat_x -= incr_x;
				icon_x += incr_icon;
				
				prevTicks = currentTicks;
				remainder = elapsedTicks - DT; 
				return true;
		    }
			catch(const std::string& msg) 
		    { 
				std::cout << msg << std::endl;  
			}
			catch(...) 
			{ 
				std::cout << "oops" << std::endl;  
			} 		
			return false;
		}
		void draw(SDL_Surface* image, SDL_Surface* screen, float x = 0.0, float y = 0.0) 
		{
			Uint16 w = image->w;
			Uint16 h = image->h;
			Sint16 xCoord = static_cast<Sint16>(x);
			Sint16 yCoord = static_cast<Sint16>(y);
			SDL_Rect src = { 0, 0, w, h };
			SDL_Rect dest = {xCoord, yCoord, 0, 0 };
			if(SDL_BlitSurface(image, &src, screen, &dest) == -1)
			{
				printf("Couldnt do blitting\n ");
			}			
		}
		virtual void Animation()
		{ 
			try
			{   
				SDL_Event event;
				bool makeVideo = false;
				bool done = false;
				bool freshFrame = false; 
				GenerateFrames genFrames(screen);
				while (!done) 
				{
				  while ( SDL_PollEvent(&event) ) 
				  {
					if (event.type == SDL_QUIT) 
						done = true;
					if (event.type == SDL_KEYDOWN) 
					{
					  if (event.key.keysym.sym == SDLK_ESCAPE) 
						done = true;
					}
				  }
				  if ( ( superman_y >=(HEIGHT/2) && superman_x <= (WIDTH-superman->w)) || ( batman_x >= (WIDTH/2) && batman_y <= (HEIGHT-batman->h)) || ( icon_x >= (WIDTH/2))) 
				  {
					freshFrame = update(superman_x,superman_y,batman_y,batman_x,icon_x);		
				  }
				  else 
				  {
					makeVideo = false;
					
				  }
				  if(freshFrame)
				  { 
					freshFrame=false;
					if ( makeVideo ) 
					{
					  genFrames.makeFrame();
					}
				  }			    
				  draw(background, screen);
				  draw(superman, screen, superman_x, superman_y);
				  draw(batman, screen, batman_x, batman_y);
				  draw(icon, screen, icon_x, icon_y);
				  SDL_Flip(screen); 
				}		
		    }
		    catch(const std::string& msg) 
		    { 
				std::cout << msg << std::endl;  
			}
			catch(...) 
			{ 
				std::cout << "oops" << std::endl;  
			}
		}
		virtual void FreeSurface()
		{
			try
			{   SDL_FreeSurface(screen);
				SDL_FreeSurface(background);
				SDL_FreeSurface(batman);
				SDL_FreeSurface(superman);
				SDL_FreeSurface(icon);			
		    }
		    catch(const std::string& msg) 
		    { 
				std::cout << msg << std::endl;  
			}
			catch(...) 
			{ 
				std::cout << "oops" << std::endl;  
			}
		}
	private:
	    SDL_Surface *screen;
		SDL_Surface *background;
		SDL_Surface *batman;
		SDL_Surface *superman;
		SDL_Surface *icon;
		const unsigned int WIDTH;
		const unsigned int HEIGHT;
		const float X_VELOCITY;
		const float Y_VELOCITY;
		const float ICON_VELOCITY;
		const unsigned int DT;
		float superman_x;
		float superman_y;
		float batman_x;
		float batman_y;
		float icon_x;
		float icon_y;
		Image(const Image&);
		Image* operator =(const Image&);
		
		
};

int main()
{
	Image *image= new Image(1920u,1080u,300.0,150.0,250.0,17u);
	image->init();
	image->setScreen();
	image->Animation();
	image->FreeSurface();
    delete image;
    return 0;
}

