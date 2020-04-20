#include "dungeon-trap/environment.h"
#include "graphicshandler.h"

Wall::Wall(float _x, float _y, float _w, float _h) :
PhysicalObject(getRectangle(_x, _y, _w, _h), 1.0f) {
  width = _w;
  height = _h;
}

void Wall::display(SDL_Renderer* renderer) {
  SDL_Rect rect = {shape->centroidPos.x - width / 2.0f, 
                   shape->centroidPos.y - height / 2.0f,
                   width,
                   height};
  getTexture(WALL)->renderTexture(renderer, 0, 0, rect);
}

float Wall::getSide(Sides side) {
  switch(side) {
  case SIDE_UP:
    return shape->centroidPos.y - height / 2.0f;
  case SIDE_DOWN:
    return shape->centroidPos.y + height / 2.0f;
  case SIDE_LEFT:
    return shape->centroidPos.x - width / 2.0f;
  case SIDE_RIGHT:
    return shape->centroidPos.x + width / 2.0f;
  }
  return 0.0f;
}

GateWall::GateWall(float _x, float _y, float _w, float _h, Sides _side) :
Wall(_x, _y, _w, _h) {
  isClosed = true;
  side = _side;
}

void GateWall::display(SDL_Renderer* renderer) {
  SDL_Rect rect = {shape->centroidPos.x - width / 2.0f, 
                   shape->centroidPos.y - height / 2.0f,
                   width,
                   height};
  getTexture(GATES)->renderTexture(renderer, 1 - isClosed, side, rect);
}

void GateWall::openGate() {
  isClosed = false;
}

bool GateWall::isOpen() {
  return !isClosed;
}

PressurePlate::PressurePlate(float _x, float _y, float _w, float _h) :
PhysicalObject(getRectangle(_x, _y, _w, _h), 1.0f) {
  pressed = false;
}

void PressurePlate::markPress(bool state) {
  pressed |= state;
}

bool PressurePlate::getState() {
  return pressed;
}

void PressurePlate::display(SDL_Renderer* renderer) {
  SDL_Rect rect = {shape->centroidPos.x - TILE_WIDTH / 2.0f, 
                   shape->centroidPos.y - TILE_HEIGHT / 2.0f,
                   TILE_WIDTH,
                   TILE_HEIGHT};
  getTexture(PRESSURE_PLATE)->renderTexture(renderer, 0, 0, rect);
}

void PressurePlate::update() {
  pressed = false;
}

Dart::Dart(Polygon* _shape, Vector2D _speed) : 
PhysicalObject(_shape, 1.0f) {
  speed = _speed;
  dartActive = true;
}

void Dart::display(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
  drawPolygon(renderer, shape);
}

void Dart::update() {
  shape->translate(speed);
}

void Dart::killDart() {
  dartActive = false;
}

bool Dart::isActive() {
  return dartActive;
}

DartHandler::DartHandler() {
}

DartHandler::~DartHandler() {
  for(int i = 0; i < darts.size(); ++i)
    delete darts[i];
  darts.clear();
}

void DartHandler::pushDart(Dart* dart) {
  darts.push_back(dart);
}

void DartHandler::display(SDL_Renderer* renderer) {
  for(int i = 0; i < darts.size(); ++i)
    darts[i]->display(renderer);
}

void DartHandler::update() {
  std::vector<Dart*> sanitizedDarts;
  for(int i = 0; i < darts.size(); ++i)
    if(darts[i]->isActive())
      sanitizedDarts.push_back(darts[i]);
    else
      delete darts[i];
  darts = sanitizedDarts;
  
  for(int i = 0; i < darts.size(); ++i)
    darts[i]->update();
}

std::vector<Dart*> DartHandler::getDarts() {
  return darts;
}

DartTrap::DartTrap(float _x, float _y, float _w, float _h, 
                   Sides _orientation, PressurePlate* _activator,
                   DartHandler* _dartHandler) :
Wall(_x, _y, _w, _h) {
  orientation = _orientation;
  activator = _activator;
  canShoot = true;
  dartHandler = _dartHandler;
}

void DartTrap::display(SDL_Renderer* renderer) {
  SDL_Rect rect = {shape->centroidPos.x - width / 2.0f, 
                   shape->centroidPos.y - height / 2.0f,
                   width,
                   height};
  getTexture(DART_TRAP)->renderTexture(renderer, orientation, 0, rect);
}

void DartTrap::update() {
  if(activator->getState()) {
    if(canShoot) {
      Dart* newdart;
      switch(orientation) {
      case SIDE_UP:
        newdart = new Dart(getSegment(shape->centroidPos.x,
                                      shape->centroidPos.y - height / 2.0f - 1.0f,
                                      shape->centroidPos.x,
                                      shape->centroidPos.y - height / 2.0f - 1.0f - ARROW_LEN),
                                      Vector2D(0.0f, -1.0f) * DART_SPEED);
        break;
      case SIDE_DOWN:
        newdart = new Dart(getSegment(shape->centroidPos.x,
                                      shape->centroidPos.y + height / 2.0f + 1.0f,
                                      shape->centroidPos.x,
                                      shape->centroidPos.y + height / 2.0f + 1.0f + ARROW_LEN),
                                      Vector2D(0.0f,  1.0f) * DART_SPEED);
        break;
      case SIDE_LEFT:
        newdart = new Dart(getSegment(shape->centroidPos.x - width / 2.0f - 1.0f,
                                      shape->centroidPos.y,
                                      shape->centroidPos.x - width / 2.0f - 1.0f - ARROW_LEN,
                                      shape->centroidPos.y),
                                      Vector2D(-1.0f, 0.0f) * DART_SPEED);
        break;
      case SIDE_RIGHT:
        newdart = new Dart(getSegment(shape->centroidPos.x + width / 2.0f + 1.0f,
                                      shape->centroidPos.y,
                                      shape->centroidPos.x + width / 2.0f + 1.0f + ARROW_LEN,
                                      shape->centroidPos.y),
                                      Vector2D( 1.0f, 0.0f) * DART_SPEED);
      }
      dartHandler->pushDart(newdart);
      canShoot = false;
      playSound(DART_SHOOT);
    }
  } else
    canShoot = true;
}
