#include "dungeon-trap/resources.h"
#include <vector>

Mix_Music* bgMusic;

std::vector<TileSetRenderer*> textures;
std::vector<Mix_Chunk*> sounds;

void loadMedia(SDL_Renderer* renderer) {
  textures.push_back(new TileSetRenderer("media/wall.png", renderer));
  textures.push_back(new TileSetRenderer("media/pressureplate.png", renderer));
  textures.push_back(new TileSetRenderer("media/darttrap.png", renderer,
                                     TILE_WIDTH, TILE_HEIGHT));
  textures.push_back(new TileSetRenderer("media/background0.png", renderer));
  textures.push_back(new TileSetRenderer("media/background1.png", renderer));
  textures.push_back(new TileSetRenderer("media/background2.png", renderer));
  textures.push_back(new TileSetRenderer("media/background3.png", renderer));
  textures.push_back(new TileSetRenderer("media/background4.png", renderer));
  textures.push_back(new TileSetRenderer("media/player.png", renderer,
                                         TILE_WIDTH, TILE_HEIGHT));
  textures.push_back(new TileSetRenderer("media/enemy.png", renderer,
                                         TILE_WIDTH, TILE_HEIGHT));
  textures.push_back(new TileSetRenderer("media/gates.png", renderer,
                                         TILE_WIDTH, TILE_HEIGHT));
  
  Mix_Chunk* sound = Mix_LoadWAV("media/sfx_dart_shoot.wav");
  sounds.push_back(sound);
  if(sound == NULL)
    SDL_Log("Couldn't load sound media/sfx_dart_shoot.wav: %s\n", Mix_GetError());
  
  sound = Mix_LoadWAV("media/sfx_death.wav");
  sounds.push_back(sound);
  if(sound == NULL)
    SDL_Log("Couldn't load sound media/sfx_death.wav: %s\n", Mix_GetError());
    
  sound = Mix_LoadWAV("media/sfx_level_end.wav");
  sounds.push_back(sound);
  if(sound == NULL)
    SDL_Log("Couldn't load sound media/sfx_level_end.wav: %s\n", Mix_GetError());
  
  bgMusic = Mix_LoadMUS("media/bgmusic.mp3");
  if(bgMusic == NULL) {
    SDL_Log("Couldn't load sound media/bgmusic.mp3: %s\n", Mix_GetError());
  } else {
    Mix_PlayMusic(bgMusic, -1);
  }
}

void freeMedia() {
  for(int i = 0; i < textures.size(); ++i)
    delete textures[i];
  textures.clear();
  
  for(int i = 0; i < sounds.size(); ++i) {
    if(sounds[i] != NULL)
      Mix_FreeChunk(sounds[i]);
    sounds[i] = NULL;
  }
  sounds.clear();
  
  if(bgMusic != NULL) {
    Mix_FreeMusic(bgMusic);
    bgMusic = NULL;
  }
}

TileSetRenderer* getTexture(Textures tex) {
  return textures[tex];
}

void playSound(Sounds sound) {
  if(sounds[sound] != NULL)
    Mix_PlayChannel(-1, sounds[sound], 0);
}
