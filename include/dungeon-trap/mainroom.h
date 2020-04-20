#ifndef __MAINROOM_H
#define __MAINROOM_H

#include <vector>

#include "room.h"
#include "dungeon-trap/resources.h"
#include "dungeon-trap/character.h"
#include "dungeon-trap/player.h"
#include "dungeon-trap/enemy.h"
#include "dungeon-trap/environment.h"
#include "dungeon-trap/colliders.h"

class MainRoom : public Room {
private:
  int level, background;
  
  Character* player;
  PlayerAI* playerAI;
  
  std::vector<Wall*> walls;
  std::vector<WallCharacterCollider*> wccolliders;
  
  std::vector<Character*> enemies;
  std::vector<EnemyAI*> enemyAIs;
  std::vector<EnemyPlayerCollider*> epcolliders;
  
  std::vector<PressurePlate*> plates;
  std::vector<PressurePlateCharacterCollider*> ppccolliders;
  
  DartHandler* dartHandler;
  std::vector<DartWallCollider*> dwcolliders;
  
  std::vector<DartTrap*> dartTraps;
  std::vector<DartCharacterCollider*> dccolliders;
  
  std::vector<GateWall*> gateWalls;
  std::vector<GateWallCharacterCollider*> gwccolliders;
  
  void deletePrevious();
public:
  MainRoom();
  ~MainRoom();
  
  void initialize();
  
  void render(SDL_Renderer* renderer);  
  
  bool runGameLoop();
};

#endif
