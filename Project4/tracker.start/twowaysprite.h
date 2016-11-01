#include "multisprite.h"


class TwoWaySprite : public MultiSprite {

public :
	TwoWaySprite(const std::string&);
	TwoWaySprite(const TwoWaySprite&);

      void left();
      void right();
      void up();
      void stopX();
      void stopY();
private:
      virtual void advanceFrame(Uint32 ticks);
      virtual void update(Uint32 ticks);
      int isJumping;
      unsigned int idleFrames;
      unsigned int idleTime;
      const unsigned int idleTimeLimit; 	
};

