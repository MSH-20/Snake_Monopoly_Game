#include "Card9.h"
Card9::Card9(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 9; // set the inherited cardNumber data member with the card number (9 here)
}

Card9::Card9(const CellPosition& pos, int n) : Card(pos)
{
	cardNumber = 9;
	SetToCellNum(n);
}

void Card9::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New Card9: Enter the moved cell number");
	ToCellNum = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();
}

void Card9::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	CellPosition cellp(ToCellNum);
	pGrid->UpdatePlayerCell(pPlayer, cellp);

}

void Card9::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " " << position.GetCellNum() << " " << GetToCellNum() << endl;
}

int Card9::GetToCellNum()
{
	return ToCellNum;
}

void Card9::SetToCellNum(int n)
{
	ToCellNum = n;
}

Card9::~Card9(void)
{
}