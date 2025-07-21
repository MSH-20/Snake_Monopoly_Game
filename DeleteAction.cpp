#include "DeleteAction.h"
#include "Card.h"
DeleteAction::DeleteAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer

}

DeleteAction::~DeleteAction()
{
}
void DeleteAction::ReadActionParameters()
{
	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("Delete : Click on card that you want to delete ...");
	cardPosition = pIn->GetCellClicked();
	// 3- Clear status bar
	pOut->ClearStatusBar();
}
void DeleteAction::Execute()
{

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (cardPosition.IsValidCell())
	{
		pGrid->RemoveObjectFromCell(cardPosition);//removing
		pOut->PrintMessage("Cell Object must have been removed (if not make sure you clicked on the right cell), Click to continue ...");
	}
	else
	{
		pOut->PrintMessage("you have not choosen a valid cell, Click to continue ...");
	}
}