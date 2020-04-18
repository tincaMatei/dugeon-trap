#include "dungeon-trap/environment.h"
#include "graphicshandler.h"

Wall::Wall(float _x, float _y, float _w, float _h) :
PhysicalObject(getRectangle(_x, _y, _w, _h), 1.0f) {
}

void Wall::display(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  drawPolygon(renderer, shape);
}
