#include "Card.h"



Card::Card(const CellPosition & pos) : GameObject(pos) // sets the cell position of the GameObject
{
	SetCardNumber(pos.GetCellNum());
	++num;
}
int Card::num = 0;
void Card::SetCardNumber(int cnum)
{
	if (cnum>0&&cnum<14)
	cardNumber = cnum; // needs validation
	else cardNumber = -1; //#?!
	//else will treated as -1 (we don't use - numbers)
}

int Card::GetCardNumber() const
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{

	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(position,GetCardNumber());

}

void Card::ReadCardParameters(Grid * pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer) 
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}


int Card::GetNumberOfCards()
{
	return num;
}
void Card::DecNum()
{
	--num;
}


Card::~Card()
{
}
