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
  
  float width, height;
  
  bool moving;

  Sides orientation;
public:
  Character(float x, float y, float w, float h, CharacterType _type);
  ~Character();
  
  void display(SDL_Renderer* renderer);
  
  void moveObject(Vector2D movement, bool changeOrientation = false);
  
  virtual void update();

  bool isAlive();
  
  CharacterType getType();
  
  Polygon* getSide(Sides side);
  
  void setSide(Sides side, float pos);
  
  void killCharacter();
};

#endif
