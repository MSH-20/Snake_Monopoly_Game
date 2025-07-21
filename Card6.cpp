#include "Card6.h"
Card6::Card6(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (6 here)
}

Card6::~Card6(void)
{
}
void Card6::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2-move the pPlayer by the last rolled dice value
	pPlayer->DecTurnCount();
	pPlayer->Move(pGrid, (-1 * (pPlayer->GetJustRolledDiceNum())));
}

void Card6::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " " << position.GetCellNum() << endl;
}
