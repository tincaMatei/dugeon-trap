#include "dungeon-trap/character.h"
#include "graphicshandler.h"

Character::Character(float x, float y, float w, float h, CharacterType _type) :
           PhysicalObject(getRectangle(x, y, w, h), 1.0f) {
  alive = true;
  sides[SIDE_UP]    = getSegment(x - w / 2, y - h / 2, x + w / 2, y - h / 2);
  sides[SIDE_DOWN]  = getSegment(x - w / 2, y + h / 2, x + w / 2, y + h / 2);
  sides[SIDE_LEFT]  = getSegment(x - w / 2, y - h / 2, x - w / 2, y + h / 2);
  sides[SIDE_RIGHT] = getSegment(x + w / 2, y - h / 2, x + w / 2, y + h / 2);
  type = _type;
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
  SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
  drawPolygon(renderer, shape);
}

void Character::moveObject(Vector2D movement) {
  shape->translate(movement);
  for(int i = 0; i < MAX_SIDES; ++i)
    sides[i]->translate(movement);
}

CharacterType Character::getType() {
  return type;
}

Polygon* Character::getSide(Sides side) {
  return sides[side];
}
