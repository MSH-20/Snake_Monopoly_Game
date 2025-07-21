#include "DiceValueAction.h"
#include "Player.h"


DiceValueAction::DiceValueAction(ApplicationManager* pApp) : Action(pApp)
{
	num = 0;
	anum = 0;
}

DiceValueAction::~DiceValueAction()
{
}

void DiceValueAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("please enter a dice value between 1-6: ");
	num = pIn->GetInteger(pOut);
	if (num > 6 || num < 1)
	{
		pGrid->PrintErrorMessage("Invalid");

	}
	else
	{
		anum = 1;
	}

}

void DiceValueAction::Execute()
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	Grid* pGrid = pManager->GetGrid();
	if (pGrid->GetEndGame())
	{
		pGrid->PrintErrorMessage("Game has ended");
	}
	else
	{
		ReadActionParameters();

		if (anum)
		{
			Player* p1 = pGrid->GetCurrentPlayer();
			if (p1->GetWallet())
			{
				p1->Move(pGrid, num);

				pGrid->AdvanceCurrentPlayer();
			}
			else
			{
				p1->IncTurnCount();
				pGrid->AdvanceCurrentPlayer();
			}

		}
	}
}


