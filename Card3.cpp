#include "Card3.h"
#include "Ladder.h"
Card3::Card3(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (3 here)
}

Card3::~Card3(void)
{
}


void Card3::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Ladder* l = pGrid->GetNextLadder(Card::GetPosition());

	if (l)
	{
		pGrid->UpdatePlayerCell(pPlayer, l->GetPosition());
		l->Apply(pGrid, pPlayer);
	}
	else
	{
		pGrid->PrintErrorMessage("There are no ladders ahead");
	}
}

void Card3::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " " << position.GetCellNum() << endl;
}
