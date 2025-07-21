#pragma once
#include "Action.h"
class CutAction :
	public Action
{
	CellPosition cardPosition; // 1- cell position of the card
public:

	CutAction(ApplicationManager* pApp);  // Constructor

	virtual void ReadActionParameters(); // Reads parameters required for action to execute 

	virtual void Execute();  // Executes action

	virtual ~CutAction();  // Virtual Destructor
};