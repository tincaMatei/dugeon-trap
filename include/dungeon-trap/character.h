#ifndef __CHARACTER_H
#define __CHARACTER_H

#include "object.h"
#include "dungeon-trap/resources.h"

class Character : public DisplayableObject,
                  public PhysicalObject,
                  public IdleObject {
protected:
  Polygon* sides[MAX_SIDES];
  bool alive;
  CharacterType type;
  
public:
  Character(float x, float y, float w, float h, CharacterType _type);
  ~Character();
  
  void display(SDL_Renderer* renderer);
  
  void moveObject(Vector2D movement);
  
  virtual void update();

  bool isAlive();
  
  CharacterType getType();
  
  Polygon* getSide(Sides side);
};

#endif
