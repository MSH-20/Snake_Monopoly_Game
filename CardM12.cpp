#include "CardM12.h"
CardM12::CardM12(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 12; // set the inherited cardNumber data member with the card number (12 here)
}

CardM12::CardM12(const CellPosition& pos, int price, int fees) : Card(pos)
{
	if (!alreadyset)
	{
		this->price = price;
		this->fees = fees;
		alreadyset = true;
	}
	cardNumber = 12;
}

bool CardM12::av = true;
bool CardM12::alreadyset = false;
int CardM12::price;
int CardM12::fees;
Player* CardM12::Owner = nullptr;
bool CardM12::isAlreadySaved = false;

int CardM12::GetPrice()
{
	return price;
}

int CardM12::GetFees()
{
	return fees;
}

void CardM12::SetPrice(int p)
{
	price = p;
}

void CardM12::SetFees(int f)
{
	fees = f;
}

void CardM12::ReadCardParameters(Grid* pGrid)
{
	if (!alreadyset)
	{
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();
		pOut->PrintMessage("New Card12: Enter the price: ");
		price = pIn->GetInteger(pOut);
		pOut->ClearStatusBar();
		pOut->PrintMessage("Enter the fees: ");
		fees = pIn->GetInteger(pOut);
		pOut->ClearStatusBar();
		alreadyset = true;
	}
}

void CardM12::Apply(Grid* pGrid, Player* pPlayer)
{
	int w;
	if (av)
	{
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();
		pOut->PrintMessage("Buy? (y/n)");
		string buy = pIn->GetSrting(pOut);
		pOut->ClearStatusBar();
		if ((buy == "y" || buy == "Y") && pPlayer->GetWallet() >= price)
		{
			av = false;
			Owner = pPlayer;
			w = Owner->GetWallet();
			Owner->SetWallet(w - price);
		}
	}
	else if (pPlayer != Owner)
	{
		w = pPlayer->GetWallet();
		if (w >= fees)
		{
			pPlayer->SetWallet(w - fees);
		}
		else
		{
			pPlayer->SetWallet(0);
		}

		w = Owner->GetWallet();
		Owner->SetWallet(w + fees);
	}
}

void CardM12::Save(ofstream& OutFile)
{
	if (!isAlreadySaved)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << " " << GetPrice() << " " << GetFees() << endl;
		isAlreadySaved = true;
	}
	else
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}

void CardM12::ResetOwnership()
{
	av = true;
	Owner = nullptr;
	alreadyset = false;
}

CardM12::~CardM12(void)
{
}
