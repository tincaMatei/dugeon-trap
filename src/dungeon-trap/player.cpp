#include "dungeon-trap/player.h"

PlayerAI::PlayerAI(Character* _player) {
  player = _player;
}

void PlayerAI::keyboardHold(const Uint8* state) {
  Vector2D move;
  
  if(state[SDL_SCANCODE_W])
    move = move + Vector2D( 0.0f, -1.0f);
  if(state[SDL_SCANCODE_S])
    move = move + Vector2D( 0.0f,  1.0f);
  if(state[SDL_SCANCODE_A])
    move = move + Vector2D(-1.0f,  0.0f);
  if(state[SDL_SCANCODE_D])
    move = move + Vector2D( 1.0f,  0.0f);
  
  if(move.length() > 0.0f)
    move = move * (1.0f / move.length());
  
  player->moveObject(move * PLAYER_SPEED, true);
}

void PlayerAI::keyboardPress(int key, bool repeat) {
}

void PlayerAI::keyboardRelease(int key) {
}
