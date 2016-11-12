#include <vector>
#include <list>
#include "drawable.h"
#include "frames.h"
class MultiBullet : Drawable {

public:
   virtual void draw () const;
   virtual void update(Uint32 ticks);
   void shoot();
private:
   double lifetime;
   std::vector<Frames*> bulletFrames;
   std::list<MultiBullet> bulletList;
   std::list<MultiBullet> freeList;
};
