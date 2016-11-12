#include "multisprite.h"

class ExplodingSprite;
class TwoWaySprite : public MultiSprite {

public :
	TwoWaySprite(const std::string&);
	TwoWaySprite(const TwoWaySprite&);
	~TwoWaySprite();

      void left();
      void right();
      void up();
      void stopX();
      void stopY();
      virtual void explode();
      virtual void draw() const;
      bool isExploding() const {if(explosion) return true; return false;}
private:
      virtual void advanceFrame(Uint32 ticks);
      virtual void update(Uint32 ticks);
      int isJumping;
      unsigned int idleFrames;
      unsigned int idleTime;
      const unsigned int idleTimeLimit; 	
      ExplodingSprite* explosion;
      TwoWaySprite& operator=(const TwoWaySprite&);
};

