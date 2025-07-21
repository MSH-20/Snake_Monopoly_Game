#pragma once
#include "Action.h"
class DeleteAction :
	public Action
{
	CellPosition cardPosition; // 1- cell position of the 
public:

	DeleteAction(ApplicationManager* pApp);  // Constructor

	virtual void ReadActionParameters(); // Reads parameters required for action to execute 

	virtual void Execute();  // Executes action

	virtual ~DeleteAction();  // Virtual Destructor
};

