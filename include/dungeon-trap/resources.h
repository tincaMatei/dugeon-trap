#ifndef __RESOURCES_H
#define __RESOURCES_H

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;

const float PLAYER_WIDTH  = 32.0f;
const float PLAYER_HEIGHT = 32.0f;

const int MAX_SIDES = 4;
enum Sides {
  SIDE_UP,
  SIDE_DOWN,
  SIDE_LEFT,
  SIDE_RIGHT
};

enum CharacterType {
  PLAYER,
  ENEMY
};

#endif
