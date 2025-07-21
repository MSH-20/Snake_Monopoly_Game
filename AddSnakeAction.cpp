#include "AddSnakeAction.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();



	///TODO: Make the needed validations on the read parameters



	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// We get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	if (startPos.GetCellNum() > endPos.GetCellNum())
	{
		// Create a Snake object with the parameters read from the user
		Snake* pSnake = new Snake(startPos, endPos);


		if (!pGrid->IsOverLapping(pSnake))
		{
			// Add the card object to the GameObject of its Cell:
			bool added = pGrid->AddObjectToCell(pSnake);

			// if the GameObject cannot be added
			if (!added)
			{
				// Print an appropriate message
				pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
			}
			// Here, the Snake is created and added to the GameObject of its Cell, so we finished executing the AddSnakeAction
		}
		else
		{
			pSnake->DecNum();
			delete pSnake;
		}
	}
	else
	{
		pOut->PrintMessage("Really inverted Snake ?!");
	}
}

void AddSnakeAction::Execute(const CellPosition& fromCell, const CellPosition& toCell)
{
	// We get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (fromCell.GetCellNum() > toCell.GetCellNum())
	{
		Snake* pSnake = new Snake(fromCell, toCell);

		// Add the card object to the GameObject of its Cell:
		if (!pGrid->IsOverLapping(pSnake))
		{
			bool added = pGrid->AddObjectToCell(pSnake);
			// if the GameObject cannot be added
			if (!added)
			{
				// Print an appropriate message
				pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
			}
			// Here, the Snake is created and added to the GameObject of its Cell, so we finished executing the AddSnakeAction
		}
		else
		{
			pSnake->DecNum();
			delete pSnake;
		}
	}
	else
	{
		pOut->PrintMessage("Really inverted Snake ?!");
	}
}

void AddSnakeAction::Open(ifstream& Infile)
{
	int n;
	Infile >> n;
	int s, e;
	for (int i = 0; i < n; ++i)
	{
		Infile >> s >> e;
		CellPosition start(s);
		CellPosition end(e);
		Execute(s, e);
	}
}