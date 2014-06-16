#ifndef GAME_STATE_MACHINE_H

#include "game_state.h"
#include <stack>

using namespace std;

class GameStateMachine {
public:

	class GameStateMachineListener {
	public:
		virtual void onGameStateChange(GameState *gameState) = 0;
	};

	static GameStateMachine * getInstance();

	void pushState(GameState *gameState);
	void changeState(GameState *gameState);
	void popState();

	void setGameStateMachineListener(GameStateMachineListener *gameStateMachineListener);

private:
	GameStateMachine();
	static GameStateMachine *instance;

	stack<GameState *> gameStateStack;
	GameStateMachineListener *gameStateMachineListener;

	bool haveListener();
	void notifyOnGameStateChange(GameState *gameState);
};

#endif