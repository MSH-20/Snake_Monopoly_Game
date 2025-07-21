#include "PasteAction.h"
#include "Card.h"
#include "Card1.h"
#include "Card2.h"
#include "Card3.h"
#include "Card4.h"
#include "Card5.h"
#include "Card6.h"
#include "Card7.h"
#include "Card8.h"
#include "Card9.h"
#include "CardM10.h"
#include "CardM11.h"
#include "CardM12.h"
#include "CardM13.h"

PasteAction::PasteAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer

}

PasteAction::~PasteAction()
{
}
void PasteAction::ReadActionParameters()
{
	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("Paste : Click on cell that you want to Paste ...");
	cardPosition = pIn->GetCellClicked();
	// 5- Clear status bar
	pOut->ClearStatusBar();
}
void PasteAction::Execute()
{

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Card* pCard = NULL;
	if (cardPosition.IsValidCell())
	{
		if (pGrid->GetClipboard())
		{
			switch ((pGrid->GetClipboard())->GetCardNumber())
			{
			case 1:
				pCard = new Card1(cardPosition);
				dynamic_cast<Card1*>(pCard)->SetWalletAmount(dynamic_cast<Card1*>(pGrid->GetClipboard())->GetWalletAmount());
				break;
			case 2:
				pCard = new Card2(cardPosition);
				dynamic_cast<Card2*>(pCard)->SetWalletAmount(dynamic_cast<Card2*>(pGrid->GetClipboard())->GetWalletAmount());
				break;
			case 3:
				pCard = new Card3(cardPosition);
				break;
			case 4:
				pCard = new Card4(cardPosition);
				break;
			case 5:
				pCard = new Card5(cardPosition);
				break;
			case 6:
				pCard = new Card6(cardPosition);
				break;
			case 7:
				pCard = new Card7(cardPosition);
				break;
			case 8:
				pCard = new Card8(cardPosition);
				break;
			case 9:
				pCard = new Card9(cardPosition);
				dynamic_cast<Card9*>(pCard)->SetToCellNum(dynamic_cast<Card9*>(pGrid->GetClipboard())->GetToCellNum());
				break;
			case 10:
				pCard = new CardM10(cardPosition);
				dynamic_cast<CardM10*>(pCard)->SetPrice(dynamic_cast<CardM10*>(pGrid->GetClipboard())->GetPrice());
				dynamic_cast<CardM10*>(pCard)->SetFees(dynamic_cast<CardM10*>(pGrid->GetClipboard())->GetFees());
				break;
			case 11:
				pCard = new CardM11(cardPosition);
				dynamic_cast<CardM11*>(pCard)->SetPrice(dynamic_cast<CardM11*>(pGrid->GetClipboard())->GetPrice());
				dynamic_cast<CardM11*>(pCard)->SetFees(dynamic_cast<CardM11*>(pGrid->GetClipboard())->GetFees());
				break;
			case 12:
				pCard = new CardM12(cardPosition);
				dynamic_cast<CardM12*>(pCard)->SetPrice(dynamic_cast<CardM12*>(pGrid->GetClipboard())->GetPrice());
				dynamic_cast<CardM12*>(pCard)->SetFees(dynamic_cast<CardM12*>(pGrid->GetClipboard())->GetFees());
				break;
			case 13:
				pCard = new CardM13(cardPosition);
				dynamic_cast<CardM13*>(pCard)->SetPrice(dynamic_cast<CardM13*>(pGrid->GetClipboard())->GetPrice());
				dynamic_cast<CardM13*>(pCard)->SetFees(dynamic_cast<CardM13*>(pGrid->GetClipboard())->GetFees());
				break;
				// A- Add the remaining cases
				//done all were added
			}
			pGrid->AddObjectToCell(pCard);
			pOut->PrintMessage("Card cell have been pasted, Click to continue ...");
		}
		else
		{
			pOut->PrintMessage("you have not pasted a card cell (check if you have copied a one), Click to continue ...");
		}
	}
	else
	{
		pOut->PrintMessage("you have not choosen a valid cell, Click to continue ...");
	}
}

