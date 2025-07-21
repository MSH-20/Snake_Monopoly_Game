#include "AddLadderAction.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

    

	///TODO: Make the needed validations on the read parameters

	

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();  // We get a pointer to the Grid from the ApplicationManager
	Output* pOut = pGrid->GetOutput();

	// Create a Ladder object with the parameters read from the user
	if (startPos.GetCellNum() < endPos.GetCellNum())
	{
		Ladder* pLadder = new Ladder(startPos, endPos);



		if (!pGrid->IsOverLapping(pLadder))
		{
			// Add the card object to the GameObject of its Cell:
			bool added = pGrid->AddObjectToCell(pLadder);

			// if the GameObject cannot be added
			if (!added)
			{
				// Print an appropriate message
				pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
			}
			// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
		}
		else
		{
			pLadder->DecNum();
			delete pLadder;
		}
	}
	else
	{
		pOut->PrintMessage("Really inverted ladder ?!");
	}

}

void AddLadderAction::Execute(const CellPosition& fromCell, const CellPosition& toCell)
{
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	Output* pOut = pGrid->GetOutput();
	if (fromCell.GetCellNum() < toCell.GetCellNum())
	{
	Ladder* pLadder = new Ladder(fromCell, toCell);


	// Add the card object to the GameObject of its Cell:
	if (!pGrid->IsOverLapping(pLadder))
	{
	bool added = pGrid->AddObjectToCell(pLadder);
	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
	}
	else
	{
		pLadder->DecNum();
		delete pLadder;
	}
	}
	else
	{
		pOut->PrintMessage("Really inverted ladder ?!");
	}
}

void AddLadderAction::Open(ifstream& Infile)
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