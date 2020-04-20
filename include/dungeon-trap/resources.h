#ifndef __RESOURCES_H
#define __RESOURCES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "graphicshandler.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 512;

const float PLAYER_WIDTH  = 18.0f;
const float PLAYER_HEIGHT = 32.0f;

const float HITBOX_SMALL_LENGTH_RATIO = 4.0f / 32.0f;
const float HITBOX_BIG_LENGTH_RATIO   = 24.0f / 32.0f;

const float ARROW_LEN = 16.0f;

const float DART_SPEED = 4.0f;
const float PLAYER_SPEED = 2.0f;
const float ENEMY_SPEED = 1.0f;

const float TILE_WIDTH = 32.0f;
const float TILE_HEIGHT = 32.0f;

const int LAST_LEVEL = 10;

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

void loadMedia(SDL_Renderer* renderer);

enum Textures {
  WALL,
  PRESSURE_PLATE,
  DART_TRAP,
  BACKGROUND0,
  BACKGROUND1,
  BACKGROUND2,
  BACKGROUND3,
  BACKGROUND4,
  PLAYER_TEX,
  ENEMY_TEX,
  GATES
};

enum Sounds {
  DART_SHOOT,
  DEATH,
  LEVEL_END
};

const Textures BGTEX[] = {BACKGROUND0, BACKGROUND1, BACKGROUND2, 
                          BACKGROUND3, BACKGROUND4};

TileSetRenderer* getTexture(Textures tex);

void playSound(Sounds sound);

void freeMedia();

#endif
