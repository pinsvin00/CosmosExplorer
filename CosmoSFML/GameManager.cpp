#include "GameManager.h"
void GameManager::state_change_callback(int state)
{
	if (state == GAME) {
		env.on_load();
		//nie rob jakiegos boola tylko zrob funkcje ktora to robi
	}
	this->state = state;
}