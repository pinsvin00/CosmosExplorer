#include "GameManager.h"
void GameManager::state_change_callback(int state)
{
   if (state == GAME) {
      env.on_load();
   }
   this->state = state;
}