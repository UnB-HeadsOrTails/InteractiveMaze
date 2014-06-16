#include "game_state_machine.h"

using namespace std;

GameStateMachine *GameStateMachine::instance = 0;

GameStateMachine::GameStateMachine()
{
	
}

GameStateMachine *
GameStateMachine::getInstance()
{
	if(instance == 0)
		instance = new GameStateMachine();

	return instance;
}

void
GameStateMachine::pushState(GameState *gameState)
{
	this->gameStateStack.push(gameState);
}

void
GameStateMachine::popState()
{
	if(!this->gameStateStack.empty())
	{
		this->gameStateStack.pop();
	}
}

void
GameStateMachine::changeState(GameState *gameState)
{
	popState();
	pushState(gameState);
}

void
GameStateMachine::setGameStateMachineListener(GameStateMachineListener *gameStateMachineListener)
{
	this->gameStateMachineListener = gameStateMachineListener;
}

bool
GameStateMachine::haveListener()
{
	return this->gameStateMachineListener != 0;
}

void
GameStateMachine::notifyOnGameStateChange(GameState *gameState)
{
	if(haveListener())
	{
		this->gameStateMachineListener->onGameStateChange(gameState);
	}
}