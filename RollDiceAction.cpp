#include "RollDiceAction.h"
#include "Player.h"

#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *pApp) : Action(pApp)
{
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
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
			// -- If not ended, do the following --:

			// 2- Generate a random number from 1 to 6 --> This step is done for you
			srand((int)time(NULL)); // time is for different seed each run
			int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed

			// 3- Get the "current" player from pGrid
			Player* p1 = pGrid->GetCurrentPlayer();
			Output* pOut = pGrid->GetOutput();
			Input* pIn = pGrid->GetInput();
		if (p1->GetWallet())                                        // to check if he has money to move
		{
			pOut->PrintMessage("The dice number is " + to_string(diceNumber));
			// 4- Move the currentPlayer using function  of class player
			p1->Move(pGrid, diceNumber);
		// 5- Advance the current player number of pGrid
			pGrid->AdvanceCurrentPlayer();
		}
		else
		{
			p1->IncTurnCount();
			if (p1->GetTurnCount() == 3)
			{
				p1->DecTurnCount();
				p1->Move(pGrid, diceNumber);
			}
			pGrid->AdvanceCurrentPlayer();
		}

		// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).
		
	}
}

RollDiceAction::~RollDiceAction()
{
}
