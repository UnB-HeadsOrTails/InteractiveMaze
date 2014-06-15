#ifndef GAME_STATE_MACHINE_H

#include "game_state.h"
#include <stack>

using namespace std;

class GameStateMachine {
public:
	static GameStateMachine * getInstance();

	void pushState(GameState *gameState);
	void changeState(GameState *gameState);
	void popState();

private:
	GameStateMachine();
	static GameStateMachine *instance;

	stack<GameState *> gameStateStack;
};

#endif