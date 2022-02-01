#include "StateMachine.h"
#include <iostream>


StateMachine::StateMachine()
{
	
}

StateMachine::~StateMachine()
{
	std::cout << "Destroying FMS...\n";
	Clean();
}

void StateMachine::Update()
{
	if(!states.empty())
		states.back()->Update();
}

void StateMachine::Render()
{
	if(!states.empty())
		states.back()->Render();
}

void StateMachine::PushState(ScreenState* state)
{
	state->Enter();
	states.push_back(state);
}

void StateMachine::ChangeState(ScreenState* state)
{
	if(!states.empty())
	{
		DeleteCurrentState();
	}
	

	PushState(state);
}

void StateMachine::PopState()
{
	if(!states.empty())
	{
		DeleteCurrentState();
	}
	
	states.back()->Resume();
}

void StateMachine::Clean()
{
	while(!states.empty())
	{
		DeleteCurrentState();
	}
}

void StateMachine::DeleteCurrentState()
{
	states.back()->Exit();
	delete states.back(); //de-allocates the states in the heap
	states.back() = nullptr;
	states.pop_back(); //remove the now null pointer from the vector
}


