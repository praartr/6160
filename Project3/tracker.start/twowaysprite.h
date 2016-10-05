#include "multisprite.h"


class TwoWaySprite : public MultiSprite {

public :
	TwoWaySprite(const std::string&);
	TwoWaySprite(const TwoWaySprite&);

private:
      virtual void advanceFrame(Uint32 ticks);

};

