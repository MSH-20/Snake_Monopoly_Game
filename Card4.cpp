#include "Card4.h"
#include "Snake.h"
Card4::Card4(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number (3 here)
}

Card4::~Card4(void)
{
}


void Card4::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Snake* s = pGrid->GetNextSnake(Card::GetPosition());
	if (s)
	{
		pGrid->UpdatePlayerCell(pPlayer, s->GetPosition());
		s->Apply(pGrid, pPlayer);
	}
	else
	{
		pGrid->PrintErrorMessage("There are no snakes ahead");
	}
}

void Card4::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " " << position.GetCellNum() << endl;
}
