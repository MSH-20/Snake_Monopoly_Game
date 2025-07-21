#pragma once

#include "Action.h"
#include "Snake.h"
#include <fstream>
#include "Input.h"
#include "Output.h"

class AddSnakeAction : public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
	CellPosition startPos; // 1- The start position of the Snake
	CellPosition endPos;   // 2- The end position of the Snake

	// Note: These parameters should be read in ReadActionParameters()

public:

	AddSnakeAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddSnakeAction action parameters (startPos, endPos)
	virtual void Open(ifstream& Infile);
	virtual void Execute(); // Creates a new Snake Object 
	// then Sets this Snake object to the GameObject Pointer of its Cell
	virtual void Execute(const CellPosition& fromCell, const CellPosition& toCell);

	virtual ~AddSnakeAction(); // Virtual Destructor

};

