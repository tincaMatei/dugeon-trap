#include "dungeon-trap/enemy.h"

EnemyAI::EnemyAI(Character* _enemy, Character* _player) {
  enemy = _enemy;
  player = _player;
}

void EnemyAI::update() {
  Vector2D movement = player->getShape()->centroidPos - 
                       enemy->getShape()->centroidPos;
  if(movement.length() > 0.0f)
    movement = movement * (1.0f / movement.length());
  enemy->moveObject(movement);
}
