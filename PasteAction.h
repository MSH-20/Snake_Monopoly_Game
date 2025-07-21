#pragma once
#include "Action.h"

class PasteAction :
	public Action
{
	CellPosition cardPosition; // 1- cell position of the card
public:

	PasteAction(ApplicationManager* pApp);  // Constructor

	virtual void ReadActionParameters(); // Reads parameters required for action to execute 

	virtual void Execute();  // Executes action

	virtual ~PasteAction();  // Virtual Destructor

};

