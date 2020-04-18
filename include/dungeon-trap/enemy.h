#ifndef __ENEMY_H
#define __ENEMY_H

#include "object.h"
#include "dungeon-trap/character.h"

class EnemyAI : public IdleObject {
private:
  Character* enemy;
  Character* player;
public:
  EnemyAI(Character* _enemy, Character* _player);
  
  void update();
};

#endif
