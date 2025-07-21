#include "AddCardAction.h"

AddCardAction::AddCardAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() 
{	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("New Card: Enter the card Number ...");
	cardNumber = pIn->GetInteger(pOut);

	// 3- Read the "cardPosition" parameter (its cell position) and set its data member
	pOut->PrintMessage("New Card: Click on the card position ...");
	cardPosition = pIn->GetCellClicked();
	// 4- Make the needed validations on the read parameters
	//done in the classes
	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddCardAction::Execute() 
{

	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	//We get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();
	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card * pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
		pCard = new Card1(cardPosition);
		break;
	case 2:
		pCard = new Card2(cardPosition);
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
		break;
	case 10:
		pCard = new CardM10(cardPosition);
		break;
	case 11:
		pCard = new CardM11(cardPosition);
		break;
	case 12:
		pCard = new CardM12(cardPosition);
		break;
	case 13:
		pCard = new CardM13(cardPosition);
		break;
	default:
		pGrid->PrintErrorMessage("Error: You have choosen an invalid Cell number ! Click to continue ...");
		// A- Add the remaining cases

	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{

		// A- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
		pCard->ReadCardParameters(pGrid);
		// B- Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pCard);
		// C- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if(!added)
		pGrid->PrintErrorMessage("Error: You have choosen an invalid Cell ! Click to continue ...");
	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}

void AddCardAction::Execute(int t, const CellPosition& p, int par1, int par2)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card* pCard = NULL; // will point to the card object type
	switch (t)
	{
	case 1:
		pCard = new Card1(p, par1);
		break;
	case 2:
		pCard = new Card2(p, par1);
		break;
	case 3:
		pCard = new Card3(p);
		break;
	case 4:
		pCard = new Card4(p);
		break;
	case 5:
		pCard = new Card5(p);
		break;
	case 6:
		pCard = new Card6(p);
		break;
	case 7:
		pCard = new Card7(p);
		break;
	case 8:
		pCard = new Card8(p);
		break;
	case 9:
		pCard = new Card9(p, par1);
		break;
	case 10:
		pCard = new CardM10(p, par1, par2);
		break;
	case 11:
		pCard = new CardM11(p, par1, par2);
		break;
	case 12:
		pCard = new CardM12(p, par1, par2);
		break;
	case 13:
		pCard = new CardM13(p, par1, par2);
		break;
		// A- Add the remaining cases

	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// A- We get a pointer to the Grid from the ApplicationManager
		Grid* pGrid = pManager->GetGrid();
		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
		// C- Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pCard);
		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if (!added)
			pGrid->PrintErrorMessage("Error: You have choosen an invalid Cell ! Click to continue ...");
	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}

void AddCardAction::Open(ifstream& Infile)
{
	int n;
	Infile >> n;
	int t, p, par1, par2;

	bool Exist[14];
	for (int i = 0; i < 14; ++i)
	{
		if(Exist[i] != true)
		{ 
		Exist[i] = false;
		}
	}

	bool repeted;

	for (int i = 0; i < n; ++i)
	{
		par1 = 0;
		par2 = 0;

		repeted = false;

		Infile >> t >> p;


		if (t > 9)
		{
			
			if (!Exist[t])
			{
				Exist[t] = true;
			}
			else
			{
				repeted = true;
			}
		}

		if ((t <= 2 || t >= 9) && !repeted)
			Infile >> par1;
		if (t > 9 && !repeted)
			Infile >> par2;


		CellPosition start(p);
		Execute(t, p, par1, par2);
	}
}
