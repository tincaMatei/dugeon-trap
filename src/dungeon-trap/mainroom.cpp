#include "dungeon-trap/mainroom.h"
#include <fstream>
#include <string>
#include <algorithm>

void readInt(std::ifstream& fin, int& val) {
  fin.read((char*)&val, sizeof(int));
}

void readUShort(std::ifstream& fin, unsigned short& val) {
  fin.read((char*)&val, sizeof(unsigned short));
}

MainRoom::MainRoom() {
  level = 0;
  player = NULL;
  playerAI = NULL;
  dartHandler = NULL;
}

void MainRoom::deletePrevious() {
  if(player != NULL) {
    delete player;
    delete playerAI;
    player = NULL;
    playerAI = NULL;
  }
  
  for(int i = 0; i < walls.size(); ++i)
    delete walls[i];
  walls.clear();
  
  for(int i = 0; i < wccolliders.size(); ++i)
    delete wccolliders[i];
  wccolliders.clear();
  
  for(int i = 0; i < enemies.size(); ++i) {
    delete enemies[i];
    delete enemyAIs[i];
  }
  enemies.clear();
  enemyAIs.clear();

  for(int i = 0; i < plates.size(); ++i)
    delete plates[i];
  plates.clear();
  
  for(int i = 0; i < ppccolliders.size(); ++i)
    delete ppccolliders[i];
  ppccolliders.clear();
  
  if(dartHandler != NULL) {
    delete dartHandler;
    dartHandler = NULL;
  }
  
  for(int i = 0; i < dccolliders.size(); ++i)
    delete dccolliders[i];
  dccolliders.clear();
  
  for(int i = 0; i < dartTraps.size(); ++i)
    delete dartTraps[i];
  dartTraps.clear();
  
  for(int i = 0; i < gateWalls.size(); ++i)
    delete gateWalls[i];
  gateWalls.clear();
  
  for(int i = 0; i < gwccolliders.size(); ++i)
    delete gwccolliders[i];
  gwccolliders.clear();
  
  for(int i = 0; i < dwcolliders.size(); ++i)
    delete dwcolliders[i];
  dwcolliders.clear();
  
  for(int i = 0; i < epcolliders.size(); ++i)
    delete epcolliders[i];
  epcolliders.clear();
}

MainRoom::~MainRoom() {
  deletePrevious();
}

void MainRoom::initialize() {
  deletePrevious();
  
  std::string lvlnumber;
  int levelc = level;
  if(level == 0)
    lvlnumber = "0";
  while(levelc > 0) {
    lvlnumber.push_back('0' + levelc % 10);
    levelc /= 10;
  }
  std::reverse(lvlnumber.begin(), lvlnumber.end());
  lvlnumber = "data/level" + lvlnumber + ".dat";
  
  std::ifstream fin(lvlnumber, std::ios::in | std::ios::binary);
  if(!fin.is_open()) {
    SDL_Log("Couldn't open level %s\n", lvlnumber.c_str());
    exit(1);
  }
  
  readInt(fin, background);
  
  int playerX, playerY;
  readInt(fin, playerX);
  readInt(fin, playerY);
  
  player = new Character((float)playerX, (float)playerY, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER);
  playerAI = new PlayerAI(player);
  
  unsigned short worldMap[10];
  for(int i = 0; i < 10; ++i)
    readUShort(fin, worldMap[i]);
  for(int i = 0; i < 16; ++i)
    for(int j = 0; j < 10; ++j)
      if((1 << i) & worldMap[j]) {
        Wall* newWall = new Wall(TILE_WIDTH * j + TILE_WIDTH / 2.0f, 
                                 TILE_HEIGHT * i + TILE_HEIGHT / 2.0f, 
                                 TILE_WIDTH, TILE_HEIGHT);
        walls.push_back(newWall);
        wccolliders.push_back(new WallCharacterCollider(newWall, player));
      }
  
  int enemiesSize;
  readInt(fin, enemiesSize);
  for(int i = 0; i < enemiesSize; ++i) {
    int x, y;
    readInt(fin, x);
    readInt(fin, y);
    
    Character* newenemy = new Character(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, ENEMY);
    enemies.push_back(newenemy);
    enemyAIs.push_back(new EnemyAI(newenemy, player));
    
    for(int i = 0; i < walls.size(); ++i)
      wccolliders.push_back(new WallCharacterCollider(walls[i], newenemy));
    epcolliders.push_back(new EnemyPlayerCollider(player, newenemy));
  }
  
  int activators;
  readInt(fin, activators);
  for(int i = 0; i < activators; ++i) {
    int x, y;
    readInt(fin, x);
    readInt(fin, y);
    
    PressurePlate* newPlate = new PressurePlate(x, y, TILE_WIDTH, TILE_HEIGHT);
    plates.push_back(newPlate);
    ppccolliders.push_back(new PressurePlateCharacterCollider(newPlate, player));
    for(int i = 0; i < enemies.size(); ++i)
      ppccolliders.push_back(new PressurePlateCharacterCollider(newPlate, enemies[i]));
  }
  
  dartHandler = new DartHandler();
  for(int i = 0; i < walls.size(); ++i)
    dwcolliders.push_back(new DartWallCollider(dartHandler, walls[i]));
  
  dccolliders.push_back(new DartCharacterCollider(dartHandler, player));
  for(int i = 0; i < enemies.size(); ++i)
    dccolliders.push_back(new DartCharacterCollider(dartHandler, enemies[i]));
  
  int darttraps;
  readInt(fin, darttraps);
  for(int i = 0; i < darttraps; ++i) {
    int x, y, orientation, activator;
    
    readInt(fin, x);
    readInt(fin, y);
    readInt(fin, orientation);
    readInt(fin, activator);
    
    DartTrap* newDart = new DartTrap(x, y, TILE_WIDTH, TILE_HEIGHT, 
                                     (Sides)orientation, plates[activator],
                                     dartHandler);
    dartTraps.push_back(newDart);
    wccolliders.push_back(new WallCharacterCollider(newDart, player));
    for(int i = 0; i < enemies.size(); ++i)
      wccolliders.push_back(new WallCharacterCollider(newDart, enemies[i]));
    
    dwcolliders.push_back(new DartWallCollider(dartHandler, newDart));
  }
  
  fin.close();
  
  if(level < LAST_LEVEL) {
    for(int i = 0; i < 2; ++i) {
      GateWall* newGateWall = new GateWall(TILE_WIDTH * (4 + i) + TILE_WIDTH / 2.0f,
                                           TILE_HEIGHT / 2.0f,
                                           TILE_WIDTH, TILE_HEIGHT, (Sides)i);
      gateWalls.push_back(newGateWall);
      gwccolliders.push_back(new GateWallCharacterCollider(newGateWall, player));
    }
  }
}

void MainRoom::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
  SDL_RenderClear(renderer);
  
  SDL_Rect rect = {SCREEN_WIDTH / 2.0f - 4 * TILE_WIDTH,
                   SCREEN_HEIGHT / 2.0f - 7 * TILE_HEIGHT,
                   8 * TILE_WIDTH,
                   14 * TILE_HEIGHT};
  getTexture(BGTEX[background])->renderTexture(renderer, 0, 0, rect);
  
  for(int i = 0; i < walls.size(); ++i)
    walls[i]->display(renderer);
  
  
  for(int i = 0; i < plates.size(); ++i)
    plates[i]->display(renderer);
  
  for(int i = 0; i < dartTraps.size(); ++i)
    dartTraps[i]->display(renderer);
  
  dartHandler->display(renderer);
  
  for(int i = 0; i < gateWalls.size(); ++i)
    gateWalls[i]->display(renderer);
    
  player->display(renderer);
  for(int i = 0; i < enemies.size(); ++i)
    enemies[i]->display(renderer);
}

bool MainRoom::runGameLoop() {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      transition = EXIT_ROOM;
      return false;
    }
  }
  
  const Uint8* state = SDL_GetKeyboardState(NULL);
  playerAI->keyboardHold(state);
  
  for(int i = 0; i < enemyAIs.size(); ++i)
    enemyAIs[i]->update();
  for(int i = 0; i < plates.size(); ++i)
    plates[i]->update();
  
  for(int i = 0; i < wccolliders.size(); ++i)
    wccolliders[i]->checkCollision();
  for(int i = 0; i < ppccolliders.size(); ++i)
    ppccolliders[i]->checkCollision();
  for(int i = 0; i < dccolliders.size(); ++i)
    dccolliders[i]->checkCollision();
  for(int i = 0; i < epcolliders.size(); ++i)
    epcolliders[i]->checkCollision();
  for(int i = 0; i < dwcolliders.size(); ++i)
    dwcolliders[i]->checkCollision();
  for(int i = 0; i < gwccolliders.size(); ++i) {
    gwccolliders[i]->checkCollision();
    if(gwccolliders[i]->getLevelFinished()) {
      level++;
      transition = 0;
      playSound(LEVEL_END);
      return false;
    }
  }
  
  for(int i = 0; i < dartTraps.size(); ++i)
    dartTraps[i]->update();
  
  dartHandler->update();
  
  if(!player->isAlive()) {
    transition = 0;
    return false;
  }
  
  bool openGates = true;
  for(int i = 0; i < enemies.size(); ++i)
    if(enemies[i]->isAlive())
      openGates = false;
  if(openGates)
    for(int i = 0; i < gateWalls.size(); ++i)
      gateWalls[i]->openGate();
  
  return true;
}
