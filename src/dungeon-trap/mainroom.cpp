#include "dungeon-trap/mainroom.h"

MainRoom::MainRoom() {
  playerAI = NULL;
  player = NULL;
  enemy = NULL;
  enemyAI = NULL;
}

void MainRoom::deletePrevious() {
  if(player != NULL) {
    delete player;
    delete playerAI;
    player = NULL;
    playerAI = NULL;
  }
  if(enemy != NULL) {
    delete enemy;
    delete enemyAI;
    enemy = NULL;
    enemyAI = NULL;
  }
}

MainRoom::~MainRoom() {
  deletePrevious();
}

void MainRoom::initialize() {
  deletePrevious();
  
  player = new Character(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 60.0f,
                         PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER);
  playerAI = new PlayerAI(player);

  enemy = new Character(SCREEN_WIDTH / 2.0f, 0.0f, 
                         PLAYER_WIDTH, PLAYER_HEIGHT, ENEMY);
  enemyAI = new EnemyAI(enemy, player);
}

void MainRoom::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
  SDL_RenderClear(renderer);
  
  player->display(renderer);
  enemy->display(renderer);
}

bool MainRoom::runGameLoop() {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      transition = -1;
      return false;
    }
  }
  
  const Uint8* state = SDL_GetKeyboardState(NULL);
  playerAI->keyboardHold(state);
  
  enemyAI->update();
  
  return true;
}
