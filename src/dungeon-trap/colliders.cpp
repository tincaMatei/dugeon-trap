#include "dungeon-trap/colliders.h"

WallCharacterCollider::WallCharacterCollider(Wall* _wall, Character* _character) {
  wall = _wall;
  character = _character;
}

void WallCharacterCollider::checkCollision() {
  if(wall->getShape()->collides(character->getSide(SIDE_UP)))
    character->setSide(SIDE_UP, wall->getSide(SIDE_DOWN));
  if(wall->getShape()->collides(character->getSide(SIDE_DOWN)))
    character->setSide(SIDE_DOWN, wall->getSide(SIDE_UP));
  if(wall->getShape()->collides(character->getSide(SIDE_LEFT)))
    character->setSide(SIDE_LEFT, wall->getSide(SIDE_RIGHT));
  if(wall->getShape()->collides(character->getSide(SIDE_RIGHT)))
    character->setSide(SIDE_RIGHT, wall->getSide(SIDE_LEFT));
}

GateWallCharacterCollider::
GateWallCharacterCollider(GateWall* _gateWall, Character* _character) {
  gateWall = _gateWall;
  character = _character;
  levelFinished = false;
}

bool GateWallCharacterCollider::getLevelFinished() {
  return levelFinished;
}

void GateWallCharacterCollider::checkCollision() {
  if(gateWall->isOpen()) {
    levelFinished |= character->getShape()->collides(gateWall->getShape());
  } else {
    if(gateWall->getShape()->collides(character->getSide(SIDE_UP)))
      character->setSide(SIDE_UP, gateWall->getSide(SIDE_DOWN));
    if(gateWall->getShape()->collides(character->getSide(SIDE_DOWN)))
      character->setSide(SIDE_DOWN, gateWall->getSide(SIDE_UP));
    if(gateWall->getShape()->collides(character->getSide(SIDE_LEFT)))
      character->setSide(SIDE_LEFT, gateWall->getSide(SIDE_RIGHT));
    if(gateWall->getShape()->collides(character->getSide(SIDE_RIGHT)))
      character->setSide(SIDE_RIGHT, gateWall->getSide(SIDE_LEFT));
  }
}

PressurePlateCharacterCollider::
PressurePlateCharacterCollider(PressurePlate* _pressurePlate,
                               Character* _character) {
  pressurePlate = _pressurePlate;
  character = _character;
}

void PressurePlateCharacterCollider::checkCollision() {
  if(character->isAlive())
    pressurePlate->markPress(pressurePlate->getShape()->collides(character->getShape()));
}

DartCharacterCollider::DartCharacterCollider(DartHandler* _dartHandler,
                                             Character* _character) {
  dartHandler = _dartHandler;
  character = _character;
}

void DartCharacterCollider::checkCollision() {
  std::vector<Dart*> darts = dartHandler->getDarts();
  for(int i = 0; i < darts.size(); ++i)
    if(character->isAlive() && darts[i]->getShape()->collides(character->getShape())) {
      darts[i]->killDart();
      character->killCharacter();
    }
}

DartWallCollider::DartWallCollider(DartHandler* _dartHandler, Wall* _wall) {
  dartHandler = _dartHandler;
  wall = _wall;
}

void DartWallCollider::checkCollision() {
  std::vector<Dart*> darts = dartHandler->getDarts();
  for(int i = 0; i < darts.size(); ++i)
    if(wall->getShape()->collides(darts[i]->getShape()))
      darts[i]->killDart();
}

EnemyPlayerCollider::EnemyPlayerCollider(Character* _player, Character* _enemy) {
  player = _player;
  enemy = _enemy;
}

void EnemyPlayerCollider::checkCollision() {
  if(enemy->isAlive() && enemy->getShape()->collides(player->getShape()))
    player->killCharacter();
}
