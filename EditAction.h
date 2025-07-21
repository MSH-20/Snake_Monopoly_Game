#pragma once
#include "Action.h"
class EditAction :
	public Action
{
	CellPosition cardPosition; // 1- cell position of the card
public:

	EditAction(ApplicationManager* pApp);  // Constructor

	virtual void ReadActionParameters(); // Reads parameters required for action to execute 

	virtual void Execute();  // Executes action

	virtual ~EditAction();  // Virtual Destructor

};

