#ifndef __COLLIDERS_H
#define __COLLIDERS_H

#include "object.h"
#include "dungeon-trap/character.h"
#include "dungeon-trap/environment.h"
#include "dungeon-trap/resources.h"

class WallCharacterCollider : public Collider {
private:
  Wall* wall;
  Character* character;
public:
  WallCharacterCollider(Wall* _wall, Character* _character);
  
  void checkCollision();
};

class GateWallCharacterCollider : public Collider {
private:
  bool levelFinished;
  
  GateWall* gateWall;
  Character* character;
public:
  GateWallCharacterCollider(GateWall* _gateWall, Character* _character);
  
  void checkCollision();

  bool getLevelFinished();
};

class PressurePlateCharacterCollider : public Collider {
private:
  PressurePlate* pressurePlate;
  Character* character;
public:
  PressurePlateCharacterCollider(PressurePlate* _pressurePlate, Character* _character);
  
  void checkCollision();
};

class DartCharacterCollider : public Collider {
private:
  DartHandler* dartHandler;
  Character* character;
public:
  DartCharacterCollider(DartHandler* _dartHandler, Character* _character);
  
  void checkCollision();
};

class DartWallCollider : public Collider {
private:
  DartHandler* dartHandler;
  Wall* wall;
public:
  DartWallCollider(DartHandler* _dartHandler, Wall* _wall);
  
  void checkCollision();
};

class EnemyPlayerCollider : public Collider {
private:
  Character* player;
  Character* enemy;
public:
  EnemyPlayerCollider(Character* _player, Character* _enemy);
  
  void checkCollision();
};

#endif
