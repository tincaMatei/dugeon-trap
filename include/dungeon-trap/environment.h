#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include "object.h"

class Wall : public DisplayableObject,
             public PhysicalObject {
private:

public:
  Wall(float _x, float _y, float _w, float _h);
  
  void display(SDL_Renderer* renderer);
}; 

#endif
