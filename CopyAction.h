#pragma once
#include "Action.h"
class CopyAction : public Action
{
	CellPosition cardPosition; // 1- cell position of the card
public:

	CopyAction(ApplicationManager* pApp);  // Constructor

	virtual void ReadActionParameters(); // Reads parameters required for action to execute 

	virtual void Execute();  // Executes action

	virtual ~CopyAction();  // Virtual Destructor
};


