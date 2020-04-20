#include "dungeon-trap/character.h"
#include "graphicshandler.h"

Character::Character(float x, float y, float w, float h, CharacterType _type) :
           PhysicalObject(getRectangle(x, y, w, h), 1.0f) {
  alive = true;
  sides[SIDE_UP]    = getRectangle(x, y - h / 2 + HITBOX_SMALL_LENGTH_RATIO * h / 2,
                                   w * HITBOX_BIG_LENGTH_RATIO, 
                                   h * HITBOX_SMALL_LENGTH_RATIO);
  sides[SIDE_DOWN]  = getRectangle(x, y + h / 2 - HITBOX_SMALL_LENGTH_RATIO * h / 2,
                                   w * HITBOX_BIG_LENGTH_RATIO, 
                                   h * HITBOX_SMALL_LENGTH_RATIO);
  sides[SIDE_LEFT]  = getRectangle(x - w / 2 + HITBOX_SMALL_LENGTH_RATIO * w / 2, y,
                                   w * HITBOX_SMALL_LENGTH_RATIO,
                                   h * HITBOX_BIG_LENGTH_RATIO);
  sides[SIDE_RIGHT] = getRectangle(x + w / 2 - HITBOX_SMALL_LENGTH_RATIO * w / 2, y,
                                   w * HITBOX_SMALL_LENGTH_RATIO,
                                   h * HITBOX_BIG_LENGTH_RATIO);
  type = _type;
  
  width = w;
  height = h;
  moving = false;
  orientation = SIDE_UP;
}

Character::~Character() {
  for(int i = 0; i < MAX_SIDES; ++i)
    delete sides[i];
}

bool Character::isAlive() {
  return alive;
}

void Character::update() {
}

void Character::display(SDL_Renderer* renderer) {
  if(alive) {
    TileSetRenderer* texture = NULL;
    if(type == PLAYER)
      texture = getTexture(PLAYER_TEX);
    else
      texture = getTexture(ENEMY_TEX);
    
    SDL_Rect rect = {shape->centroidPos.x - TILE_WIDTH / 2.0f,
                     shape->centroidPos.y - TILE_HEIGHT / 2.0f,
                     TILE_WIDTH, TILE_HEIGHT};
    
    if(!moving && texture != NULL) {
      texture->renderTexture(renderer, orientation, 0, rect);
    } else if(texture != NULL) {
      texture->renderTexture(renderer, orientation, (SDL_GetTicks() / 250) % 4, rect);
    }
  }
}

void Character::moveObject(Vector2D movement, bool changeOrientation) {
  if(alive) {
    shape->translate(movement);
    for(int i = 0; i < MAX_SIDES; ++i)
      sides[i]->translate(movement);
      
    if(movement.length() > 0.0f) {
      moving = true;
      
      if(changeOrientation && fabs(movement.x) > fabs(movement.y)) {
        if(movement.x > 0.0f)
          orientation = SIDE_RIGHT;
        else
          orientation = SIDE_LEFT;
      } else if(changeOrientation) {
        if(movement.y < 0.0f)
          orientation = SIDE_UP;
        else
          orientation = SIDE_DOWN;
      }
    } else
      moving = false;
  }
}

CharacterType Character::getType() {
  return type;
}

Polygon* Character::getSide(Sides side) {
  return sides[side];
}

void Character::setSide(Sides side, float pos) {
  switch(side) {
  case SIDE_UP:
    moveObject(Vector2D(0.0f, pos - shape->centroidPos.y + height / 2.0f));
    break;
  case SIDE_DOWN:
    moveObject(Vector2D(0.0f, pos - shape->centroidPos.y - height / 2.0f));
    break;
  case SIDE_LEFT:
    moveObject(Vector2D(pos - shape->centroidPos.x + width / 2.0f, 0.0f));
    break;
  case SIDE_RIGHT:
    moveObject(Vector2D(pos - shape->centroidPos.x - width / 2.0f, 0.0f));
    break;
  }
}

void Character::killCharacter() {
  if(alive) {
    alive = false;
    playSound(DEATH);
  }
}
