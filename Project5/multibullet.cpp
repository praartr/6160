#include "multibullet.h"

MultiBullet::MultiBullet() : lifetiime(0), bulletFrames(), bulletList(), freeList() {} 

MultiBullet::~MultiBullet() {
  std::vector<Frames*>::iterator ptr = bulletFrames.begin();
  while(ptr != bulletFrames.end()){
    ptr = bulletFrames.erase(ptr);
  }
  std::list<MultiBullet>::iterator ptr1 = bulletList.begin();
  while(ptr1 != bulletList.end()){
    ptr1 = bulletList.erase(ptr1);
  }
  std::list<MultiBullet>::iterator ptr2 = freeList.begin();
  while(ptr2 != freeList.end()){
    ptr2 = freeList.erase(ptr1);
  }
}

void MultiBullet::reset(){


}
void MultiBullet::shoot(){

  if(freeList.empty()){
    bulletList.push_back(new MultiBullet());      
  
  } 
  else {
    MultiBullet b = freeList.popFront();
    b.reset();
    bulletList.push_back(b);
  }  

}
void draw () const {
	
	
}
void update(Uint32 ticks) {


}
