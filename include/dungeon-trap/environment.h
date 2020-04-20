#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <vector>

#include "object.h"
#include "dungeon-trap/resources.h"

class Wall : public DisplayableObject,
             public PhysicalObject {
protected:
  float width, height;
public:
  Wall(float _x, float _y, float _w, float _h);
  
  virtual void display(SDL_Renderer* renderer);
  
  virtual float getSide(Sides side);
}; 

class GateWall : public Wall {
private:
  bool isClosed;
  Sides side;
public:
  GateWall(float _x, float _y, float _w, float _h, Sides _side);
  
  void display(SDL_Renderer* renderer);
  
  void openGate();
  
  bool isOpen();
};

class PressurePlate : public DisplayableObject,
                      public PhysicalObject,
                      public IdleObject {
private:
  bool pressed;
public:
  PressurePlate(float _x, float _y, float _w, float _h);
  
  void display(SDL_Renderer* renderer);
  
  void markPress(bool state);
  bool getState();
  void update();
};

class Dart : public DisplayableObject,
             public PhysicalObject,
             public IdleObject {
private:
  Vector2D speed;
  
  bool dartActive;
public:
  Dart(Polygon* _shape, Vector2D _speed);
  
  void display(SDL_Renderer* renderer);
  
  void update();

  void killDart();
  
  bool isActive();
};

class DartHandler : public DisplayableObject,
                    public IdleObject {
private:
  std::vector<Dart*> darts;
public:
  DartHandler();
  ~DartHandler();
  
  void pushDart(Dart* _dart);
  
  void display(SDL_Renderer* renderer);
  
  void update();
  
  std::vector<Dart*> getDarts();
};

class DartTrap : public Wall,
                 public IdleObject {
private:
  PressurePlate* activator;
  Sides orientation;
  bool canShoot;
  DartHandler* dartHandler;
public:
  DartTrap(float _x, float _y, float _w, float _h, 
           Sides _orientation, PressurePlate* activator, 
           DartHandler* _dartHandler);
  
  void display(SDL_Renderer* renderer);

  void update();
};

#endif
