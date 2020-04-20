#include <SDL2/SDL.h>
#include "dungeon-trap/mainroom.h"
#include "dungeon-trap/resources.h"

SDL_Window* window;
SDL_Renderer* renderer;

void init() {
  
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    exit(1);
  }
  
  window = SDL_CreateWindow("Deeznuts", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  
  if(window == NULL) {
    SDL_Log("Unable to create window: %s\n", SDL_GetError());
    exit(1);
  }
  
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == NULL) {
    SDL_Log("Unable to create renderer: %s\n", SDL_GetError());
    exit(1);
  }
  
  if(!IMG_Init(IMG_INIT_PNG)) {
    SDL_Log("Unable to initialized SDL_Image: %s", IMG_GetError());
    exit(1);
  }
  
  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 512) < 0) {
    SDL_Log("Unable to initialize SDL_Mixer: %s", Mix_GetError());
    exit(1);
  }
}

void deinit() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  
  renderer = NULL;
  window = NULL;
  
  SDL_Quit();
}

int main(int argc, char** argv) {
  init();
  loadMedia(renderer);
  SDL_ShowCursor(SDL_DISABLE);
  
  MainRoom* mainRoom = new MainRoom();
  
  Room* currentRoom = mainRoom;
  bool quit = false;
  
  while(!quit) {    
    int lag = 0, lastT = SDL_GetTicks();
    currentRoom->initialize();
    
    bool keepRoom = true;
    while(keepRoom) {
      int nowT = SDL_GetTicks();
      lag = lag + nowT - lastT;
      lastT = nowT;
      while(keepRoom && lag >= MS_TICK_SIZE) {
        keepRoom &= currentRoom->runGameLoop();
        lag -= MS_TICK_SIZE;
      }
      currentRoom->render(renderer);
      SDL_RenderPresent(renderer);
    }
    
    if(currentRoom->getTransition() == -1)
      quit = true;
  }
  
  delete mainRoom;

  freeMedia();
  deinit();
  return 0;
}
