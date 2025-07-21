#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "AddLadderAction.h"
#include "AddSnakeAction.h"
#include "AddCardAction.h"


class OpenAction : public Action
{
private:
	string F;
public:
	OpenAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~OpenAction();
};