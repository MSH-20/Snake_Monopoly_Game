#include "EditAction.h"
#include "Card.h"
#include "CardM10.h"
#include "CardM11.h"
#include "CardM12.h"
#include "CardM13.h"
EditAction::EditAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}
EditAction::~EditAction()
{
}
void EditAction::ReadActionParameters()
{
	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("Edit : Click on cell that you want to Edit ...");
	cardPosition = pIn->GetCellClicked();
	// 5- Clear status bar
	pOut->ClearStatusBar();
}
void readof10to13(int& p, int& f,Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New Card10: Enter the price: ");
	p = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the fees: ");
	f = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();
}
void EditAction::Execute()
{

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (cardPosition.IsValidCell())
	{
		Card* pCard = NULL;
		pCard = dynamic_cast<Card*>(pGrid->GetGameObject(cardPosition));
		if (pCard)
		{
			int price, fees;
			switch ((pCard)->GetCardNumber())
			{
			case 1: 
			case 2:
			case 9:
				pCard->ReadCardParameters(pGrid);
				pGrid->AddObjectToCell(pCard);
				pOut->PrintMessage("Card cell have been Edited, Click to continue ...");
				break;
			case 10:
				readof10to13(price, fees, pGrid);
				dynamic_cast<CardM10*>(pCard)->SetPrice(price);
				dynamic_cast<CardM10*>(pCard)->SetFees(fees);
				break;
			case 11:
				readof10to13(price, fees, pGrid);
				dynamic_cast<CardM11*>(pCard)->SetPrice(price);
				dynamic_cast<CardM11*>(pCard)->SetFees(fees);
				break;
			case 12:
				readof10to13(price, fees, pGrid);
				dynamic_cast<CardM12*>(pCard)->SetPrice(price);
				dynamic_cast<CardM12*>(pCard)->SetFees(fees);
				break;
			case 13:
				readof10to13(price, fees, pGrid);
				dynamic_cast<CardM13*>(pCard)->SetPrice(price);
				dynamic_cast<CardM13*>(pCard)->SetFees(fees);
				break;
			default:
				pOut->PrintMessage("Card cell can not be Edited, Click to continue ...");
			}
		}
		else
		{
			pOut->PrintMessage("you have not Edited a card cell (check if you have choosen a card), Click to continue ...");
		}
	}
	else
	{
		pOut->PrintMessage("you have not choosen a valid cell, Click to continue ...");
	}
	pIn->GetCellClicked();
	pOut->ClearStatusBar();
}