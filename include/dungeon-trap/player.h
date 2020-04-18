#ifndef __PLAYER_H
#define __PLAYER_H

#include "object.h"
#include "dungeon-trap/character.h"

class PlayerAI : public KeyboardObject {
private:
  Character* player;
public:
  PlayerAI(Character* _player);
  
  void keyboardHold(const Uint8* state);
  void keyboardPress(int key, bool repeat = false);
  void keyboardRelease(int key);
};

#endif
