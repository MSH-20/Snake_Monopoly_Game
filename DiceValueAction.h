#pragma once

#include "Action.h"

class DiceValueAction : public Action
{

	int num;                     // the number of cells to be moved
	bool anum;                   // to check if the number between 0 and 6
public:
	DiceValueAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~DiceValueAction();
};