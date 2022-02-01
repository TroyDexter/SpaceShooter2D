#pragma once
#include <vector>
#include "ScreenState.h"

using namespace std;


class StateMachine
{
private:
	vector<ScreenState*> states;
	void DeleteCurrentState();
	
public:
	StateMachine();
	~StateMachine();

	void Update();
	void Render();
	void PushState(ScreenState* state);
	void ChangeState(ScreenState* state);
	void PopState();
	void Clean();
};

