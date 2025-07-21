#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"

class SaveAction : public Action
{
private:
	string F;
public:
	SaveAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~SaveAction();
};
