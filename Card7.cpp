#include "Card7.h"
Card7::Card7(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (7 here)
}

Card7::~Card7(void)
{
}

void Card7::Apply(Grid* pGrid, Player* pPlayer)
{
	int diceNumber = 1 + rand() % 6; // from 1 to 6 --> (random automatic)
	//3- Get the "current" player from pGrid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("The dice number is " + to_string(diceNumber)+" ,Click to move ...");
	//4- Move the currentPlayer using function  of class player
	pIn->GetCellClicked();
	pPlayer->DecTurnCount();
	pPlayer->Move(pGrid, diceNumber);
	pOut->ClearStatusBar();
}

void Card7::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " " << position.GetCellNum() << endl;
}
