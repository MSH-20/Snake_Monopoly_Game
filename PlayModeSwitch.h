#pragma once

#include "Action.h"

class PlayModeSwitch : public Action
{

public:

	PlayModeSwitch(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~PlayModeSwitch();

};
