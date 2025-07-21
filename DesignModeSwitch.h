#pragma once

#include "Action.h"

class DesignModeSwitch : public Action
{

public:

	DesignModeSwitch(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~DesignModeSwitch();

};
