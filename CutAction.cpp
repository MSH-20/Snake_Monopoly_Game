#include "CutAction.h"
#include "Card.h"
CutAction::CutAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer

}

CutAction::~CutAction()
{
}
void CutAction::ReadActionParameters()
{
	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("Cut : Click on card that you want to cut ...");
	cardPosition = pIn->GetCellClicked();
	// 5- Clear status bar
	pOut->ClearStatusBar();
}
void CutAction::Execute()
{

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (cardPosition.IsValidCell())
	{ 
		Card* pCard = NULL;
		pCard = dynamic_cast<Card*>(pGrid->GetGameObject(cardPosition));
		if (pCard)
		{
			pGrid->SetClipboard(pCard);
			pGrid->RemoveObjectFromCell(cardPosition);
			pOut->PrintMessage("Card cell have been choosen, Click to continue ...");
		}
		else
		{
			pOut->PrintMessage("you have not choosen a card cell, Click to continue ...");
		}
	}
	else
	{
		pOut->PrintMessage("you have not choosen a valid cell, Click to continue ...");
	}
}
