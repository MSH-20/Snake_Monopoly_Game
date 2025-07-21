#include "Card2.h"
Card2::Card2(const CellPosition& pos) : Card(pos)
{
	cardNumber = 2;
}

Card2::Card2(const CellPosition& pos, int walletAmount) : Card(pos)
{
	cardNumber = 2;
	this->walletAmount = walletAmount;
}

Card2::~Card2(void)
{
}


void Card2::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New Card2: Enter its wallet amount ...");
	walletAmount = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();
}

void Card2::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	int newWallet = pPlayer->GetWallet() + walletAmount;
	pPlayer->SetWallet(newWallet);
}
int Card2::GetWalletAmount()
{
	return walletAmount;
}
void Card2::SetWalletAmount(int ComingWalletAmount)
{
	walletAmount = ComingWalletAmount;
}

void Card2::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " " << position.GetCellNum() << " " << GetWalletAmount() << endl;
}
